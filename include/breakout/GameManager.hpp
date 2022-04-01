#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SDL.h>

#include <map>
#include <string>
#include <vector>

#include "Ball.hpp"
#include "Block.hpp"
#include "Button.hpp"
#include "CollisionDetector.hpp"
#include "LevelData.hpp"
#include "Paddle.hpp"
#include "SDL_DEBUG.hpp"

/**
 * @brief A class for managing game references, like references to Ball,
 * Paddles, Block and score management. Starts at level 1, progresses through
 * levels (defined as text files) as the player clears all blocks.
 */
class GameManager {
 private:
  GameManager() = default;  // Private Singleton
  ~GameManager() = default;
  GameManager(GameManager const &) = delete;     // Avoid copy constructor.
  void operator=(GameManager const &) = delete;  // Don't allow copy assignment.
  GameManager(GameManager &&) = delete;          // Avoid move constructor.
  void operator=(GameManager &&) = delete;       // Don't allow move assignment.

 public:
  /**
   * @brief Number of Level files in res\2DBreakout_Levels
   */
  const int MAX_LEVEL = 4;
  const int EASY_BALL_X = 3;
  const int EASY_BALL_Y = 5;
  const int MEDIUM_BALL_X = 4;
  const int MEDIUM_BALL_Y = 6;
  const int HARD_BALL_X = 6;
  const int HARD_BALL_Y = 8;

  /**
   * @brief Get the Instance object.
   *
   * @return GameManager&
   */
  static GameManager &getInstance();

  /**
   * @brief Acts as the contructor.
   *
   * @param screenWidth screen width
   * @param screenHeight screen height
   */
  void startUp(int screenWidth, int screenHeight);

  /**
   * @brief Acts as a destructor.
   *
   */
  void shutDown();

  /**
   * @brief Update the game state one frame. Includes Ball pos, Mouse input,
   * collisions, etc.
   */
  void update();

  /**
   * @brief Render a frame of the game.
   *
   * @param ren (in) Provided SDL Renderer to use for display
   */
  void render(SDL_Renderer *ren);

  /**
   * @brief Move the Paddle to the Left
   *
   * @param deltaT elapsed time
   * @param sw screen width
   */
  void movePaddleLeft(uint32_t deltaT, int sw);

  /**
   * @brief Move the Paddle to the Right
   *
   * @param deltaT elapsed time
   * @param sw screen width
   */
  void movePaddleRight(uint32_t deltaT, int sw);

  /**
   * @brief Get the Level name/number text
   *
   * @return std::string
   */
  std::string getLevel();

  /**
   * @brief Get the Score text
   *
   * @return std::string
   */
  std::string getScore();

  /**
   * @brief Get the Score value
   *
   * @return int
   */
  int getScoreVal();

  /**
   * @brief Get the Level number
   *
   * @return int
   */
  int getLevelVal();

  /**
   * @brief Get the number of blocks remaining on screen
   *
   * @return int
   */
  int getNumBlocks();

  /**
   * @brief Clear Top block.
   *
   */
  void clearBlock();

  /**
   * @brief This is the button listener. Check if a button was clicked and which
   * one.
   */
  void checkButtons();

  /**
   * @brief Return is the game in GameState::InGame state.
   *
   * @return true/false
   */
  bool isGameStarted();

  /**
   * @brief Create the level and start the game.
   */
  void startGame();

  /**
   * @brief Stops the Ball
   *
   */
  void stopBall();

  /**
   * @brief Stops the Paddle
   */
  void stopPaddle();

  /**
   * @brief Main states of a game.
   */
  enum GameState {
    PreGame = 0,
    InGame,
    GameEnd,
    LanguageSelect,
    DifficultySelect,
    HighScoreEntry
  };

  /**
   * @brief The current difficulty of the game
   *
   */
  enum GameDifficulty { Easy = 0, Medium, Hard };

  /**
   * @brief Get the Game State object
   *
   * @return GameState
   */
  GameState getGameState();

  /**
   * @brief Set the Game State object.
   *
   * @param gs new value to use
   */
  void setGameState(GameState gs);

  /**
   * @brief Clear the level.
   */
  void clearLevel();

  /**
   * @brief Whether or not Game is a Win.
   *
   * @return true/false
   */
  bool isGameWon();

  /**
   * @brief Get the lives string.
   *
   * @return std::string
   */
  std::string getLives();

  std::string getHighScore();

  /**
   * @brief Get the number of lives remaining.
   *
   * @return int
   */
  int getLivesVal();

  /**
   * @brief Reduce a life if lives exists.
   * Also, reset ball if life reduced and play audio bit.
   * @details No-op if no lives are left.
   */
  void reduceLife();

  /**
   * @brief Whether Game over conditions met.
   *
   * @return true/false
   */
  bool isGameEnd();

  /**
   * @brief Increase the level number (ie. go to next level). Reset back to
   * level 1 if all levels have been completed.
   */
  void updateLevel();

  /**
   * @brief Get the Level End Message object string.
   * @return std::string
   */
  std::string getLevelEndMessage();

  bool isNeedNewBall();

  void spawnNewBall();

  int getNeedNewBallTicks();

  std::string getHighScoreInputText() { return highestScoreUsername; };

  void setHighScoreInputText(const std::string &s) {
    highestScoreUsername = s;
  };

  std::string getTranslation(const std::string &s);

#ifdef _TEST
  inline const Paddle *getPaddle() { return paddle; }
  inline const Ball *getBall() { return ball; }
  inline const Mouse *getMouse() { return mouse; }
  inline const Button *getStartButton() { return startButton; }
  inline const Button *getReturnButton() { return returnButton; }
  inline const std::vector<Block> *getBlockList() { return &blockList; }
#endif

 private:
  Paddle *paddle = nullptr;
  Ball *ball = nullptr;
  Mouse *mouse = nullptr;

  // Buttons for user configuration
  Button *startButton = nullptr;
  Button *difficultyButton = nullptr;
  Button *returnButton = nullptr;
  Button *returnButtonMenus = nullptr;
  Button *languageButton = nullptr;
  Button *englishButton = nullptr;
  Button *spanishButton = nullptr;
  Button *easyButton = nullptr;  // hehe
  Button *mediumButton = nullptr;
  Button *hardButton = nullptr;
  Button *enterButton = nullptr;
  Button *nextLevelButton = nullptr;

  std::string highestScoreUsername;

  int screenWidth;
  int screenHeight;

  static const int livesPerGame = 3;
  int lives = livesPerGame;
  int highestScore = 0;

  int blocksPerRow = 0;
  int rowsOfBlocks = 0;
  int numBlocks = -1;
  int blocksPerColor = 2;
  std::vector<Block> blockList;
  bool blocksLeft;

  int level{1};
  bool needNewBall{false};

  Uint32 needNewBallTicks{0};

  int score{0};

  GameState gameState_{GameState::PreGame};
  Language language_{Language::ENGLISH};
  GameDifficulty gameDifficulty_{GameDifficulty::Easy};

  void detectCollisions();

  void clearBlock(std::vector<Block>::iterator i);

  void readHighestScoreOnFile();

  void updateHighestScoreOnFile(const std::string &username, int highScore);
};

#endif