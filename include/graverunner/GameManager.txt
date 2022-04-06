#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SDL.h>

#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "base/SDL_DEBUG.hpp"
#include "graverunner/BaseEnemy.hpp"
#include "graverunner/Block.hpp"
#include "graverunner/Button.hpp"
#include "graverunner/FollowerZombie.hpp"
#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/Jack.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/PatrolZombie.hpp"
#include "graverunner/UIManager.hpp"
#include "base/TinyMath.hpp"

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
  const int MAX_LEVEL = 3;

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
   * @brief Main states of a game.
   */
  enum GameState {
    PreGame = 0,
    InGame,
    GameEnd,
    LanguageSelect
  };

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
   * @brief Return is the game in GameState::InGame state.
   *
   * @return true/false
   */
  bool isGameStarted();

  /**
   * @brief Whether Game over conditions met.
   *
   * @return true/false
   */
  bool isGameEnd();

  /**
   * @brief Handles keyboard input from SDL
   *
   * @param keyboardState Current keyboard state
   */
  // void handleKeyboard(const Uint8 *keyboardState);

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
   * @brief Create the level and start the game.
   */
  void startGame();

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
   * @brief Increase the level number (ie. go to next level). Reset back to
   * level 1 if all levels have been completed.
   */
  void updateLevel();

 private:
  const std::string BACKGROUND_IMAGE = "graveyardtiles/png/BG.jpg";

  std::shared_ptr<Jack> jack;

  std::shared_ptr<Block> exitBlock = nullptr;

  int blocksPerRow = 0;
  int rowsOfBlocks = 0;
  Vector2D<int> blockSize;

  SDL_Texture *background{nullptr};
  SDL_Rect bg_dest;

  GameState gameState_{GameState::PreGame};

  int currentLevelNumber{1};

  int score{0};

  std::shared_ptr<GraveRunnerLevel> currentLevel{nullptr};

  LevelData mLevelData;

};

#endif