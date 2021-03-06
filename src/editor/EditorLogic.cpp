#include "editor/EditorLogic.hpp"

void EditorLogic::startUp(SDL_Renderer *gRender, int width, int height) {
  createAndInitStartMenu(width, height);
  createAndInitBreakoutLevelSelector(width, height);
  createAndInitGraveRunnerSelector(width, height);
  createAndInitTdSelector(width, height);
  createBreakoutLevelEditors(width, height);
  createGraveRunnerLevelEditors(width, height);
  createTdLevelEditors(width, height);
  mCurrentlyActiveLevel = mStartMenu;
}
void EditorLogic::update() {
  mCurrentlyActiveLevel->update();
  framerateModerator();
}

void EditorLogic::render(SDL_Renderer *renderer) {
  mCurrentlyActiveLevel->render(renderer);
}

void EditorLogic::shutDown() {
  mStartMenu->finalize();
  mBreakOutLevelSelector->finalize();
  mGraveRunnerLevelSelector->finalize();
  mTowerDefenceLevelSelector->finalize();
  for (auto l : mBreakoutLevelEditors) l->finalize();
  for (auto l : mGraveRunnerLevelEditors) l->finalize();
  for (auto l : mTowerDefenseLevelEditors) l->finalize();
}

void EditorLogic::createAndInitStartMenu(int width, int height) {
  mStartMenu = std::make_shared<Level>(width, height);
  // Create the select Game message
  auto gameSelectMessage = std::make_shared<TextMessageObject>(
      *mStartMenu, u8"Select Game:", width / 2 - 200, height / 5,
      "2DBreakout/Fonts/Gageda.ttf", 64);
  mStartMenu->addObject(gameSelectMessage);
  // Create buttons for each Game

  // Breakout Button
  auto breakoutButton = std::make_shared<BreakoutButton>(
      *mStartMenu, width * 0.4, height / 2, 2 * width / 3, 139,
      BreakoutButton::Color::GREEN, u8"Breakout",
      [&]() { mCurrentlyActiveLevel = mBreakOutLevelSelector; });
  mStartMenu->addObject(breakoutButton);
  // Graverunner Button
  auto gRunnerButton = std::make_shared<GraveRunnerButton>(
      *mStartMenu, width * 1.5, height / 2 - 20, 2 * width / 3, 139,
      u8"GraveRunner",
      [&]() { mCurrentlyActiveLevel = mGraveRunnerLevelSelector; });
  mStartMenu->addObject(gRunnerButton);
  // Tower defense Button
  auto tDefenseButton = std::make_shared<TdButton>(
      *mStartMenu, width, height / 2 + 180, 2 * width / 3, 139,
      u8"Tower Defense",
      [&]() { mCurrentlyActiveLevel = mTowerDefenceLevelSelector; }, 32);
  mStartMenu->addObject(tDefenseButton);
}

void EditorLogic::createAndInitBreakoutLevelSelector(int width, int height) {
  mBreakOutLevelSelector = std::make_shared<Level>(width, height);
  // Create the select level message
  auto gameSelectMessage = std::make_shared<TextMessageObject>(
      *mBreakOutLevelSelector, u8"Select Level:", width / 2 - 150, height / 5,
      "2DBreakout/Fonts/Gageda.ttf", 64);
  mBreakOutLevelSelector->addObject(gameSelectMessage);
  // Level numbers button
  for (size_t i = 0; i < mBreakoutLevelEditors.size(); i++) {
    auto breakoutButton = std::make_shared<BreakoutButton>(
        *mBreakOutLevelSelector, width * 0.4 + i * (width * 0.4), height / 2,
        2 * width / 3, 139, BreakoutButton::Color::GREEN, std::to_string(i + 1),
        [=]() {
          mBreakoutLevelEditors[i]->finalize();
          mBreakoutLevelEditors[i]->initialize();
          auto returnButton = std::make_shared<BreakoutButton>(
              *mBreakoutLevelEditors[i], 200, 640, 2 * width / 3, 50,
              BreakoutButton::Color::RED, u8"Return",
              [&]() { mCurrentlyActiveLevel = mStartMenu; }, 40);
          mBreakoutLevelEditors[i]->addObject(returnButton);
          mCurrentlyActiveLevel = mBreakoutLevelEditors[i];
        });
    mBreakOutLevelSelector->addObject(breakoutButton);
  }

  // Back button
  auto returnButton = std::make_shared<BreakoutButton>(
      *mBreakOutLevelSelector, width * 1.0 - 25, height * 0.7, 2 * width / 3,
      139, BreakoutButton::Color::RED, u8"Return",
      [&]() { mCurrentlyActiveLevel = mStartMenu; });
  mBreakOutLevelSelector->addObject(returnButton);
}

