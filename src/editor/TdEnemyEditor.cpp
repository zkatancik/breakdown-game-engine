#include "editor/TdEnemyEditor.hpp"

#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"



void TdEnemyEditor::initialize() {
  auto toolbarBackground = std::make_shared<GameObject>(
      *this, 0, 0, xOffset, mScreenHeight, hash("ToolbarTag"));
  auto backgroundRenderer =
      std::make_shared<TextureRenderComponent>(*toolbarBackground);

  backgroundRenderer->setRenderMode(
      TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  toolbarBackground->setRenderComponent(backgroundRenderer);
  backgroundRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/sidebar.png"));

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
    if (count == 4) {
      y = y + 79;
      x = 26;
      count = 0;
    }
  }
  // Grid component here
  auto gridCallback = [&, mLevelData = &mLevelData](int i, int j, int x, int y) {
    if (currentlySelected != TdLevelItem::NONE) {
      Mix_PlayChannel(1, ResourceManager::getInstance().getChunk(mSoundPath),
                      0);
      updateCurrentLevel(mLevelData, Vector2D<int>(j, i), Vector2D<int>(y - xOffset, x), currentlySelected);
      refreshLevelEditor();
    }
  };

  auto levelGrid = std::make_shared<GridObject>(*this, xOffset, 0, 20, 20, 64,
                                                64);
  levelGrid->setGridCallBack(gridCallback);
  addObject(levelGrid);
  refreshLevelEditor();
}

std::string TdLevelEditor::getTdBlockPath(
    TdLevelItem item) {
  switch (item) {
    case TdLevelItem::PLAINBLOCK:
      return "TD2D/Sprites/Tiles/Empty.png";
    case TdLevelItem::PATHBLOCK0:
      return "TD2D/Sprites/Tiles/Road0.png";
    case TdLevelItem::PATHBLOCK1:
      return "TD2D/Sprites/Tiles/Road1.png";
    case TdLevelItem::PATHBLOCK2:
      return "TD2D/Sprites/Tiles/Road2.png";
    case TdLevelItem::PATHBLOCK3:
      return "TD2D/Sprites/Tiles/Road3.png";
    case TdLevelItem::PATHBLOCK4:
      return "TD2D/Sprites/Tiles/Road4.png";
    case TdLevelItem::PATHBLOCK5:
      return "TD2D/Sprites/Tiles/Road5.png";
    case TdLevelItem::PATHBLOCK6:
      return "TD2D/Sprites/Tiles/Road6.png";
    case TdLevelItem::PATHBLOCK7:
      return "TD2D/Sprites/Tiles/Road7.png";
    case TdLevelItem::PATHBLOCK8:
      return "TD2D/Sprites/Tiles/Road8.png";
    case TdLevelItem::PATHBLOCK9:
      return "TD2D/Sprites/Tiles/Road9.png";
    case TdLevelItem::PATHBLOCKA:
      return "TD2D/Sprites/Tiles/RoadA.png";
    case TdLevelItem::PLACETOWER:
      return "TD2D/Sprites/Towers/BuildingPlace.png";
    case TdLevelItem::START:
      return "TD2D/Sprites/Gizmos/SpawnPointGizmo.png";
    case TdLevelItem::END:
      return "TD2D/Sprites/Gizmos/CapturePointGizmo.png";
    case TdLevelItem::BUSH1:
      return "TD2D/Sprites/Environment/Bush 1.png";
    case TdLevelItem::BUSH2:
      return "TD2D/Sprites/Environment/Bush 2.png";
    case TdLevelItem::BUSH3:
      return "TD2D/Sprites/Environment/Bush 3.png";
    case TdLevelItem::FOREST1:
      return "TD2D/Sprites/Environment/Forest 1.png";
    case TdLevelItem::GRASS1:
      return "TD2D/Sprites/Environment/Grass 1.png";
    case TdLevelItem::GRASS2:
      return "TD2D/Sprites/Environment/Grass 2.png";
    case TdLevelItem::GRASS3:
      return "TD2D/Sprites/Environment/Grass 3.png";
    case TdLevelItem::GRASS4:
      return "TD2D/Sprites/Environment/Grass 4.png";
    case TdLevelItem::STONE1:
      return "TD2D/Sprites/Environment/Stone 1.png";
    case TdLevelItem::TREE1:
      return "TD2D/Sprites/Environment/Tree 1.png";
    case TdLevelItem::TREE2:
      return "TD2D/Sprites/Environment/Tree 2.png";
    case TdLevelItem::TREE3:
      return "TD2D/Sprites/Environment/Tree 3.png";
    case TdLevelItem::TREE4:
      return "TD2D/Sprites/Environment/Tree 4.png";
    case TdLevelItem::TREE5:
      return "TD2D/Sprites/Environment/Tree 5.png";
    default:
      std::cerr << "Failed to get Tower Defense block path for item "
                << static_cast<int>(item) << std::endl;
      return "";
  }
}

void TdLevelEditor::refreshLevelEditor() {
  
  for (const auto& gameObject : getGameObjects()) {
    // Remove any blocks remaining previously
    if (gameObject->tag() == TdRockThrowerTowerTag ||
        gameObject->tag() == TdEndBlockTag ||
        gameObject->tag() == TdBlockTag ||
        gameObject->tag() == TdBGTag ||
        gameObject->tag() == TdEnemyTag ||
        gameObject->tag() == TdBulletTag ||
        gameObject->tag() == TdStartWaveButtonTag ||
        gameObject->tag() == TdEditButtonTag ||
        gameObject->tag() == TdToolbarTag ||
        gameObject->tag() == BaseTextTag)
      removeObject(gameObject);
  }

  TdLevel::initialize();
  // Strip away unwanted things for rendering in level editor
  for (const auto& gameObject : getGameObjectsToAdd()) {
    // Remove any text components (lives, level, score, etc) + Ball + Paddle +
    // Boundaries
    if (
        gameObject->tag() == TdRockThrowerTowerTag ||
        gameObject->tag() == TdEndBlockTag ||
        gameObject->tag() == TdBlockTag ||
        gameObject->tag() == TdBGTag ||
        gameObject->tag() == BaseTextTag
      ) {
        // Add an x-offset to make space for buttons
        gameObject->setX(gameObject->x() + float(xOffset));
      } else if (
        gameObject->tag() == TdEnemyTag ||
        gameObject->tag() == TdBulletTag ||
        gameObject->tag() == TdStartWaveButtonTag ||
        gameObject->tag() == TdEditButtonTag ||
        gameObject->tag() == TdToolbarTag
      ) {
        gameObject->setIsVisibleOnScreen(false);
        removeObject(gameObject);
      }
  }

  // Read in the level data for our own usage
  loadLevel(&mLevelData, getLevelNumber());
  
}
