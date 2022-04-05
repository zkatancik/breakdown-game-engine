#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "graverunner/Mouse.hpp"
#include "breakout/Tag.hpp"

/**
 * @brief A class representing a clickable UI Text Button.
 */
class Button : public GameObject {
 private:
  const Uint8 BUTTON_TEXT_COLOR_RED = 249;
  const Uint8 BUTTON_TEXT_COLOR_GREEN = 219;
  const Uint8 BUTTON_TEXT_COLOR_BLUE = 114;
  const Uint8 BUTTON_TEXT_OPACITY = 0;
  const Uint8 BUTTON_TEXT_MOUSEOVER_COLOR_RED = 212;
  const Uint8 BUTTON_TEXT_MOUSEOVER_COLOR_GREEN = 120;
  const Uint8 BUTTON_TEXT_MOUSEOVER_COLOR_BLUE = 0;
  const Uint8 BUTTON_TEXT_MOUSEOVER_OPACITY = 0;
  const Uint8 BUTTON_FONT_SIZE = 64;
  const int BUTTON_TEXT_PADDING = 70;
  const int BUTTON_TEXT_X_POS_OFFSET = 30;
  const int BUTTON_TEXT_Y_POS_OFFSET = 55;
  const int CLICK_FACTOR_MOVEMENT = 3;
  const std::string BUTTON_SPRITE_SHEET = "buttons/buttonspritesheet.png";
  const std::string BUTTON_CLICK_SOUND = "mixkit-video-game-mystery-alert-234.wav";
  SDL_Texture *texture_;
  std::shared_ptr<GameObject> mText;
  SDL_Texture *textTextureMouseover;
  SDL_Rect Src;
  SDL_Rect Dest;
  SDL_Rect Text_Dest;
  int originalTextYPos;
  int originalButtonXPos;
  int originalButtonYPos;
  int clickedButtonXPos;
  int clickedButtonYPos;
  int clickFactor;
  bool isSelected = false;

 public:
  /**
   * @brief Initializes/Configures this Button for use and display.
   *
   * @param srcw Source width of texture to render
   * @param srch Source height of texture to render
   * @param srcx Source x coord of texture to render
   * @param srcy Source y coord of texture to render
   * @param destx Destination x coord of texture to render
   * @param desty Destination y coord of texture to render
   * @param clickedX Source x coord of texture to render for mouseover
   * @param clickedY Source y coord of texture to render for mouseover
   * @param text String to render onto the Button
   */
  Button(Level& level, int srcw, int srch, int srcx, int srcy, int destw,
         int desth, int destx, int desty, std::string text);
  /**
   * @brief Mouse click handler, e.g. plays sound.
   */
  void isClicked();

  /**
   * @brief Whether or not this Button is selected.
   *
   * @return true/false
   */
  bool IsSelected() const;

  /**
   * @brief Updates depiction of this Button on screen, based on mouse position.
   *
   * @param mouse (in) Mouse object to use to get its position
   */
  void update(Mouse *mouse);

  /**
   * @brief Calls SDL Render to show Button on screen.
   *
   * @param renderer (in) an external SDL renderer to use
   */
  void render(SDL_Renderer *renderer);

  /**
   * @brief Change the language of the text on this Button.
   *
   * @param language The desired language
   */
  void changeLanguage(Language language);

#ifdef _TEST
  inline const bool getIsSelected() { return isSelected; }
#endif
};

#endif