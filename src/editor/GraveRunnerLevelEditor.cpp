#include "editor/GraveRunnerLevelEditor.hpp"

#include "graverunner/LevelData.hpp"
#include "graverunner/Tag.hpp"

void GraveRunnerLevelEditor::initialize() {
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
    currentlySelected = GraveRunnerLevelItem::NOBLOCK;
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
        *this, x, y, 74, 74, 5.f, 5.f, getGraverunnerBlockPath(item),
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
      if (currentlySelected != GraveRunnerLevelItem::NONE) {
        Mix_PlayChannel(1, ResourceManager::getInstance().getChunk(mSoundPath),
                        0);
        updateCurrentLevel(mLevelData, Vector2D<int>(i, j), currentlySelected);
        refreshLevelEditor();
        currentlySelected = GraveRunnerLevelItem::NONE;
      }
    };

    auto levelGrid = std::make_shared<GridObject>(*this, xOffset, 0, 20, 20, 64,
                                                  64, gridCallback);
    addObject(levelGrid);
  }
  refreshLevelEditor();
}

std::string GraveRunnerLevelEditor::getGraverunnerBlockPath(
    GraveRunnerLevelItem item) {
  switch (item) {
    case GraveRunnerLevelItem::NONE:
      return "";
    case GraveRunnerLevelItem::NOBLOCK:
      return "";
    case GraveRunnerLevelItem::TILE1:
      return "Graverunner/graveyardtiles/png/Tiles/Tile1.png";
    case GraveRunnerLevelItem::TILE2:
      return "Graverunner/graveyardtiles/png/Tiles/Tile2.png";
    case GraveRunnerLevelItem::TILE3:
      return "Graverunner/graveyardtiles/png/Tiles/Tile3.png";
    case GraveRunnerLevelItem::TILEX:
      return "Graverunner/graveyardtiles/png/Tiles/TileX.png";
    case GraveRunnerLevelItem::TILEY:
      return "Graverunner/graveyardtiles/png/Tiles/TileY.png";
    case GraveRunnerLevelItem::TILEZ:
      return "Graverunner/graveyardtiles/png/Tiles/TileZ.png";
    case GraveRunnerLevelItem::JACK:
      return "Graverunner/jack/Idle1.png";
    case GraveRunnerLevelItem::PATROLZOMBIE:
      return "Graverunner/zombies/male/Idle1.png";
    case GraveRunnerLevelItem::FOLLOWZOMBIE:
      return "Graverunner/zombies/male/Idle1.png";
    case GraveRunnerLevelItem::KEY:
      return "Graverunner/key.png";
    case GraveRunnerLevelItem::EXIT:
      return "Graverunner/exit.png";
    default:
      std::cerr << "Failed to get Graverunner block path for item "
                << static_cast<int>(item) << std::endl;
      return "";
  }
}

void GraveRunnerLevelEditor::refreshLevelEditor() {
  for (const auto& gameObject : getGameObjects()) {
    // Remove any blocks remaining previously
    if (gameObject->tag() == GraveRunnerLevelBoundaryTag ||
    gameObject->tag() == GraveRunnerBulletTag ||
    gameObject->tag() == GraveRunnerJackTag ||
    gameObject->tag() == GraveRunnerZombieTag ||
    gameObject->tag() == GraveRunnerExitTag ||
    gameObject->tag() == GraveRunnerKeyTag ||
    gameObject->tag() == GraveRunnerNormalBlockTag ||
    gameObject->tag() == BaseTextTag)
      removeObject(gameObject);
  }
  GraveRunnerLevel::initialize();
  // Strip away unwanted things for rendering in level editor
  for (const auto& gameObject : getGameObjectsToAdd()) {
    // Remove any text components (lives, level, score, etc) + Ball + Paddle +
    // Boundaries
    if (gameObject->tag() == GraveRunnerLevelBoundaryTag ||
    gameObject->tag() == GraveRunnerBulletTag ||
    gameObject->tag() == GraveRunnerJackTag ||
    gameObject->tag() == GraveRunnerZombieTag ||
    gameObject->tag() == GraveRunnerExitTag ||
    gameObject->tag() == GraveRunnerKeyTag ||
    gameObject->tag() == GraveRunnerNormalBlockTag ||
    gameObject->tag() == BaseTextTag ||
    gameObject->tag() == GraveRunnerBGTag
    )
      // Add an x-offset to make space for buttons
      gameObject->setX(gameObject->x() + float(xOffset));
  }
  // Read in the level data for our own usage
  loadLevel(&mLevelData, getLevelNumber());
}
