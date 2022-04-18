#include "editor/TdLevelEditor.hpp"

#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"

void TdLevelEditor::initialize() {
  auto toolbarBackground = std::make_shared<GameObject>(
      *this, 0, 0, xOffset, mScreenHeight, hash("ToolbarTag"));
  auto backgroundRenderer =
      std::make_shared<TextureRenderComponent>(*toolbarBackground);

  backgroundRenderer->setRenderMode(
      TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  toolbarBackground->setRenderComponent(backgroundRenderer);
  backgroundRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "2DBreakout/Graphics/editorToolbar.png"));

  addObject(toolbarBackground);

  auto changeToErase = [&] {
    currentlySelected = TdLevelItem::NOBLOCK;
  };

  auto eraseButton =
      std::make_shared<LevelEditButton>(*this, 35, 35, 74, 74, 5, 5,
                                        "2DBreakout/Graphics/"
                                        "erase.png",
                                        mSoundPath, changeToErase);

  addObject(eraseButton);

  // Add buttons here:
  int x = 26;
  int y = 114;
  int count = 0;

  for (const auto& item : itemVector) {
    auto lambda = [&] {
      currentlySelected = item;
      // mGridRenderComponent.setCurrentlySelectedPath(pair.second);
    };
    auto button = std::make_shared<LevelEditButton>(
        *this, x, y, 74, 74, 5.f, 5.f, getTdBlockPath(item),
        mSoundPath, lambda, true);
    addObject(button);
    x = x + 79;
    count++;
    if (count == 2) {
      y = y + 79;
      x = 26;
      count = 0;
    }

    // Grid component here
    auto gridCallback = [&, mLevelData = &mLevelData](int i, int j) {
      if (currentlySelected != TdLevelItem::NONE) {
        Mix_PlayChannel(1, ResourceManager::getInstance().getChunk(mSoundPath),
                        0);
        updateCurrentLevel(mLevelData, Vector2D<int>(i, j), currentlySelected);
        refreshLevelEditor();
        // currentlySelected = GraveRunnerLevelItem::NONE;
      }
    };

    auto levelGrid = std::make_shared<GridObject>(*this, xOffset, 0, 20, 20, 64,
                                                  64, gridCallback);
    addObject(levelGrid);
  }
  refreshLevelEditor();
}

std::string TdLevelEditor::getTdBlockPath(
    TdLevelItem item) {
  switch (item) {
    case TdLevelItem::NONE:
      return "";
    case TdLevelItem::NOBLOCK:
      return "";
    // case TdLevelItem::TILE1:
    //   return "Graverunner/graveyardtiles/png/Tiles/Tile1.png";
    // case TdLevelItem::TILE2:
    //   return "Graverunner/graveyardtiles/png/Tiles/Tile2.png";
    // case TdLevelItem::TILE3:
    //   return "Graverunner/graveyardtiles/png/Tiles/Tile3.png";
    // case TdLevelItem::TILEX:
    //   return "Graverunner/graveyardtiles/png/Tiles/TileX.png";
    // case TdLevelItem::TILEY:
    //   return "Graverunner/graveyardtiles/png/Tiles/TileY.png";
    // case TdLevelItem::TILEZ:
    //   return "Graverunner/graveyardtiles/png/Tiles/TileZ.png";
    // case TdLevelItem::JACK:
    //   return "Graverunner/jack/Idle1.png";
    // case TdLevelItem::PATROLZOMBIE:
    //   return "Graverunner/zombies/male/Idle1.png";
    // case TdLevelItem::FOLLOWZOMBIE:
    //   return "Graverunner/zombies/male/Idle1.png";
    // case TdLevelItem::KEY:
    //   return "Graverunner/key.png";
    // case TdLevelItem::EXIT:
    //   return "Graverunner/exit.png";
    default:
      std::cerr << "Failed to get Tower Defense block path for item "
                << static_cast<int>(item) << std::endl;
      return "";
  }
}

void TdLevelEditor::refreshLevelEditor() {
  for (const auto& gameObject : getGameObjects()) {
    // Remove any blocks remaining previously
    if (/*gameObject->tag() == TdLevelBoundaryTag ||*/
        // gameObject->tag() == TdBulletTag ||
        // gameObject->tag() == TdJackTag ||
        // gameObject->tag() == TdZombieTag ||
        // gameObject->tag() == TdExitTag ||
        // gameObject->tag() == TdKeyTag ||
        // gameObject->tag() == TdNormalBlockTag ||
        gameObject->tag() == BaseTextTag)
      removeObject(gameObject);
  }
  TdLevel::initialize();
  // Strip away unwanted things for rendering in level editor
  for (const auto& gameObject : getGameObjectsToAdd()) {
    // Remove any text components (lives, level, score, etc) + Ball + Paddle +
    // Boundaries
    if (/*gameObject->tag() == TdLevelBoundaryTag ||
        gameObject->tag() == TdBulletTag ||
        gameObject->tag() == TdJackTag ||
        gameObject->tag() == TdZombieTag ||
        gameObject->tag() == TdExitTag ||
        gameObject->tag() == TdKeyTag ||
        gameObject->tag() == TdNormalBlockTag ||
        gameObject->tag() == TdBGTag ||*/
        gameObject->tag() == BaseTextTag)
      // Add an x-offset to make space for buttons
      gameObject->setX(gameObject->x() + float(xOffset));
  }
  // Read in the level data for our own usage
  loadLevel(&mLevelData, getLevelNumber());
}