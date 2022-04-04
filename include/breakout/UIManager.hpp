//#ifndef UI_MANAGER_HPP
//#define UI_MANAGER_HPP
//
//#include <SDL.h>
//
//#include <deque>
//#include <map>
//#include <sstream>
//#include <string>
//#include <vector>
//
//#include "base/ResourceManager.hpp"
//#include "base/SDLGraphicsProgram.hpp"
//#include "base/SDL_DEBUG.hpp"
//#include "graverunner/Button.hpp"
//#include "breakout/GameManager.hpp"
//#include "base/GridRenderComponent.hpp"
//#include "base/Page.hpp"
//
///**
// * @brief A class for managing game references, like references to Ball,
// * Paddles, Block and score management. Starts at level 1, progresses through
// * levels (defined as text files) as the player clears all blocks.
// */
//class UIManager {
// private:
//  UIManager() = default;  // Private Singleton
//  ~UIManager() = default;
//  UIManager(UIManager const &) = delete;       // Avoid copy constructor.
//  void operator=(UIManager const &) = delete;  // Don't allow copy assignment.
//  UIManager(UIManager &&) = delete;            // Avoid move constructor.
//  void operator=(UIManager &&) = delete;       // Don't allow move assignment.
//
// public:
//  /**
//   * @brief Get the Instance object.
//   *
//   * @return UIManager&
//   */
//  static UIManager &getInstance();
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
//  /**
//   * @brief Get the Translation string from language to language
//   *
//   * @param s string to translate
//   * @return std::string string in language
//   */
//  std::string getTranslation(const std::string &s);
//
//  /**
//   * @brief Get the Level End Message object string.
//   * @return std::string
//   */
//  std::string getLevelEndMessage();
//
//  /**
//   * @brief Get the Level name/number text
//   *
//   * @return std::string
//   */
//  std::string getLevel();
//
//  /**
//   * @brief Get the Score text
//   *
//   * @return std::string
//   */
//  std::string getScore();
//
//#ifdef _TEST
//  inline const Mouse *getMouse() { return mouse; }
//  inline const Language getLanguage() { return language_; }
//#endif
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
//  Button *startButton = nullptr;
//  Button *returnButton = nullptr;
//  Button *returnButtonMenus = nullptr;
//  Button *languageButton = nullptr;
//  Button *englishButton = nullptr;
//  Button *spanishButton = nullptr;
//  Button *nextLevelButton = nullptr;
//
//  Language language_{Language::ENGLISH};
//
//};
//
//#endif