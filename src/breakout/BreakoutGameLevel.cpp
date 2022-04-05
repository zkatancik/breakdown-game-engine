#include "breakout/BreakoutGameLevel.hpp"

const int MAX_LEVEL = 4;
const int EASY_BALL_X = 200;
const int EASY_BALL_Y = 200;
const int MEDIUM_BALL_X = 4;
const int MEDIUM_BALL_Y = 6;
const int HARD_BALL_X = 6;
const int HARD_BALL_Y = 8;


void BreakoutGameLevel::initialize() {
  finalize();
  LevelData levelData;
  loadLevel(&levelData, mLevelNumber);

  rowsOfBlocks = levelData.rowCount;
  blocksPerRow = levelData.colCount;
  numBlocks = levelData.numOfblocks;
  std::shared_ptr<GameObject> paddle;
  std::shared_ptr<GameObject> ball;

  switch(gameDifficulty_) {
    case GameDifficulty::Easy:
    default:
      paddle = std::make_shared<Paddle>(*this, w(), h(), 200, 208);
      ball = std::make_shared<Ball>(*this, 100, 75, EASY_BALL_X, EASY_BALL_Y);
      break;
    case GameDifficulty::Medium:
      paddle = std::make_shared<Paddle>(*this, w(), h(), 11, 156);
      ball = std::make_shared<Ball>(*this, 100, 75, MEDIUM_BALL_X, MEDIUM_BALL_Y);
      break;
    case GameDifficulty::Hard:
      paddle = std::make_shared<Paddle>(*this, w(), h(), 7, 208);
      ball = std::make_shared<Ball>(*this, 100, 75, HARD_BALL_X, HARD_BALL_Y);
      break;
  }
  addObject(paddle);
  addObject(ball);

  // dynamic y placement of blocks
  int y = 100;
  int count = 1;
  int color = 3;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = (w() - (blocksPerRow * 64)) / 2;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = levelData.blocks[(i * blocksPerRow) + j];
      if (b.block_Type != BlockType::NoBlock) {
        std::shared_ptr<Block> block;
        if (b.block_Type == BlockType::PlainBlock) {
          block = std::make_shared<Block>(*this, x, y, color, b, 1);
          blocksLeft = true;
          addObject(block);
        } else if (b.block_Type == BlockType::HardBlock) {
          block = std::make_shared<Block>(*this, x, y, 5, b, 3);
          addObject(block);
        } else if (b.block_Type == BlockType::Wall) {
          block = std::make_shared<Block>(*this, x, y, 6, b, 0);
          addObject(block);
        }
      }
      x = x + 64;
    }
    if (count == blocksPerColor) {
      color++;
      count = 0;
      if (color > 4) {
        color = 0;
      }
    }
    count++;
    y = y + 32;
  }

  // Add UI Elements
}