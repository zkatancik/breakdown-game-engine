#include "Button.hpp"

Button::Button() {}

Button::~Button() {}

void Button::startUp(int srcw, int srch, int srcx, int srcy, int destw,
                     int desth, int destx, int desty, std::string text) {
  static SDL_Texture *t =
      ResourceManager::getInstance().getTexture("buttonSpriteSheet.png");
  texture_ = t;
  text_ = text;

  textTexture = ResourceManager::getInstance().getTextTexture(
      text, "Gageda.ttf", {255, 255, 255, 0}, 64);

  Src.w = srcw;
  Src.h = srch;
  Src.x = srcx;
  Src.y = srcy;

  int w, h;
  SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);
  Text_Dest.w = w;
  Text_Dest.h = h;

  Dest.w = Text_Dest.w + 70;
  Dest.h = desth;
  Dest.x = destx - (Dest.w / 2);
  Dest.y = desty;

  Text_Dest.x = Dest.x + 30;
  Text_Dest.y = Dest.y + 30;

  originalYPos = Text_Dest.y;
  clickFactor = Text_Dest.y + 3;
}

void Button::shutDown() {}

void Button::isClicked() {
  isSelected = false;

  // Button Click sound.
  Mix_PlayChannel(
      1, ResourceManager::getInstance().getChunk("ButtonClick_SFX.wav"), 0);
}

void Button::update(Mouse *mouse) {
  if (SDL_HasIntersection(&Dest, &mouse->point)) {
    isSelected = true;
    // TODO: get rid of Hard codes
    Src.x = 57;
    Text_Dest.y = clickFactor;
  } else {
    isSelected = false;
    // TODO: get rid of Hard codes
    Src.x = 635;
    Text_Dest.y = originalYPos;
  }
}

void Button::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, texture_, &Src, &Dest);
  SDL_RenderCopy(renderer, textTexture, NULL, &Text_Dest);
}

bool Button::IsSelected() const {
  return isSelected;
}
void Button::changeLanguage(Language language) {
  textTexture = ResourceManager::getInstance().getTextTexture(
      ResourceManager::getInstance().getTranslation(text_, language),
      "Gageda.ttf", {255, 255, 255, 0}, 64);
}
