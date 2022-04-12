#include "editor/BreakoutGameLevelEditor.hpp"

#include "base/GridObject.hpp"

void BreakoutGameLevelEditor::initialize() {
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
    std::string blockName(1, (char)item);
    auto button = std::make_shared<LevelEditButton>(
        *this, x, y, 74, 42, 5.f, 5.f, getBreakoutBlockPath(blockName),
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
    auto gridCallback = [&, mLevelData = &mLevelData](int i, int j) {
      if (currentlySelected != BreakoutLevelItem::NONE) {
        Mix_PlayChannel(1, ResourceManager::getInstance().getChunk(mSoundPath),
                        0);
        updateCurrentLevel(mLevelData, Vector2D<int>(i, j), currentlySelected);
        refreshLevelEditor();
        //currentlySelected = BreakoutLevelItem::NONE;
      }
    };

    auto levelGrid = std::make_shared<GridObject>(*this, xOffset, 0, 20, 15, 64,
                                                  32, gridCallback);
    addObject(levelGrid);
  }
  refreshLevelEditor();
}
void BreakoutGameLevelEditor::refreshLevelEditor() {
  for (const auto& gameObject : getGameObjects()) {
    // Remove any blocks remaining previously
    if (gameObject->tag() == BreakoutBlockTag ||
        gameObject->tag() == BaseTextTag ||
        gameObject->tag() == BreakoutBallTag ||
        gameObject->tag() == BreakoutPaddleTag ||
        gameObject->tag() == BreakoutBottomWallTag ||
        gameObject->tag() == BreakoutReflectingWallTag)
      removeObject(gameObject);
  }
  BreakoutGameLevel::initialize();
  // Strip away unwanted things for rendering in level editor
  for (const auto& gameObject : getGameObjectsToAdd()) {
    // Remove any text components (lives, level, score, etc) + Ball + Paddle +
    // Boundaries
    if (gameObject->tag() == BaseTextTag ||
        gameObject->tag() == BreakoutBallTag ||
        gameObject->tag() == BreakoutPaddleTag ||
        gameObject->tag() == BreakoutBottomWallTag ||
        gameObject->tag() == BreakoutReflectingWallTag ||
        gameObject->tag() == BreakoutBlockTag)
      // Add an x-offset to make space for buttons
      gameObject->setX(gameObject->x() + float(xOffset));
  }
  // Read in the level data for our own usage
  loadLevel(&mLevelData, getLevelNumber());
}
