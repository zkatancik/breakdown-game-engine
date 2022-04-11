#include "editor/BreakoutGameLevelEditor.hpp"

void BreakoutGameLevelEditor::initialize() {
  // Let the game initialize itself as it would in a normal game
  BreakoutGameLevel::initialize();
  // Update so that gameObjects are added to the list
  update();
  // Strip away unwanted things for rendering in level editor
  for (const auto& gameObject : getGameObjects()) {
    // Remove any text components (lives, level, score, etc) + Ball + Paddle +
    // Boundaries
    if (gameObject->tag() == BaseTextTag ||
        gameObject->tag() == BreakoutBallTag ||
        gameObject->tag() == BreakoutPaddleTag ||
        gameObject->tag() == BreakoutBottomWallTag ||
        gameObject->tag() == BreakoutReflectingWallTag)
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

  auto changeToErase = [&] { currentlySelected = BreakoutLevelItem::NOBLOCK; };

  auto eraseButton =
      std::make_shared<LevelEditButton>(*this, 35, 35, 74, 74, 5.f, 5.f,
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
    std::string blockName(1, (char)item);
    auto button = std::make_shared<LevelEditButton>(
        *this, x, y, 74, 42, 5.f, 5.f, getBreakoutBlockPath(blockName), mSoundPath, lambda);
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
    mGridRenderComponent =
        std::make_shared<GridRenderComponent>(*levelGrid, 64, 32, 21, 15);
    levelGrid->setRenderComponent(mGridRenderComponent);
    setGridRenderComponent(mGridRenderComponent);
    addObject(levelGrid);
  }
}