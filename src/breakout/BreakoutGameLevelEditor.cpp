#include "breakout/BreakoutGameLevelEditor.hpp"

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

  auto changeLanguageToEnglish = [&] {};

  // Add the English button
  addObject(std::make_shared<LevelEditButton>(*this, 100, 100, 100, 100,
                                              changeLanguageToEnglish));

  // Add buttons here:
  // w and h where the buttons are going to be placed
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      // Lambda to set global state.
      // auto editorButton = std::make_shared<EditorButton>(*this, the texutre,
      // the block data, lambda) addObject(editorButton);
    }
  }

  // Grid component here
  // The lambda should check for currently selected button, and overwrite.
  // Render over is also nice to have.

  // auto mHoverChangeFocus = [&]() { buttonRenderer->setCrop(mCropFocused); };
  // auto mNotSelectChangeFocus = [&]() {
  //   buttonRenderer->setCrop(mCropNotFocused);
  // };

  // auto addedSoundWithSelectHook = [selectHook = std::move(selectHook)] {
  //   Mix_PlayChannel(1,
  //                   ResourceManager::getInstance().getChunk(
  //                       "Graverunner/2DPlatformer_SFX/"
  //                       "mixkit-video-game-mystery-alert-234.wav"),
  //                   0);
  //   selectHook();
  // };
  // textRenderer = std::make_shared<TextureRenderComponent>(
  //     *this, std::vector({buttonRenderer}));

  // textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);

  // setRenderComponent(textRenderer);

  // textComponent = std::make_shared<TextComponent>(*this, text, mFontSize,
  //                                                 mButtonFont, textRenderer);
  // addGenericComponent(textComponent);

  // addGenericComponent(std::make_shared<CenterTextComponent>(
  //     *this, textRenderer, this->x(), this->y()));

  // textRenderer->setOffSetY(int(60));

  // auto selectableComponent = std::make_shared<SelectableComponent>(
  //     *this, addedSoundWithSelectHook, mHoverChangeFocus,
  //     mNotSelectChangeFocus);
  // addGenericComponent(selectableComponent);
}