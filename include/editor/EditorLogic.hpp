#ifndef EDITOR_LOGIC_HPP
#define EDITOR_LOGIC_HPP
#include "base/SDLProgramLogic.hpp"
#include "base/PhysicsManager.hpp"
#include "editor/EditorManager.hpp"
#include "editor/EditorUIManager.hpp"

/**
 * @brief Contains Subsystem management for the editor
 */
class EditorLogic : public SDLProgramLogic {
 public:
  EditorLogic() = default;
  EditorLogic(EditorLogic const&) = delete; // Avoid copy constructor.
  void operator=(EditorLogic const&) = delete; // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override {
    EditorManager::getInstance().startUp(width, height);
    EditorUIManager::getInstance().startUp(width, height);
  }

  void shutDown() override {
    EditorUIManager::getInstance().shutDown();
    EditorManager::getInstance().shutDown();
  }

  void update() override {
    EditorUIManager::getInstance().update();
    EditorManager::getInstance().update();
  }

  void checkButtons() override {
    EditorUIManager::getInstance().checkButtons();
  }

  void render(SDL_Renderer* renderer) override {
    EditorManager::getInstance().render(renderer);
    EditorUIManager::getInstance().render(renderer);
  }
};

#endif