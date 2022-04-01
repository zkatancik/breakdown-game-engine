#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Mouse.hpp"

/**
 * @brief A class representing a clickable UI Text Button in our game.
 */
class Button {
 private:
  SDL_Texture *texture_;
  std::string text_;
  SDL_Texture *textTexture;
  SDL_Rect Src;
  SDL_Rect Dest;
  SDL_Rect Text_Dest;
  int originalYPos;
  int clickFactor;
  bool isSelected = false;

 public:
  /**
   * @brief Construct an empty Button object, don't forget to call startUp().
   */
  Button();

  /**
   * @brief Destroy the Button object, don't forget to call shutDown().
   */
  virtual ~Button();

  /**
   * @brief Initializes/Configures this Button for use and display.
   *
   * @param srcw Source width of texture to render
   * @param srch Source height of texture to render
   * @param srcx Source x coord of texture to render
   * @param srcy Source y coord of texture to render
   * @param destw Destination width of texture to render
   * @param desth Destination height of texture to render
   * @param destx Destination x coord of texture to render
   * @param desty Destination y coord of texture to render
   * @param text String to render onto the Button
   */
  void startUp(int srcw, int srch, int srcx, int srcy, int destw, int desth,
               int destx, int desty, std::string text);

  /**
   * @brief Cleans up this Button.
   */
  void shutDown();

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
};

#endif