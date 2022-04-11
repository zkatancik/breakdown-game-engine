#include "editor/GraveRunnerLevelEditor.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/Tag.hpp"

void GraveRunnerLevelEditor::initialize() {
  // Let the game initialize itself as it would in a normal game
  GraveRunnerLevel::initialize();
  // Update so that gameObjects are added to the list
  update();
  // Strip away unwanted things for rendering in level editor
  for (const auto& gameObject : getGameObjects()) {
    // Remove boundaries and bullets
    if (gameObject->tag() == GraveRunnerLevelBoundaryTag ||
        gameObject->tag() == GraveRunnerBulletTag)
      removeObject(gameObject);
    // Add an x-offset to make space for buttons
    gameObject->setX(gameObject->x() + float(xOffset));
  }
  update();
  // Read in the level data for our own usage
  loadLevel(&mLevelData, getLevelNumber());

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

  auto changeToErase = [&] { currentlySelected = GraveRunnerLevelItem::NOBLOCK; };

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
        *this, x, y, 74, 42, 5.f, 5.f, getGraverunnerBlockPath(item),
        mSoundPath, lambda);
    addObject(button);
    x = x + 79;
    count++;
    if (count == 2) {
      y = y + 47;
      x = 26;
      count = 0;
    }

    // Grid component here
    auto levelGrid =
        std::make_shared<GameObject>(*this, xOffset, 0, 20 * 64, 20 * 32, 44);
//    mGridRenderComponent = std::make_shared<GridRenderComponent>(
//        *this, *levelGrid, 64, 32, 20, 15);
//    levelGrid->setRenderComponent(mGridRenderComponent);
//    setGridRenderComponent(mGridRenderComponent);
    addObject(levelGrid);
  }
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
