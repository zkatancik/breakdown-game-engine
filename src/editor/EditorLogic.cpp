#include "editor/EditorLogic.hpp"


void EditorLogic::startUp(SDL_Renderer *gRender, int width, int height) {
  createAndInitStartMenu(width, height);
  createAndInitBreakoutLevelSelector(width, height);
  createAndInitGraveRunnerSelector(width, height);
  createBreakoutLevelEditors(width, height);
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
  for (auto l : mBreakoutLevelEditors)
    l->finalize();
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
  // Create the select level message
  auto gameSelectMessage = std::make_shared<TextMessageObject>(*mBreakOutLevelSelector,
                                                               "Select Level:",
                                                               width / 2 - 150, height / 5,
                                                               "2DBreakout/Fonts/Gageda.ttf",
                                                               64);
  mBreakOutLevelSelector->addObject(gameSelectMessage);
  // Level numbers button
  for (size_t i = 0; i < mBreakoutLevelEditors.size(); i++) {
    auto breakoutButton = std::make_shared<BreakoutButton>(*mBreakOutLevelSelector, width * 0.4 + i * (width * 0.4), height / 2,
                                                           2 * width / 3, 139, BreakoutButton::Color::GREEN,
                                                           std::to_string(i + 1),
                                                           [=](){
      mBreakoutLevelEditors[i]->finalize();
      mBreakoutLevelEditors[i]->initialize();
      mCurrentlyActiveLevel = mBreakoutLevelEditors[i];
    });
    mBreakOutLevelSelector->addObject(breakoutButton);
  }

  // Back button
  auto returnButton = std::make_shared<BreakoutButton>(*mBreakOutLevelSelector, width * 1.0 - 25, height * 0.7,
                                                         2 * width / 3, 139, BreakoutButton::Color::RED,
                                                         "Return",
                                                         [&](){mCurrentlyActiveLevel = mStartMenu;});
  mBreakOutLevelSelector->addObject(returnButton);
}
void EditorLogic::createAndInitGraveRunnerSelector(int width, int height) {
  mGraveRunnerLevelSelector = std::make_shared<Level>(width, height);
  // Create the select level message
  auto gameSelectMessage = std::make_shared<TextMessageObject>(*mGraveRunnerLevelSelector,
                                                               "Select Level:",
                                                               width / 2 - 200, height / 5,
                                                               "Graverunner/fonts/GADAQUALI.ttf",
                                                               64);
  mGraveRunnerLevelSelector->addObject(gameSelectMessage);
  // Level numbers button
  for (int i = 0; i < 3; i++) {
    auto breakoutButton = std::make_shared<GraveRunnerButton>(*mGraveRunnerLevelSelector, width * 0.4 + i * (width * 0.5), height / 2,
                                                           2 * width / 3, 139,
                                                           std::to_string(i + 1),
                                                           [&](){mCurrentlyActiveLevel = mGraveRunnerLevelSelector;});
    mGraveRunnerLevelSelector->addObject(breakoutButton);
  }

  // Back button
  auto returnButton = std::make_shared<GraveRunnerButton>(*mGraveRunnerLevelSelector, width * 1.0 - 25, height * 0.7,
                                                         2 * width / 3, 139,
                                                         "Return",
                                                         [&](){mCurrentlyActiveLevel = mStartMenu;});
  mGraveRunnerLevelSelector->addObject(returnButton);

}
void EditorLogic::createBreakoutLevelEditors(int width, int height) {
  for (size_t i = 0; i < mBreakoutLevelEditors.size(); i++)
    mBreakoutLevelEditors[i] = std::make_shared<BreakoutGameLevelEditor>(width, height, i + 1);
}





