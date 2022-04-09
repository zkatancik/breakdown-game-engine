#include <cxxtest/TestSuite.h>

#include "graverunner/GameManager.hpp"
#include "graverunner/ResourceManager.hpp"
#include "graverunner/UIManager.hpp"

class UIManagerTestSuite : public CxxTest::TestSuite {
 public:
  const float EPSILON = 0.001f;

  // --------------------- BLOCK TESTS -----------------------------------

  void testStartUp() {
    UIManager::getInstance().startUp(1280, 720);
    TS_ASSERT_EQUALS(UIManager::getInstance().getLanguage(), Language::ENGLISH);
  }

  void testShutDown() {
    UIManager::getInstance().startUp(1280, 720);
    UIManager::getInstance().shutDown();
  }

  void testUpdate() {}

  void testRender() {}

  void testFramerateModerator() {
    UIManager::getInstance().startUp(1280, 720);
    UIManager::getInstance().framerateModerator();
  }

  void testCheckButtons() {}

  void testGetTranslation() {
    UIManager::getInstance().startUp(1280, 720);
    // TS_ASSERT_EQUALS(UIManager::getInstance().getTranslation("START"),
    //                   "COMIENZO")
    UIManager::getInstance().shutDown();
  }

  void testGetLevelEndMessage() {
    UIManager::getInstance().startUp(1280, 720);
    TS_ASSERT_EQUALS(UIManager::getInstance().getLevelEndMessage(), "LEVEL CLEARED!");
    UIManager::getInstance().shutDown();
  }

  void testGetLevel() {
    UIManager::getInstance().startUp(1280, 720);
    GameManager::getInstance().startUp(1280, 720);
    GameManager::getInstance().startGame();
    TS_ASSERT_EQUALS(UIManager::getInstance().getLevel(), "Level 1");
    GameManager::getInstance().shutDown();
    UIManager::getInstance().shutDown();
  }

  void testGetScore() {
    UIManager::getInstance().startUp(1280, 720);
    GameManager::getInstance().startUp(1280, 720);
    GameManager::getInstance().startGame();
    TS_ASSERT_EQUALS(UIManager::getInstance().getScore(), "Score 0");
    GameManager::getInstance().shutDown();
    UIManager::getInstance().shutDown();
  }

  void testGetLives() {
    UIManager::getInstance().startUp(1280, 720);
    GameManager::getInstance().startUp(1280, 720);
    GameManager::getInstance().startGame();
    TS_ASSERT_EQUALS(UIManager::getInstance().getLives(), "Lives 3");
    GameManager::getInstance().shutDown();
    UIManager::getInstance().shutDown();
  }

  void testGetHighScore() {}

  void testGetHighScoreInputText() {}

  void testGetHighScoreValue() {}

  void testSetHighScoreValue() {}

  void testReadHighestScoreOnFile() {}

  void testUpdateHighestScoreOnFile() {}
};
