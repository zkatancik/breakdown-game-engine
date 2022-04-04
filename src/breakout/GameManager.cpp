//#include "breakout/GameManager.hpp"
//
//GameManager &GameManager::getInstance() {
//  static GameManager *instance = new GameManager();
//  return *instance;
//}
//
//void GameManager::startUp(int w, int h) {
//  screenWidth = w;
//  screenHeight = h;
//
//
////  mouse = new Mouse();
////  mouse->startUp();
////
////  startButton = new Button();
////  startButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
////                       screenHeight / 6, u8"START");
////
////  difficultyButton = new Button();
////  difficultyButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
////                            screenHeight - (screenHeight / 1.7),
////                            u8"SELECT DIFFICULTY");
////
////  languageButton = new Button();
////  languageButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
////                          screenHeight - (screenHeight / 3),
////                          u8"CHANGE LANGUAGE");
////
////  returnButton = new Button();
////  returnButton->startUp(513, 177, 510, 860, 400, 139, screenWidth / 2,
////                        screenHeight / 2 + (139 / 2), u8"RETURN");
////
////  returnButtonMenus = new Button();
////  returnButtonMenus->startUp(513, 177, 510, 860, 400, 139, screenWidth / 2,
////                             screenHeight / 2 + (139 / 2), u8"RETURN");
////
////  englishButton = new Button();
////  englishButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 3,
////                         screenHeight / 3, u8"ENGLISH");
////
////  spanishButton = new Button();
////  spanishButton->startUp(513, 177, 635, 1122, 400, 139,
////                         screenWidth - (screenWidth / 3), screenHeight / 3,
////                         u8"SPANISH");
////
////  easyButton = new Button();
////  easyButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 5,
////                      screenHeight / 3, u8"EASY");
////
////  mediumButton = new Button();
////  mediumButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
////                        screenHeight / 3, u8"MEDIUM");
////
////  hardButton = new Button();
////  hardButton->startUp(513, 177, 635, 1122, 400, 139,
////                      screenWidth - (screenWidth / 5), screenHeight / 3,
////                      u8"HARD");
////  enterButton = new Button();
////  enterButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
////                       screenHeight - (screenHeight * 2) / 7, u8"ENTER");
////
////  nextLevelButton = new Button();
////  nextLevelButton->startUp(513, 177, 635, 1122, 400, 139, screenWidth / 2,
////                           screenHeight / 10, u8"NEXT LEVEL");
////  readHighestScoreOnFile();
//}
//
////void GameManager::readHighestScoreOnFile() {
////  std::string highScoreFilePath =
////      (getResourcePath() / "2DBreakout_Files" / "highScores.txt").u8string();
////  std::fstream *highScoreFile =
////      ResourceManager::getInstance().openFile(highScoreFilePath, std::ios::in);
////  if (highScoreFile->peek() == std::ifstream::traits_type::eof()) return;
////  *highScoreFile >> highestScoreUsername >> highestScore;
////  //  highestScore = std::stoi(line.substr(line.rfind(',')));
////  ResourceManager::getInstance().closeFile(highScoreFilePath);
////}
//
////void GameManager::updateHighestScoreOnFile(const std::string &username,
////                                           int highScore) {
////  std::string highScoreFilePath =
////      (getResourcePath() / "2DBreakout_Files" / "highScores.txt").u8string();
////  std::fstream *highScoreFile =
////      ResourceManager::getInstance().openFile(highScoreFilePath, std::ios::out);
////  *highScoreFile << username << " " << highScore << std::endl;
////  ResourceManager::getInstance().closeFile(highScoreFilePath);
////}
//
//void GameManager::shutDown() {
////  delete mouse;
////  delete startButton;
////  delete returnButton;
////  delete returnButtonMenus;
////  delete languageButton;
////  delete difficultyButton;
////  delete englishButton;
////  delete spanishButton;
////  delete easyButton;
////  delete mediumButton;
////  delete hardButton;
////  delete nextLevelButton;
//}
//
//void GameManager::update() {
////  mouse->update();
//
////  if (isGameStarted()) {
////    if (!needNewBall) {
////      ball->update();
////      detectCollisions();
////    }
////
////    if (isGameEnd()) {
////      return;
////    }
////  } else if (gameState_ == GameState::PreGame) {
////    startButton->update(mouse);
////    difficultyButton->update(mouse);
////    languageButton->update(mouse);
////  } else if (gameState_ == GameState::GameEnd) {
////    nextLevelButton->update(mouse);
////    returnButton->update(mouse);
////  } else if (gameState_ == GameState::LanguageSelect) {
////    englishButton->update(mouse);
////    spanishButton->update(mouse);
////    returnButtonMenus->update(mouse);
////  } else if (gameState_ == GameState::DifficultySelect) {
////    easyButton->update(mouse);
////    mediumButton->update(mouse);
////    hardButton->update(mouse);
////    returnButtonMenus->update(mouse);
////  } else if (gameState_ == GameState::HighScoreEntry) {
////    enterButton->update(mouse);
////    nextLevelButton->update(mouse);
////  }
//}
//
//void GameManager::render(SDL_Renderer *ren) {
////  if (isGameStarted()) {
////    // Gameobjects
////    paddle->render(ren);
////    if (!needNewBall) {
////      ball->render(ren);
////    }
////    for (auto &&block : blockList) {
////      block.render(ren);
////    }
////  } else if (gameState_ == GameState::PreGame) {
////    // Pregame UI
////    startButton->render(ren);
////    difficultyButton->render(ren);
////    languageButton->render(ren);
////  } else if (gameState_ == GameState::GameEnd) {
////    // End game UI
////    returnButton->render(ren);
////    nextLevelButton->render(ren);
////  } else if (gameState_ == GameState::LanguageSelect) {
////    englishButton->render(ren);
////    spanishButton->render(ren);
////    returnButtonMenus->render(ren);
////  } else if (gameState_ == GameState::DifficultySelect) {
////    easyButton->render(ren);
////    mediumButton->render(ren);
////    hardButton->render(ren);
////    returnButtonMenus->render(ren);
////  } else if (gameState_ == GameState::HighScoreEntry) {
////    enterButton->render(ren);
////    nextLevelButton->render(ren);
////  }
////  // Mouse should be last as it should be drawn over everything.
////  mouse->render(ren);
//}
//
//
////std::string GameManager::getLevel() {
//////  return ResourceManager::getInstance().getTranslation(u8"Level", language_) +
//////         " " + std::to_string(level);
////}
////
////std::string GameManager::getScore() {
////  return ResourceManager::getInstance().getTranslation(u8"Score", language_) +
////         " " + std::to_string(score);
////}
//
////std::string GameManager::getLives() {
////  return ResourceManager::getInstance().getTranslation(u8"Lives", language_) +
////         " " + std::to_string(lives);
////}
//
////std::string GameManager::getHighScore() {
////  return ResourceManager::getInstance().getTranslation(u8"Highest Ever",
////                                                       language_) +
////         " " + std::to_string(highestScore);
////}
////
////std::string GameManager::getTranslation(const std::string &s) {
////  return ResourceManager::getInstance().getTranslation(s, language_);
////}
//
//
//
//void GameManager::reduceLife() {
//  if (lives > 0) {
//    lives--;
//    Mix_PlayChannel(
//        1, ResourceManager::getInstance().getChunk("LifeLost_SFX.mp3"), 0);
//    // Reset ball position and resume game.
//    delete ball;
//    needNewBall = true;
//    needNewBallTicks = SDL_GetTicks();
//  }
//}
//
//
//void GameManager::clearBlock() {
//  auto i = std::begin(blockList);
//
//  if (i != std::end(blockList)) {
//
//    BlockType t = i->getBlockData().block_Type;
//
//    std::cout << "Clearing " << std::to_string(t) << "\n" ;
//    blockList.erase(i);
//    std::cout << "Cleared " << std::to_string(t) << "\n" ;
//
//    if (t != BlockType::Wall && t != BlockType::HardBlock) {
//      score++;
//    }
//
//    Mix_PlayChannel(
//        1, ResourceManager::getInstance().getChunk("BrickHit_SFX.mp3"), 0);
//  }
//}
//
//void GameManager::clearBlock(std::vector<Block>::iterator i) {
//  BlockType t = i->getBlockData().block_Type;
//
//  if (t == BlockType::NoBlock) {
//    return;
//  }
//
//  if (t == BlockType::PlainBlock) {
//    Mix_PlayChannel(
//        1, ResourceManager::getInstance().getChunk("BrickHit_SFX.mp3"), 0);
//  } else if (t == BlockType::Wall) {
//    Mix_PlayChannel(
//        1, ResourceManager::getInstance().getChunk("WallBrickHit_SFX.wav"), 0);
//  } else if (t == BlockType::HardBlock) {
//    Mix_PlayChannel(
//        1, ResourceManager::getInstance().getChunk("BrickCrack_SFX.wav"), 0);
//  }
//
//  if (i->reduceHealth()) {
//    if (t == BlockType::PlainBlock) {
//      blockList.erase(i);
//      score++;
//    } else if (t == BlockType::HardBlock) {
//      blockList.erase(i);
//      score = score + 3;
//    }
//  }
//}
//
//void GameManager::stopBall() {
//  if (isGameStarted()) {
//    ball->stop();
//  }
//}
//
//void GameManager::stopPaddle() {
//  if (isGameStarted()) {
//    paddle->stop();
//  }
//}
//
//void GameManager::detectCollisions() {
//  bool vBounceDetected = false;
//  bool hBounceDetected = false;
//  Vector2D ballPos = ball->getPosition();
//  // Collision checking with the walls
//  // The asymmetry below is because the pos is the top left corner of a
//  // rectangle around the ball image
//  if (ballPos.y >= screenHeight - ball->BALL_HEIGHT / 2) {
//    reduceLife();
//    if (isGameEnd() || needNewBall) {
//      return;
//    }
//  } else if (ballPos.x <= ball->BALL_WIDTH / 2 ||
//             ballPos.x >= screenWidth - ball->BALL_WIDTH / 2) {
//    vBounceDetected = true;
//  } else if (ballPos.y <= ball->BALL_WIDTH / 2 ||
//             ballPos.y >= screenHeight - ball->BALL_HEIGHT / 2) {
//    hBounceDetected = true;
//  }
//  // Collision checking with the paddle
//  auto paddleCollVector = detect_collision(*paddle, *ball);
//  auto paddleBallCenterVector = ball->getPosition() - paddle->getCenter();
//  auto ballVel = ball->getVelocity();
//  auto intBallVel = Vector2D<int>(ballVel.x, ballVel.y);
//  bool isBallMovingTowardsPaddle =
//      Magnitude(paddleBallCenterVector + intBallVel) <=
//      Magnitude(paddleBallCenterVector) + 3;
//  if (paddleCollVector.x != 0 && isBallMovingTowardsPaddle) {
//    Mix_PlayChannel(
//        0, ResourceManager::getInstance().getChunk("PaddleBorderHit_SFX.mp3"),
//        0);
//    hBounceDetected = true;
//
//    if (!(paddle->getVelocity() == Vector2D<int>(0, 0))) {
//      Vector2D<int> paddleVel = paddle->getVelocity();
//      auto paddleContribution =
//          Vector2D<float>(paddleVel.x / 2.0f, paddleVel.y / 2.0f);
//      // (scaled) paddle velocity contributes to ball velocity
//      ball->nudgeVelocity(paddleContribution);
//    }
//  }
//
//  if (paddleCollVector.y != 0 && isBallMovingTowardsPaddle) {
//    Mix_PlayChannel(
//        0, ResourceManager::getInstance().getChunk("PaddleBorderHit_SFX.mp3"),
//        0);
//    vBounceDetected = true;
//  }
//
//  // Collision checking with the blocks
//  blocksLeft = false;
//  int recalc = 0;
//  for (std::vector<Block>::iterator block = blockList.begin();
//       block != blockList.end();) {
//    auto blockCollVector = detect_collision(*block, *ball);
//
//    // Check if there are still plain blocks left.
//    if (block->getBlockData().block_Type == BlockType::PlainBlock) {
//      blocksLeft = true;
//    }
//
//    if (blockCollVector.x != 0) {
//      hBounceDetected = true;
//      clearBlock(block);
//      if (block->getBlockData().block_Type == BlockType::HardBlock) {
//        block++;
//        recalc = 0;
//      }
//
//    } else if (blockCollVector.y != 0) {
//      vBounceDetected = true;
//
//      clearBlock(block);
//
//      if (block->getBlockData().block_Type == BlockType::HardBlock) {
//        block++;
//        recalc = 0;
//      }
//
//    } else {
//      block++;
//      recalc = 0;
//    }
//
//    recalc++;
//    if (recalc == 4) block++;
//  }
//
//  // Quick and dirty "debouncing" of ball collisions
//  static int ctr = 0;
//  const int kThreshold = 5;
//  if (ctr % kThreshold == 0) {
//    if (vBounceDetected) {
//      ball->bounceVWall();
//      ctr++;
//    }
//    if (hBounceDetected) {
//      ball->bounceHWall();
//      ctr++;
//    }
//  } else {
//    ctr++;
//  }
//  if (!vBounceDetected && !hBounceDetected) {
//    ctr = 0;
//  }
//}
//
//void GameManager::startGame() {
//
//}
//
//GameManager::GameState GameManager::getGameState() { return gameState_; }
//
//// TODO: Move this to a UIManager.
//void GameManager::checkButtons() {
//  if (startButton->IsSelected()) {
//    startButton->isClicked();
//    startGame();
//    gameState_ = GameState::InGame;
//  } else if (returnButton->IsSelected()) {
//    returnButton->isClicked();
//    gameState_ = GameState::PreGame;
//    clearLevel();
//  } else if (languageButton->IsSelected()) {
//    languageButton->isClicked();
//    gameState_ = GameState::LanguageSelect;
//  } else if (difficultyButton->IsSelected()) {
//    difficultyButton->isClicked();
//    gameState_ = GameState::DifficultySelect;
//  } else if (returnButtonMenus->IsSelected()) {
//    returnButtonMenus->isClicked();
//    gameState_ = GameState::PreGame;
//  } else if (englishButton->IsSelected()) {
//    englishButton->isClicked();
//    language_ = Language::ENGLISH;
//    startButton->changeLanguage(language_);
//    difficultyButton->changeLanguage(language_);
//    returnButton->changeLanguage(language_);
//    returnButtonMenus->changeLanguage(language_);
//    languageButton->changeLanguage(language_);
//    englishButton->changeLanguage(language_);
//    spanishButton->changeLanguage(language_);
//    easyButton->changeLanguage(language_);
//    mediumButton->changeLanguage(language_);
//    hardButton->changeLanguage(language_);
//    enterButton->changeLanguage(language_);
//  } else if (spanishButton->IsSelected()) {
//    spanishButton->isClicked();
//    language_ = Language::SPANISH;
//    startButton->changeLanguage(language_);
//    difficultyButton->changeLanguage(language_);
//    returnButton->changeLanguage(language_);
//    returnButtonMenus->changeLanguage(language_);
//    languageButton->changeLanguage(language_);
//    englishButton->changeLanguage(language_);
//    spanishButton->changeLanguage(language_);
//    easyButton->changeLanguage(language_);
//    mediumButton->changeLanguage(language_);
//    hardButton->changeLanguage(language_);
//    enterButton->changeLanguage(language_);
//  } else if (easyButton->IsSelected()) {
//    easyButton->isClicked();
//    gameDifficulty_ = GameDifficulty::Easy;
//    gameState_ = GameState::PreGame;
//  } else if (mediumButton->IsSelected()) {
//    mediumButton->isClicked();
//    gameDifficulty_ = GameDifficulty::Medium;
//    gameState_ = GameState::PreGame;
//  } else if (hardButton->IsSelected()) {
//    hardButton->isClicked();
//    gameDifficulty_ = GameDifficulty::Hard;
//    gameState_ = GameState::PreGame;
//  } else if (enterButton->IsSelected()) {
//    highestScore = score;
//    enterButton->isClicked();
//    clearLevel();
//    updateHighestScoreOnFile(highestScoreUsername, highestScore);
//    gameState_ = GameState::PreGame;
//  } else if (nextLevelButton->IsSelected()) {
//    nextLevelButton->isClicked();
//    startGame();
//    gameState_ = GameState::InGame;
//  }
//}
//
//bool GameManager::isGameStarted() { return (gameState_ == GameState::InGame); }
//
//void GameManager::clearLevel() {
//  // Clear Level.
//
//  score = 0;
//  lives = livesPerGame;
//
//  delete paddle;
//  blockList.clear();
//}
//
//void GameManager::setGameState(GameState gs) { gameState_ = gs; }
//
//bool GameManager::isGameWon() {
//  // TODO: Game win has to be better coded.
//  return (score >= numBlocks) && (lives > 0);
//}
//
//bool GameManager::isGameEnd() {
//  if (getLivesVal() == 0 || (!blocksLeft) || blockList.empty()) {
//    needNewBall = false;
//    gameState_ =
//        score > highestScore ? GameState::HighScoreEntry : GameState::GameEnd;
//
//    if (isGameWon()) {
//      updateLevel();
//
//      Mix_PlayChannel(
//          1, ResourceManager::getInstance().getChunk("GameWin_SFX.wav"), 0);
//    } else {
//      Mix_PlayChannel(
//          1, ResourceManager::getInstance().getChunk("GameOver_SFX.mp3"), 0);
//    }
//
//    return true;
//  }
//
//  return false;
//}
//
//void GameManager::updateLevel() {
//  if (level < MAX_LEVEL) {
//    level++;
//  } else {
//    // Reset levels after all are passed.
//    level = 1;
//  }
//}
//
//std::string GameManager::getLevelEndMessage() {
//  return isGameWon() ? ResourceManager::getInstance().getTranslation(
//                           u8"LEVEL CLEARED!", language_)
//                     : ResourceManager::getInstance().getTranslation(
//                           u8"YOU LOST", language_);
//}
//
//bool GameManager::isNeedNewBall() { return needNewBall; }
//
//void GameManager::spawnNewBall() {
//  if (gameDifficulty_ == GameDifficulty::Easy) {
//    ball = new Ball(100, 75, EASY_BALL_X, EASY_BALL_Y);
//  }
//  if (gameDifficulty_ == GameDifficulty::Medium) {
//    ball = new Ball(100, 75, MEDIUM_BALL_X, MEDIUM_BALL_Y);
//  }
//  if (gameDifficulty_ == GameDifficulty::Hard) {
//    ball = new Ball(100, 75, HARD_BALL_X, HARD_BALL_Y);
//  }
//  needNewBall = false;
//}
//
//int GameManager::getNeedNewBallTicks() { return needNewBallTicks; }
