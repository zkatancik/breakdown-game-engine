#include <cxxtest/TestSuite.h>

#include "graverunner/GameManager.hpp"
#include "graverunner/ResourceManager.hpp"

class GameManagerTestSuite : public CxxTest::TestSuite {
 public:
  const float EPSILON = 0.001f;
  const int screenWidth = 1280;
  const int screenHeight = 720;
  SDL_Window* testWindow = nullptr;
  SDL_Renderer* testRenderer = nullptr;

  static GameManagerTestSuite* createSuite() {
    auto suite = new GameManagerTestSuite();
    int success = 0;
    success += SDL_Init(SDL_INIT_EVERYTHING);
    success += TTF_Init();
    success += Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TS_ASSERT_EQUALS(success, 0);

    suite->testWindow = SDL_CreateWindow(
        "ResourceManager Test Window", 100, 100, suite->screenWidth,
        suite->screenHeight, SDL_WINDOW_HIDDEN);
    TS_ASSERT_DIFFERS(suite->testWindow, nullptr);

    suite->testRenderer =
        SDL_CreateRenderer(suite->testWindow, -1, SDL_RENDERER_ACCELERATED);
    TS_ASSERT_DIFFERS(suite->testRenderer, nullptr);
    ResourceManager::getInstance().startUp(suite->testRenderer);
    return suite;
  }

  static void destroySuite(GameManagerTestSuite* suite) {
    ResourceManager::getInstance().shutDown();
    SDL_DestroyRenderer(suite->testRenderer);
    // Destroy window
    SDL_DestroyWindow(suite->testWindow);
    Mix_CloseAudio();
    Mix_Quit();
    // Point gWindow to NULL to ensure it points to nothing.
    suite->testRenderer = nullptr;
    suite->testWindow = nullptr;
    // Quit SDL subsystems
    SDL_Quit();
  }
  // --------------------- GameManager TESTS -----------------------------------

  void testStartUp() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    GameManager::getInstance().startGame();
  }

  void testShutDown() {}

  void testUpdate() {
    // tested in jack update 
  }

  void testRender() {
    // tested in instance render methods
  }

  void testGetGameState() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    TS_ASSERT_EQUALS(GameManager::getInstance().getGameState(),
                     GameManager::getInstance().GameState::PreGame);
  }

  void testSetGameState() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    GameManager::getInstance().setGameState(
        GameManager::getInstance().GameState::InGame);
    TS_ASSERT_EQUALS(GameManager::getInstance().getGameState(),
                     GameManager::getInstance().GameState::InGame);
  }

  void testIsGameStarted() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    GameManager::getInstance().setGameState(
        GameManager::getInstance().GameState::InGame);
    TS_ASSERT_EQUALS(GameManager::getInstance().isGameStarted(), true);
    GameManager::getInstance().setGameState(
        GameManager::getInstance().GameState::PreGame);
    TS_ASSERT_EQUALS(GameManager::getInstance().isGameStarted(), false);
  }

  void testIsGameEnd() {}

  void testGetScoreVal() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    TS_ASSERT_EQUALS(GameManager::getInstance().getScoreVal(), 0);
  }

  void testGetLivesVal() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    TS_ASSERT_EQUALS(GameManager::getInstance().getLivesVal(), 3);
  }

  void testReduceLife() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    TS_ASSERT_EQUALS(GameManager::getInstance().getLivesVal(), 3);
    GameManager::getInstance().reduceLife();
    TS_ASSERT_EQUALS(GameManager::getInstance().getLivesVal(), 2);
  }

  void testGetLevelVal() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    TS_ASSERT_EQUALS(GameManager::getInstance().getLevelVal(), 1);
  }

  void testGetDifficulty() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    GameManager::getInstance().setDifficulty(
        GameManager::getInstance().GameDifficulty::Hard);
    TS_ASSERT_EQUALS(GameManager::getInstance().getDifficulty(),
                     GameManager::getInstance().GameDifficulty::Hard);
  }

  void testSetDifficulty() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    GameManager::getInstance().setDifficulty(
        GameManager::getInstance().GameDifficulty::Hard);
    TS_ASSERT_EQUALS(GameManager::getInstance().getDifficulty(),
                     GameManager::getInstance().GameDifficulty::Hard);
  }

  void testStartGame() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    GameManager::getInstance().startGame();
  }

  void testClearLevel() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    TS_ASSERT_EQUALS(GameManager::getInstance().getLivesVal(), 2);
    GameManager::getInstance().reduceLife();
    TS_ASSERT_EQUALS(GameManager::getInstance().getLivesVal(), 1);
    GameManager::getInstance().clearLevel();
    TS_ASSERT_EQUALS(GameManager::getInstance().getLivesVal(), 3);
  }

  void testIsGameWon() {}

  void testUpdateLevel() {
    GameManager::getInstance().startUp(screenWidth, screenHeight);
    TS_ASSERT_EQUALS(GameManager::getInstance().getLevelVal(), 1);
    GameManager::getInstance().updateLevel();
    TS_ASSERT_EQUALS(GameManager::getInstance().getLevelVal(), 2);
  }
};