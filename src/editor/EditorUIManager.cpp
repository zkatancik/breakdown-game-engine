#include "editor/EditorUIManager.hpp"

#include "editor/EditorManager.hpp"

EditorUIManager& EditorUIManager::getInstance() {
  static EditorUIManager* instance = new EditorUIManager();
  return *instance;
}

/**
 * @brief Acts as the contructor.
 *
 * @param screenWidth screen width
 * @param screenHeight screen height
 */
void EditorUIManager::startUp(int screenWidth, int screenHeight) {
  mScreenHeight = screenHeight;
  mScreenWidth = screenWidth;

  mouse = new Mouse();
  mouse->startUp();

  background = ResourceManager::getInstance().getTexture(BACKGROUND_IMAGE);
  bg_dest.w = screenWidth;
  bg_dest.h = screenHeight;
  bg_dest.x = 0;
  bg_dest.y = 0;

  fpsXPadding = screenWidth - FPS_X_PADDING;

  title = ResourceManager::getInstance().getTextTexture(
      "GraveRunner", fontType,
      {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
       TITLE_TEXT_OPACITY},
      TITLE_FONT_SIZE);

  int w, h;
  SDL_QueryTexture(title, nullptr, nullptr, &w, &h);
  title_dest.w = w;
  title_dest.h = h;
  title_dest.x = screenWidth / 2 - (title_dest.w / 2);
  title_dest.y = screenHeight / 6;

  helpText = ResourceManager::getInstance().getTextTexture(
      helpTextStr, fontType, 
      {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
       TITLE_TEXT_OPACITY},
      30);

  SDL_QueryTexture(helpText, nullptr, nullptr, &w, &h);
  helpText_dest.w = w;
  helpText_dest.h = h;
  helpText_dest.x = screenWidth / 2 - (helpText_dest.w / 2);;
  helpText_dest.y = 600;

  fps_dest.x = 20;
  fps_dest.y = 20;

  startTicks = SDL_GetTicks();

  const int screenMidX = screenWidth / 2;

  editorButton = new Button();
  editorButton->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                        BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                        BUTTON_SRC_CLICKED_Y, screenMidX,
                        screenHeight - (screenHeight / 2.2), u8"EDIT LEVEL");

  returnButton = new Button();
  returnButton->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                        BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                        BUTTON_SRC_CLICKED_Y, screenMidX,
                        screenHeight / 2 + (139 / 2), u8"RETURN");

  const int levelButtonRowHeight = 300;
  const int levelButtonGap = 350;
  selectLevel1Button = new Button();
  selectLevel1Button->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                        BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                        BUTTON_SRC_CLICKED_Y, screenMidX - levelButtonGap, levelButtonRowHeight, u8"LEVEL 1");

  selectLevel2Button = new Button();
  selectLevel2Button->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                        BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                        BUTTON_SRC_CLICKED_Y, screenMidX, levelButtonRowHeight, u8"LEVEL 2");

  selectLevel3Button = new Button();
  selectLevel3Button->startUp(BUTTON_SRC_WIDTH, BUTTON_SRC_HEIGHT, BUTTON_SRC_X,
                        BUTTON_SRC_Y, BUTTON_SRC_CLICKED_X,
                        BUTTON_SRC_CLICKED_Y, screenMidX + levelButtonGap, levelButtonRowHeight, u8"LEVEL 3");


  tools_rect.x = 0;
  tools_rect.y = 0;
  tools_rect.w = 212;
  tools_rect.h = mScreenHeight;

//  editor_buttons.at(UNDO).startUp("graveyardtiles/undo.png", 5, 10, 64, 64);
//  editor_buttons.at(REDO).startUp("graveyardtiles/redo.png", 143, 10, 64, 64);
  editor_buttons.at(ERASE).startUp("graveyardtiles/erase.png", 5, 84, 64, 64);
//  editor_buttons.at(MOVE).startUp("graveyardtiles/move.png", 143, 84, 64, 64);
  editor_buttons.at(TILE1).startUp("graveyardtiles/png/Tiles/Tile1.png", 5, 158,
                                   64, 64);
  editor_buttons.at(TILE2).startUp("graveyardtiles/png/Tiles/Tile2.png", 74,
                                   158, 64, 64);
  editor_buttons.at(TILE3).startUp("graveyardtiles/png/Tiles/Tile3.png", 143,
                                   158, 64, 64);
  editor_buttons.at(TILEX).startUp("graveyardtiles/png/Tiles/TileX.png", 5, 232,
                                   64, 64);
  editor_buttons.at(TILEY).startUp("graveyardtiles/png/Tiles/TileY.png", 74,
                                   232, 64, 64);
  editor_buttons.at(TILEZ).startUp("graveyardtiles/png/Tiles/TileZ.png", 143,
                                   232, 64, 64);
