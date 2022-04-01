#ifndef LEVEL_EDIT_BUTTON_HPP
#define LEVEL_EDIT_BUTTON_HPP

#include "graverunner/Mouse.hpp"

/**
 * @brief A class representing a clickable UI Text LevelEditButton in our game.
 */
class LevelEditButton {
 private:
  const int CLICK_FACTOR_MOVEMENT = 3;
  const std::string BUTTON_SPRITE_SHEET = "buttons/buttonspritesheet.png";
  const std::string BUTTON_CLICK_SOUND =
      "mixkit-video-game-mystery-alert-234.wav";
  // const std::string BUTTON_MOUSEOVER_SOUND =
  //     "mixkit-interface-click-hover-1127.wav";
  SDL_Texture *texture;
  SDL_Rect texture_dest;
  SDL_Rect texture_outline;

  int clickFactor;
  int originalYPos;
  bool isSelected = false;

 public:
  /**
   * @brief Construct an empty LevelEditButton object, don't forget to call
   * startUp().
   */
  LevelEditButton();

  /**
   * @brief Destroy the LevelEditButton object, don't forget to call shutDown().
   */
  virtual ~LevelEditButton();

  /**
   * @brief Initializes/Configures this LevelEditButton for use and display.
   *
   */
  void startUp(std::string imagePath, int x, int y, int w, int h);

  /**
   * @brief Cleans up this LevelEditButton.
   */
  void shutDown();

  /**
   * @brief
   *
   */
  void isClicked();

  /**
   * @brief Whether or not this LevelEditButton is selected.
   *
   * @return true/false
   */
  bool IsSelected() const;

  /**
   * @brief Updates depiction of this LevelEditButton on screen, based on mouse
   * position.
   *
   * @param mouse (in) Mouse object to use to get its position
   */
  void update(Mouse *mouse);

  /**
   * @brief Calls SDL Render to show LevelEditButton on screen.
   *
   * @param renderer (in) an external SDL renderer to use
   */
  void render(SDL_Renderer *renderer);

#ifdef _TEST
  inline const bool getIsSelected() { return isSelected; }
#endif
};

#endif