void EditorLogic::createAndInitGraveRunnerSelector(int width, int height) {
  mGraveRunnerLevelSelector = std::make_shared<Level>(width, height);
  // Create the select level message
  auto gameSelectMessage = std::make_shared<TextMessageObject>(
      *mGraveRunnerLevelSelector, u8"Select Level:", width / 2 - 150, height / 5,
      "Graverunner/fonts/GADAQUALI.ttf", 64);
  mGraveRunnerLevelSelector->addObject(gameSelectMessage);
  // Level numbers button
  for (size_t i = 0; i < mGraveRunnerLevelEditors.size(); i++) {
    auto graverunnerButton = std::make_shared<GraveRunnerButton>(
        *mGraveRunnerLevelSelector, width * 0.6 + i * (width * 0.4), height / 2,
        2 * width / 3, 139, std::to_string(i + 1), [=]() {
          mGraveRunnerLevelEditors[i]->finalize();
          mGraveRunnerLevelEditors[i]->initialize();
          auto returnButton = std::make_shared<GraveRunnerButton>(
              *mGraveRunnerLevelSelector, 200, 640, 2 * width / 3, 40, "Return",
              [&]() { mCurrentlyActiveLevel = mStartMenu; });
          mGraveRunnerLevelEditors[i]->addObject(returnButton);
          mCurrentlyActiveLevel = mGraveRunnerLevelEditors[i];
        });
    mGraveRunnerLevelSelector->addObject(graverunnerButton);
  }

  // Back button
  auto returnButton = std::make_shared<GraveRunnerButton>(
      *mGraveRunnerLevelSelector, width * 1.0 - 25, height * 0.7, 2 * width / 3,
      139, u8"Return", [&]() { mCurrentlyActiveLevel = mStartMenu; });
  mGraveRunnerLevelSelector->addObject(returnButton);
}

void EditorLogic::createAndInitTdSelector(int width, int height) {
  mTowerDefenceLevelSelector = std::make_shared<Level>(width, height);
  // Create the select level message
  auto gameSelectMessage = std::make_shared<TextMessageObject>(
      *mTowerDefenceLevelSelector, u8"Select Level:", width / 2 - 150, height / 5,
      "Graverunner/fonts/GADAQUALI.ttf", 64);
  mTowerDefenceLevelSelector->addObject(gameSelectMessage);
  // Level numbers button
  for (size_t i = 0; i < mTowerDefenseLevelEditors.size(); i++) {
    // Add map editor level select buttons
    auto tdButtonMap = std::make_shared<TdButton>(
        *mTowerDefenceLevelSelector, width * 0.4 + i * (width * 0.4), height / 3,
        2 * width / 3, 139, std::to_string(i + 1) + " map", [=]() {
          mTowerDefenseLevelEditors[i]->finalize();
          mTowerDefenseLevelEditors[i]->initialize();
          auto returnButton = std::make_shared<TdButton>(
              *mTowerDefenceLevelSelector, 200, 670, 2 * width / 5, 12, u8"Return",
              [&]() { mCurrentlyActiveLevel = mStartMenu; }, 15);
          mTowerDefenseLevelEditors[i]->addObject(returnButton);
          mCurrentlyActiveLevel = mTowerDefenseLevelEditors[i];
        }, 32);
    mTowerDefenceLevelSelector->addObject(tdButtonMap);
    // Add enemy editor select buttons
    auto tdButtonEnemy = std::make_shared<TdButton>(
        *mTowerDefenceLevelSelector, width * 0.4 + i * (width * 0.4), height / 3 + 150,
        2 * width / 3, 139, std::to_string(i + 1) + " enemies", [=]() {
          mTowerDefenseEnemyEditors[i]->finalize();
          mTowerDefenseEnemyEditors[i]->initialize();
          auto returnButton = std::make_shared<TdButton>(
              *mTowerDefenceLevelSelector, 200, 670, 2 * width / 5, 12, u8"Return",
              [&]() { mCurrentlyActiveLevel = mStartMenu; }, 15);
          mTowerDefenseEnemyEditors[i]->addObject(returnButton);
          mCurrentlyActiveLevel = mTowerDefenseEnemyEditors[i];
        }, 32);
    mTowerDefenceLevelSelector->addObject(tdButtonEnemy);

  }

  // Back button
  auto returnButton = std::make_shared<TdButton>(
      *mTowerDefenceLevelSelector, width * 1.0 - 25, height * 0.7, 2 * width / 3,
      139, u8"Return", [&]() { mCurrentlyActiveLevel = mStartMenu; }, 32);
  mTowerDefenceLevelSelector->addObject(returnButton);
}

void EditorLogic::createBreakoutLevelEditors(int width, int height) {
  for (size_t i = 0; i < mBreakoutLevelEditors.size(); i++) {
    mBreakoutLevelEditors[i] =
        std::make_shared<BreakoutGameLevelEditor>(width, height, i + 1);
  }
}

void EditorLogic::createGraveRunnerLevelEditors(int width, int height) {
  for (size_t i = 0; i < mGraveRunnerLevelEditors.size(); i++) {
    mGraveRunnerLevelEditors[i] =
        std::make_shared<GraveRunnerLevelEditor>(width, height, i + 1);
  }
}

void EditorLogic::createTdLevelEditors(int width, int height) {
  for (size_t i = 0; i < mTowerDefenseLevelEditors.size(); i++) {
    mTowerDefenseLevelEditors[i] =
        std::make_shared<TdLevelEditor>(width, height, i + 1);
  }
  for (size_t i = 0; i < mTowerDefenseLevelEditors.size(); i++) {
    mTowerDefenseEnemyEditors[i] =
        std::make_shared<TdEnemyEditor>(width, height, i + 1);
  }
}