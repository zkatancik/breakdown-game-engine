//#ifndef EDITOR_UI_MANAGER_HPP
//#define EDITOR_UI_MANAGER_HPP
//
//#include <SDL.h>
//
//#include <cassert>
//#include <deque>
//#include <map>
//#include <sstream>
//#include <string>
//#include <vector>
//
//#include "base/GridRenderComponent.hpp"
//#include "base/ResourceManager.hpp"
//#include "base/SDLGraphicsProgram.hpp"
//#include "base/SDL_DEBUG.hpp"
//#include "graverunner/BaseEnemy.hpp"
//#include "graverunner/GraveRunnerButton.hpp"
//#include "graverunner/Jack.hpp"
//#include "editor/LevelEditButton.hpp"
//#include "graverunner/LevelData.hpp"
//
///**
// * @brief A class for managing game references, like references to Ball,
// * Paddles, Block and score management. Starts at level 1, progresses through
// * levels (defined as text files) as the player clears all blocks.
// */
//class EditorUIManager {
// private:
//  EditorUIManager() = default;  // Private Singleton
//  ~EditorUIManager() = default;
//  EditorUIManager(EditorUIManager const &) = delete;  // Avoid copy constructor.
//  void operator=(EditorUIManager const &) =
//      delete;                                    // Don't allow copy assignment.
//  EditorUIManager(EditorUIManager &&) = delete;  // Avoid move constructor.
//  void operator=(EditorUIManager &&) = delete;   // Don't allow move assignment.
//
// public:
//  /**
//   * @brief Get the Instance object.
//   *
//   * @return EditorUIManager&
//   */
//  static EditorUIManager &getInstance();
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
//   * @brief Update the game state one frame. Includes Ball pos, Mouse input,
//   * collisions, etc.
//   */
//  void update();
//
//  /**
//   * @brief Render a frame of the game.
//   *
//   * @param ren (in) Provided SDL Renderer to use for display
//   */
//  void render(SDL_Renderer *ren);
//
//  /**
//   * @brief Moderates the framerate to a below FRAME_COUNT and outputs the
//   * resulting FPS as a string
//   *
//   * @return std::string string with the format "Current FPS: XX.X"
//   */
//  std::string framerateModerator();
//
//  /**
//   * @brief This is the button listener. Check if a button was clicked and which
//   * one.
//   */
//  void checkButtons();
//
//  // inline std::map<EditorUIManager::LevelEditButtonIndex, std::string>
//  // getPathMap() {
//  //   return pathMap;
//  // }
//
// private:
//  const int BUTTON_SRC_WIDTH = 784;
//  const int BUTTON_SRC_HEIGHT = 295;
//  const int BUTTON_SRC_X = 408;
//  const int BUTTON_SRC_Y = 179;
//  const int BUTTON_SRC_CLICKED_X = 408;
//  const int BUTTON_SRC_CLICKED_Y = 541;
//  const Uint8 TITLE_TEXT_COLOR_RED = 249;
//  const Uint8 TITLE_TEXT_COLOR_GREEN = 219;
//  const Uint8 TITLE_TEXT_COLOR_BLUE = 114;
//  const Uint8 TITLE_TEXT_OPACITY = 0;
//  const int TITLE_FONT_SIZE = 150;
//  const int FPS_FONT_SIZE = 32;
//  const int FPS_Y_PADDING = 10;
//  const int FPS_X_PADDING = 190;
//  const std::string BACKGROUND_IMAGE = "graveyardtiles/menubg.jpg";
//  const std::string fontType = "GADAQUALI.ttf";
//  int fpsXPadding;
//
//  SDL_Texture *background;
//  SDL_Rect bg_dest;
//
//  SDL_Texture *title;
//  SDL_Rect title_dest;
//  SDL_Texture *helpText;
//  SDL_Rect helpText_dest;
//  const std::string helpTextStr = "Choose the level you wish to edit via the buttons above.\nThen select an item by clicking in the left pane. Place by clicking on the grid.";
//
//  SDL_Texture *gameOver;
//  SDL_Rect gameOver_dest;
//
//  SDL_Texture *levelClear;
//  SDL_Rect levelClear_dest;
//
//  SDL_Rect score_dest;
//
//  SDL_Texture *fps_reader;
//  SDL_Rect fps_dest;
//  std::deque<Uint32> frameTimes;
//  Uint32 startTicks;
//
//  int mScreenWidth;
//  int mScreenHeight;
//
//  Mouse *mouse = nullptr;
//
//  // Buttons for user configuration
//  GraveRunnerButton *startButton = nullptr;
//  GraveRunnerButton *editorButton = nullptr;
//  GraveRunnerButton *returnButton = nullptr;
//  GraveRunnerButton *returnButtonMenus = nullptr;
//  GraveRunnerButton *selectLevel1Button = nullptr;
//  GraveRunnerButton *selectLevel2Button = nullptr;
//  GraveRunnerButton *selectLevel3Button = nullptr;
//
//  Language language_{Language::ENGLISH};
//
//  void createUIForLevelEditor();
//  void updateUIForLevelEditor();
//  void renderUIForLevelEditor(SDL_Renderer *ren);
//  void loadLevel();
//
//  int level{1};
//  SDL_Texture *level_background;
//  std::shared_ptr<Block> exitBlock = nullptr;
//  std::shared_ptr<Jack> jack;
//  std::vector<std::shared_ptr<BaseEnemy>> enemies;
//  int blocksPerRow = 0;
//  int rowsOfBlocks = 0;
//  Vector2D<int> blockSize;
//
//  enum LevelEditButtonIndex {
////    UNDO = 0,
////    REDO,
//    ERASE = 0,
////    MOVE,
//    TILE1,
//    TILE2,
//    TILE3,
//    TILEX,
//    TILEY,
//    TILEZ,
////    BONES1,
////    BONES2,
////    BONES3,
////    ARROWSIGN,
////    BUSH1,
////    BUSH2,
////    CRATE,
////    DEADBUSH,
////    SIGN,
////    SKELETON,
////    TOMBSTONE1,
////    TOMEBSTONE2,
////    TREE,
//    JACK,
//    ZOMBIE,
//    LAST_IDX  // End of the buttons, also indicates "None"
//  };
//  std::vector<LevelEditButton> editor_buttons{LAST_IDX};
//
//  LevelEditButtonIndex cur_editor_button{LAST_IDX};
//
//  SDL_Rect tools_rect;
//
//  LevelItem getLevelDataFromEditButtonIdx(LevelEditButtonIndex levelEditButtonIdx);
//
//  // std::map<EditorUIManager::LevelEditButtonIndex, std::string> pathMap = {
//  //     {LevelEditButtonIndex::CRATE, "graveyardtiles/png/Objects/Crate.png"},
//  //     {LevelEditButtonIndex::TILE1, "graveyardtiles/png/Tiles/Tile1.png"}};
//};
//
//#endif