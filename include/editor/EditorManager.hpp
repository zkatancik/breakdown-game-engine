//#ifndef EDITOR_MANAGER_HPP
//#define EDITOR_MANAGER_HPP
//
//#include <SDL.h>
//
//#include <map>
//#include <numeric>
//#include <string>
//#include <vector>
//
//#include "base/SDL_DEBUG.hpp"
//#include "base/TinyMath.hpp"
//#include "graverunner/BaseEnemy.hpp"
//#include "graverunner/Block.hpp"
//#include "graverunner/GraveRunnerButton.hpp"
//#include "graverunner/FollowerZombie.hpp"
//#include "graverunner/GraveRunnerLevel.hpp"
//#include "graverunner/Jack.hpp"
//#include "graverunner/LevelData.hpp"
//#include "graverunner/PatrolZombie.hpp"
//
///**
// * @brief A class for managing the editor
// */
//class EditorManager {
// private:
//  EditorManager() = default;  // Private Singleton
//  ~EditorManager() = default;
//  EditorManager(EditorManager const &) = delete;  // Avoid copy constructor.
//  void operator=(EditorManager const &) =
//      delete;                                 // Don't allow copy assignment.
//  EditorManager(EditorManager &&) = delete;   // Avoid move constructor.
//  void operator=(EditorManager &&) = delete;  // Don't allow move assignment.
//
// public:
//  /**
//   * @brief Number of Level files in res\2DBreakout_Levels
//   */
//  const int MAX_LEVEL = 3;
//
//  /**
//   * @brief Get the Instance object.
//   *
//   * @return EditorManager&
//   */
//  static EditorManager &getInstance();
//
//  /**
//   * @brief Acts as the contructor.
//   *
//   * @param screenWidth screen width
//   * @param screenHeight screen height
//   */
//  void startUp(int screenWidth, int screenHeight);
//
//  /**
//   * @brief Acts as a destructor.
//   *
//   */
//  void shutDown();
//
//  /**
//   * @brief Update the editor state one frame. Includes Ball pos, Mouse input,
//   * collisions, etc.
//   */
//  void update();
//
//  /**
//   * @brief Render a frame of the editor.
//   *
//   * @param ren (in) Provided SDL Renderer to use for display
//   */
//  void render(SDL_Renderer *ren);
//
//  /**
//   * @brief Main states of a editor.
//   */
//  enum EditorState { Menu = 0, LevelEditor };
//
//  /**
//   * @brief Get the editor State object
//   *
//   * @return GameState
//   */
//  EditorState getEditorState();
//
//  /**
//   * @brief Set the editor State object.
//   *
//   * @param es new value to use
//   */
//  void setEditorState(EditorState es);
//
//  /**
//   * @brief Create the level and start the editor.
//   */
//  void startEditor();
//
//  /**
//   * @brief Update the item in the current level.
//   *
//   * @param gridPosition the position at which to update item
//   * @param item the item to add at above position
//   */
//  void updateCurrentLevel(Vector2D<int> gridPosition, LevelItem item);
//
//  /**
//   * @brief Clear the level.
//   */
//  void clearLevel();
//
//  /**
//   * @brief Set the current level number to a new value.
//   *
//   * @param newVal new level num
//   */
//  inline void setCurrentLevelVal(int newVal) {currentLevelNumber = newVal;}
//
//  int getLevelVal();
//
//  inline std::shared_ptr<GraveRunnerLevel> getCurrentLevel() {
//    return currentLevel;
//  }
//
// private:
//  const std::string BACKGROUND_IMAGE = "graveyardtiles/png/BG.jpg";
//
//  std::shared_ptr<Jack> jack;
//
//  std::vector<std::shared_ptr<BaseEnemy>> enemies;
//
//  std::shared_ptr<BreakoutBlock> exitBlock = nullptr;
//
//  int blocksPerRow = 0;
//  int rowsOfBlocks = 0;
//  Vector2D<int> blockSize;
//
//  SDL_Texture *background{nullptr};
//  SDL_Rect bg_dest;
//
//  EditorState editorState_{EditorState::Menu};
//
//  int currentLevelNumber{1};
//
//  int score{0};
//
//  std::shared_ptr<GraveRunnerLevel> currentLevel{nullptr};
//
//  LevelData mLevelData;
//};
//
//#endif