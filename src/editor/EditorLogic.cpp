#include "editor/EditorLogic.hpp"


void EditorLogic::startUp(SDL_Renderer *gRender, int width, int height) {
  createAndInitStartMenu(width, height);
  createAndInitBreakoutLevelSelector(width, height);
  createAndInitGraveRunnerSelector(width, height);
  mCurrentlyActiveLevel = mStartMenu;
}
void EditorLogic::update() {
  mCurrentlyActiveLevel->update();
}

void EditorLogic::render(SDL_Renderer *renderer) {
  mCurrentlyActiveLevel->render(renderer);
}


void EditorLogic::shutDown() {
  mStartMenu->finalize();
  mBreakOutLevelSelector->finalize();
  mGraveRunnerLevelSelector->finalize();
}


void EditorLogic::createAndInitStartMenu(int width, int height) {
  mStartMenu = std::make_shared<Level>(width, height);
  // Create the select Game message
  auto gameSelectMessage = std::make_shared<TextMessageObject>(*mStartMenu,
                                                               "Select Game:",
                                                               width / 2 - 200, height / 5,
                                                               "2DBreakout/Fonts/Gageda.ttf",
                                                               64);
  mStartMenu->addObject(gameSelectMessage);
  // Create buttons for each Game

  // Breakout Button
  auto breakoutButton = std::make_shared<BreakoutButton>(*mStartMenu, width * 0.4, height / 2,
                                                         2 * width / 3, 139, BreakoutButton::Color::GREEN,
                                                         "Breakout",
                                                         [&](){mCurrentlyActiveLevel = mBreakOutLevelSelector;});
  mStartMenu->addObject(breakoutButton);
  // Graverunner Button
  auto gRunnerButton = std::make_shared<GraveRunnerButton>(*mStartMenu, width * 1.5, height / 2 - 20,
                                                           2 * width / 3, 139, "GraveRunner",
                                                           [&](){mCurrentlyActiveLevel = mGraveRunnerLevelSelector;});
  mStartMenu->addObject(gRunnerButton);
}

void EditorLogic::createAndInitBreakoutLevelSelector(int width, int height) {
  mBreakOutLevelSelector = std::make_shared<Level>(width, height);
}
void EditorLogic::createAndInitGraveRunnerSelector(int width, int height) {
  mGraveRunnerLevelSelector = std::make_shared<Level>(width, height);
}



