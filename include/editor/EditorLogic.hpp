#ifndef EDITOR_LOGIC_HPP
#define EDITOR_LOGIC_HPP
#include "base/Level.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SDLProgramLogic.hpp"
#include "base/TextMessageObject.hpp"
#include "breakout/BreakoutButton.hpp"
#include "breakout/BreakoutGameLevelEditor.hpp"
#include "editor/EditorManager.hpp"
#include "editor/EditorUIManager.hpp"
#include "graverunner/GraveRunnerButton.hpp"

/**
 * @brief Contains Subsystem management for the editor
 */
class EditorLogic : public SDLProgramLogic {
 public:
  EditorLogic() = default;
  EditorLogic(EditorLogic const&) = delete;     // Avoid copy constructor.
  void operator=(EditorLogic const&) = delete;  // Don't allow copy assignment.

  void startUp(SDL_Renderer* gRender, int width, int height) override;

  void shutDown() override;

  void update() override;

  void render(SDL_Renderer* renderer) override;

  bool quit() override { return mQuite; }

 private:
  bool mQuite{false};
  std::shared_ptr<Level> mCurrentlyActiveLevel{
      nullptr};  //< The level that's being shown to the user
  std::shared_ptr<Level> mStartMenu{
      nullptr};  // < First menu the user sees. Lets the user choose between
                 // GraveRunner or Breakout
  std::shared_ptr<Level> mBreakOutLevelSelector{
      nullptr};  //< Menu that selects the level number for Breakout
  std::shared_ptr<Level> mGraveRunnerLevelSelector{
      nullptr};  //< Menu that selects the level number for GraveRunner
  std::vector<std::shared_ptr<BreakoutGameLevelEditor>> mBreakoutLevelEditors{
      nullptr, nullptr, nullptr, nullptr};  //< Level editors

  /**
   * Creates and initializes the start menu of the level editor.
   * The start menu lets the user select the game they wish to edit.
   * @param width of the level
   * @param height of the level
   */
  void createAndInitStartMenu(int width, int height);

  void createAndInitBreakoutLevelSelector(int width, int height);

  void createAndInitGraveRunnerSelector(int width, int height);

  void createBreakoutLevelEditors(int width, int height);
};

#endif