//  editor_buttons.at(BONES1).startUp("graveyardtiles/png/Tiles/Bone1.png", 5,
//                                    306, 64, 64);
//  editor_buttons.at(BONES2).startUp("graveyardtiles/png/Tiles/Bone2.png", 74,
//                                    306, 64, 64);
//  editor_buttons.at(BONES3).startUp("graveyardtiles/png/Tiles/Bone3.png", 143,
//                                    306, 64, 64);
//  editor_buttons.at(ARROWSIGN).startUp(
//      "graveyardtiles/png/Objects/ArrowSign.png", 5, 380, 64, 64);
//  editor_buttons.at(BUSH1).startUp("graveyardtiles/png/Objects/Bush1.png", 74,
//                                   380, 64, 64);
//  editor_buttons.at(BUSH2).startUp("graveyardtiles/png/Objects/Bush2.png", 143,
//                                   380, 64, 64);
//  editor_buttons.at(CRATE).startUp("graveyardtiles/png/Objects/Crate.png", 5,
//                                   454, 64, 64);
//  editor_buttons.at(DEADBUSH).startUp("graveyardtiles/png/Objects/DeadBush.png",
//                                      74, 454, 64, 64);
//  editor_buttons.at(SIGN).startUp("graveyardtiles/png/Objects/Sign.png", 143,
//                                  454, 64, 64);
//  editor_buttons.at(SKELETON).startUp("graveyardtiles/png/Objects/Skeleton.png",
//                                      5, 560, 64, 32);
//  editor_buttons.at(TOMBSTONE1)
//      .startUp("graveyardtiles/png/Objects/TombStone1.png", 74, 528, 64, 64);
//  editor_buttons.at(TOMEBSTONE2)
//      .startUp("graveyardtiles/png/Objects/TombStone2.png", 143, 528, 48, 64);
//  editor_buttons.at(TREE).startUp("graveyardtiles/png/Objects/Tree.png", 5, 602,
//                                  64, 64);
  editor_buttons.at(JACK).startUp("jack/Idle1.png", 74, 602, 64, 64);
  editor_buttons.at(ZOMBIE).startUp("zombies/male/Idle1.png", 143, 602, 64, 64);
}

void EditorUIManager::updateUIForLevelEditor() {
  for (LevelEditButton& button : editor_buttons) {
    button.update(mouse);
  }
}

void EditorUIManager::renderUIForLevelEditor(SDL_Renderer* ren) {
  SDL_SetRenderDrawColor(ren, 112, 128, 144, 127);
  SDL_RenderFillRect(ren, &tools_rect);
  SDL_RenderDrawRect(ren, &tools_rect);

  for (LevelEditButton& button : editor_buttons) {
    button.render(ren);
  }
}

/**
 * @brief Acts as a destructor.
 *
 */
void EditorUIManager::shutDown() {
  for (LevelEditButton& button : editor_buttons) {
    button.shutDown();
  }
  delete selectLevel1Button;
  delete selectLevel2Button;
  delete selectLevel3Button;
  delete mouse;
  delete startButton;
  delete returnButton;
  delete returnButtonMenus;
  delete editorButton;
}

/**
 * @brief Update the UI/ menu state
 */
void EditorUIManager::update() {
  mouse->update();
  if (EditorManager::getInstance().getEditorState() ==
      EditorManager::getInstance().EditorState::Menu) {
    editorButton->update(mouse);
    selectLevel1Button->update(mouse);
    selectLevel2Button->update(mouse);
    selectLevel3Button->update(mouse);
  } else if (EditorManager::getInstance().getEditorState() ==
             EditorManager::getInstance().EditorState::LevelEditor) {
    EditorManager::getInstance().startEditor();
    updateUIForLevelEditor();
  }
}

/**
 * @brief Render a frame of the editor.
 *
 * @param ren (in) Provided SDL Renderer to use for display
 */
void EditorUIManager::render(SDL_Renderer* ren) {
  if (EditorManager::getInstance().getEditorState() ==
      EditorManager::getInstance().EditorState::Menu) {
    // PreEditor UI
    SDL_RenderCopy(ren, background, nullptr, &bg_dest);
    SDL_RenderCopy(ren, title, nullptr, &title_dest);
    SDL_RenderCopy(ren, helpText, nullptr, &helpText_dest);
    editorButton->render(ren);
    selectLevel1Button->render(ren);
    selectLevel2Button->render(ren);
    selectLevel3Button->render(ren);
  } else if (EditorManager::getInstance().getEditorState() ==
             EditorManager::getInstance().EditorState::LevelEditor) {
    SDL_RenderCopy(ren, level_background, NULL, &bg_dest);

    renderUIForLevelEditor(ren);

    fps_reader = ResourceManager::getInstance().getTextTexture(
        framerateModerator(), fontType,
        {TITLE_TEXT_COLOR_RED, TITLE_TEXT_COLOR_GREEN, TITLE_TEXT_COLOR_BLUE,
         TITLE_TEXT_OPACITY},
        FPS_FONT_SIZE);

    int w, h;
    SDL_QueryTexture(fps_reader, nullptr, nullptr, &w, &h);
    fps_dest.w = w;
    fps_dest.h = h;
    fps_dest.x = fpsXPadding;
    fps_dest.y = FPS_Y_PADDING;
    SDL_RenderCopy(ren, fps_reader, nullptr, &fps_dest);
  }
  mouse->render(ren);
}

