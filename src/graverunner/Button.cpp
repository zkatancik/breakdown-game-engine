#include "graverunner/Button.hpp"

Button::Button() {}

Button::~Button() {}

void Button::startUp(int srcw, int srch, int srcx, int srcy, int clickedX,
                     int clickedY, int destx, int desty, std::string text) {
  static SDL_Texture *t =
      ResourceManager::getInstance().getTexture(BUTTON_SPRITE_SHEET);
  texture_ = t;
  text_ = text;

  textTexture = ResourceManager::getInstance().getTextTexture(
      text, BUTTON_FONT,
      {BUTTON_TEXT_COLOR_RED, BUTTON_TEXT_COLOR_GREEN, BUTTON_TEXT_COLOR_BLUE,
       BUTTON_TEXT_OPACITY},
      BUTTON_FONT_SIZE);

  textTextureMouseover = ResourceManager::getInstance().getTextTexture(
      text, BUTTON_FONT,
      {BUTTON_TEXT_MOUSEOVER_COLOR_RED, BUTTON_TEXT_MOUSEOVER_COLOR_GREEN,
       BUTTON_TEXT_MOUSEOVER_COLOR_BLUE, BUTTON_TEXT_MOUSEOVER_OPACITY},
      BUTTON_FONT_SIZE);

  Src.w = srcw;
  Src.h = srch;
  Src.x = srcx;
  Src.y = srcy;

  int w, h;
  SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);
  Text_Dest.w = w;
  Text_Dest.h = h;

  Dest.w = Text_Dest.w + BUTTON_TEXT_PADDING;
  Dest.h = Text_Dest.h + BUTTON_TEXT_PADDING;
  Dest.x = destx - (Dest.w / 2);
  Dest.y = desty;

  Text_Dest.x = Dest.x + BUTTON_TEXT_X_POS_OFFSET;
  Text_Dest.y = Dest.y + BUTTON_TEXT_Y_POS_OFFSET;

  originalButtonXPos = srcx;
  originalButtonYPos = srcy;
  clickedButtonXPos = clickedX;
  clickedButtonYPos = clickedY;
  originalTextYPos = Text_Dest.y;
  clickFactor = Text_Dest.y + CLICK_FACTOR_MOVEMENT;
}

void Button::shutDown() {}

void Button::isClicked() {
  isSelected = false;

  // Button Click sound.
  Mix_PlayChannel(
      1, ResourceManager::getInstance().getChunk(BUTTON_CLICK_SOUND), 0);
}

void Button::update(Mouse *mouse) {
  if (SDL_HasIntersection(&Dest, &mouse->point)) {
    isSelected = true;
    Src.x = clickedButtonXPos;
    Src.y = clickedButtonYPos;
    Text_Dest.y = clickFactor;
    // Mix_PlayChannel(
    //     1, ResourceManager::getInstance().getChunk(BUTTON_MOUSEOVER_SOUND),
    //     0);
  } else {
    isSelected = false;
    Text_Dest.y = originalTextYPos;
    Src.x = originalButtonXPos;
    Src.y = originalButtonYPos;
  }
}

void Button::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, texture_, &Src, &Dest);
  if (isSelected) {
    SDL_RenderCopy(renderer, textTextureMouseover, NULL, &Text_Dest);
  } else {
    SDL_RenderCopy(renderer, textTexture, NULL, &Text_Dest);
  }
}

bool Button::IsSelected() const { return isSelected; }

void Button::changeLanguage(Language language) {
  textTexture = ResourceManager::getInstance().getTextTexture(
      ResourceManager::getInstance().getTranslation(text_, language),
      BUTTON_FONT,
      {BUTTON_TEXT_COLOR_RED, BUTTON_TEXT_COLOR_GREEN, BUTTON_TEXT_COLOR_BLUE,
       BUTTON_TEXT_OPACITY},
      BUTTON_FONT_SIZE);

  textTextureMouseover = ResourceManager::getInstance().getTextTexture(
      ResourceManager::getInstance().getTranslation(text_, language),
      BUTTON_FONT,
      {BUTTON_TEXT_MOUSEOVER_COLOR_RED, BUTTON_TEXT_MOUSEOVER_COLOR_GREEN,
       BUTTON_TEXT_MOUSEOVER_COLOR_BLUE, BUTTON_TEXT_MOUSEOVER_OPACITY},
      BUTTON_FONT_SIZE);
}
