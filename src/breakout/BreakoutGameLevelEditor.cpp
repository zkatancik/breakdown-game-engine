#include "breakout/BreakoutGameLevelEditor.hpp"

void BreakoutGameLevelEditor::initialize() {
  // Let the game initialize itself as it would in a normal game
  BreakoutGameLevel::initialize();
  // Update so that gameObjects are added to the list
  update();
  // Strip away unwanted things for rendering in level editor
  for (const auto& gameObject : getGameObjects()) {
    // Remove any text components (lives, level, score, etc) + Ball + Paddle + Boundaries
    if (gameObject->tag() == BaseTextTag || gameObject->tag() == BreakoutBallTag || gameObject->tag() == BreakoutPaddleTag ||
        gameObject->tag() == BreakoutBottomWallTag || gameObject->tag() == BreakoutReflectingWallTag)
      removeObject(gameObject);
    // Add an x-offset to make space for buttons
    gameObject->setX(gameObject->x() + float(xOffset));
  }
  update();
  // Read in the level data for our own usage
  loadLevel(&mLevelData, getLevelNumber());
  // Add buttons here:
  // w and h where the buttons are going to be placed
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      // Lambda to set global state.
      // auto editorButton = std::make_shared<EditorButton>(*this, the texutre, the block data, lambda)
      // addObject(editorButton);
    }
  }

  // Grid component here
  // The lambda should check for currently selected button, and overwrite. Render over is also nice to have.
}