std::string EditorUIManager::framerateModerator() {
  const size_t FRAME_COUNT = 60;
  const size_t DESIRED_TICKS_PER_FRAME = 1000 / FRAME_COUNT;

  Uint32 currTicks = SDL_GetTicks();
  Uint32 elapsedTicks = currTicks - startTicks;

  if (elapsedTicks < DESIRED_TICKS_PER_FRAME) {
    SDL_Delay(DESIRED_TICKS_PER_FRAME - elapsedTicks);
    currTicks = SDL_GetTicks();
    elapsedTicks = currTicks - startTicks;
  }

  startTicks = currTicks;

  frameTimes.push_back(elapsedTicks);
  if (frameTimes.size() > FRAME_COUNT) {
    frameTimes.pop_front();
  }
  assert(frameTimes.size() >= 1);
  assert(frameTimes.size() <= FRAME_COUNT);

  float avgTicksPerFrame =
      std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0f) /
      frameTimes.size();
  float avgFps = 1.0f / (avgTicksPerFrame / 1000.0f);

  std::stringstream sstr;
  sstr << std::fixed << std::setprecision(1) << "Current FPS: " << avgFps;

  return sstr.str();
}

void EditorUIManager::checkButtons() {
  // is there a block
  // grid report interaction between you and mouse
  // if not -1, -1, call Roshan's function with grid

  if (cur_editor_button != LevelEditButtonIndex::LAST_IDX) {
    Vector2D<int> coords = EditorManager::getInstance()
                               .getCurrentLevel()
                               ->getGridRenderComponent()
                               ->getGridCoords();
    if (coords.x != -1 && coords.y != -1) {
      EditorManager::getInstance().updateCurrentLevel(coords, getLevelDataFromEditButtonIdx(cur_editor_button));
      cur_editor_button = LevelEditButtonIndex::LAST_IDX;
    }
  }
  if (returnButton->IsSelected()) {
    returnButton->isClicked();
    EditorManager::getInstance().setEditorState(
        EditorManager::EditorState::Menu);
    EditorManager::getInstance().clearLevel();
  } else if (editorButton->IsSelected()) {
    editorButton->isClicked();
    EditorManager::getInstance().setEditorState(
        EditorManager::EditorState::LevelEditor);
  } else if (selectLevel1Button->IsSelected()) {
    selectLevel1Button->isClicked();
    EditorManager::getInstance().setCurrentLevelVal(1);
  } else if (selectLevel2Button->IsSelected()) {
    selectLevel2Button->isClicked();
    EditorManager::getInstance().setCurrentLevelVal(2);
  } else if (selectLevel3Button->IsSelected()) {
    selectLevel3Button->isClicked();
  EditorManager::getInstance().setCurrentLevelVal(3);
  } else {
    bool editButtonWasSelected = false;
    for (int idx = 0; idx < LAST_IDX; idx++) {
      LevelEditButton& button = editor_buttons.at(idx);
      if (button.IsSelected() && idx != cur_editor_button) {
        button.isClicked();
        editButtonWasSelected = true;
        cur_editor_button = LevelEditButtonIndex(idx);
      }
    }

    if (!editButtonWasSelected) {
      cur_editor_button = LAST_IDX;
    }
  }
}

LevelItem EditorUIManager::getLevelDataFromEditButtonIdx(LevelEditButtonIndex levelEditButtonIdx) {
  switch(levelEditButtonIdx) {
//    case UNDO:
//      return LevelItem::NONE;
//    case REDO:
//      return LevelItem::NONE;
    case ERASE:
      return LevelItem::NOBLOCK;
//    case MOVE:
//      return LevelItem::NONE;
    case TILE1:
      return LevelItem::TILE1;
    case TILE2:
      return LevelItem::TILE2;
    case TILE3:
      return LevelItem::TILE3;
    case TILEX:
      return LevelItem::TILEX;
    case TILEY:
      return LevelItem::TILEY;
    case TILEZ:
      return LevelItem::TILEZ;
    case JACK:
      return LevelItem::JACK;
    case ZOMBIE:
      return LevelItem::PATROLZOMBIE;
    default:
      return LevelItem::NONE;
  }
}
