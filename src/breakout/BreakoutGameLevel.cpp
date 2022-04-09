#include "breakout/BreakoutGameLevel.hpp"

#include <base/RemoveOnCollideComponent.hpp>

const int MAX_LEVEL = 4;
const int EASY_BALL_X = 200;
const int EASY_BALL_Y = 200;
const int MEDIUM_BALL_X = 300;
const int MEDIUM_BALL_Y = 300;
const int HARD_BALL_X = 400;
const int HARD_BALL_Y = 400;

void BreakoutGameLevel::initialize() {
  finalize();
  BreakoutLevelData levelData;
  loadLevel(&levelData, mLevelNumber);

  rowsOfBlocks = levelData.rowCount;
  blocksPerRow = levelData.colCount;
  numBlocksLeft = levelData.numOfblocks;
  std::shared_ptr<GameObject> paddle;
  // Create UI elements
  addObject(createLevelIndicatorObject());
  auto livesIndicatorSharedPtr = createLivesIndicatorObject();
  livesIndicator = livesIndicatorSharedPtr->weak_from_this();
  addObject(livesIndicatorSharedPtr);
  auto scoreIndicatorSharedPtr = createScoreIndicatorObject();
  scoreIndicator = scoreIndicatorSharedPtr->weak_from_this();
  addObject(scoreIndicatorSharedPtr);
  // Create ball and paddle
  switch (gameDifficulty_) {
    case GameDifficulty::Easy:
    default:
      paddle = std::make_shared<Paddle>(*this, w(), h(), 200, 400);
      break;
    case GameDifficulty::Medium:
      paddle = std::make_shared<Paddle>(*this, w(), h(), 150, 500);
      break;
    case GameDifficulty::Hard:
      paddle = std::make_shared<Paddle>(*this, w(), h(), 100, 600);
      break;
  }
  addObject(paddle);
  auto ballObject = createBallObject();
  addObject(ballObject);

  // dynamic y placement of blocks
  int y = 100;
  int count = 1;
  int color = 3;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = (w() - (blocksPerRow * 64)) / 2;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = levelData.blocks[(i * blocksPerRow) + j];
      if (b.block_Type != BreakoutBlockType::NoBlock) {
        std::shared_ptr<BreakoutBlock> block;
        if (b.block_Type == BreakoutBlockType::PlainBlock) {
          block = std::make_shared<BreakoutBlock>(*this, x, y, color, b, 1);
        } else if (b.block_Type == BreakoutBlockType::HardBlock) {
          block = std::make_shared<BreakoutBlock>(*this, x, y, 5, b, 3);
        } else if (b.block_Type == BreakoutBlockType::Wall) {
          block = std::make_shared<BreakoutBlock>(*this, x, y, 6, b, 1);
        }
        auto blockHealthComponent =
            block->getGenericComponent<HealthComponent>();
        blockHealthComponent->setCallbackAtDeath(
            [&,
             scoreIndicator =
                 std::weak_ptr<GameObject>(scoreIndicatorSharedPtr),
             blockType = block->getBlockType(),
             ballObject = ballObject->weak_from_this()]() {
              int increment = blockType == BreakoutBlockType::HardBlock ? 3 : 1;
              auto scoreVarComponent =
                  scoreIndicator.lock()
                      ->getGenericComponent<GameVariableComponent<int>>();
              scoreVarComponent->setVariable(scoreVarComponent->getVariable() +
                                             increment);
              numBlocksLeft--;
              if (numBlocksLeft == 0) {
                ballObject.lock()->physicsComponent()->setVx(0);
                ballObject.lock()->physicsComponent()->setVy(0);
              }
            });
        addObject(block);
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
  // Add Boundaries
  auto leftMostBoundary =
      std::make_shared<GameObject>(*this, -1, 0, 1, 3 * h(), ReflectingWallTag);
  leftMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *leftMostBoundary, b2_staticBody, false, 0.f, 10.f));
  addObject(leftMostBoundary);

  auto rightMostBoundary = std::make_shared<GameObject>(
      *this, w(), 0, 1, 3 * h(), ReflectingWallTag);
  rightMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *rightMostBoundary, b2_staticBody, false, 0.f, 10.f));
  addObject(rightMostBoundary);

  auto topMostBoundary = std::make_shared<GameObject>(*this, -1, -1, 3 * w(), 1,
                                                      ReflectingWallTag);
  topMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *topMostBoundary, b2_staticBody, false, 0.f, 10.f));
  addObject(topMostBoundary);

  // Add Bottom Boundary
  auto BottomMostBoundary =
      std::make_shared<GameObject>(*this, -1, h(), 3 * w(), 1, BottomWallTag);
  BottomMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *BottomMostBoundary, b2_staticBody, true, 0.f, 10.f));

  auto removeOnCollideComponent =
      std::make_shared<RemoveOnCollideComponent>(*BottomMostBoundary, BallTag);
  BottomMostBoundary->addGenericComponent(removeOnCollideComponent);

  auto reduceLifeOnCollideLambda =
      [&, livesIndicator = std::weak_ptr<GameObject>(livesIndicatorSharedPtr)](
          Level &level, std::shared_ptr<GameObject> obj) {
        auto livesVarComponent =
            livesIndicator.lock()
                ->getGenericComponent<GameVariableComponent<int>>();
        livesVarComponent->setVariable(livesVarComponent->getVariable() - 1);
        Mix_PlayChannel(1,
                        ResourceManager::getInstance().getChunk(
                            "2DBreakout/SFX/LifeLost_SFX.mp3"),
                        0);
        if (livesVarComponent->getVariable() > 0) {
          level.addObject(createBallObject());
        }
      };
  auto reduceLifeOnCollideComponent =
      std::make_shared<PerformHookOnCollideComponent>(
          *BottomMostBoundary, BallTag, reduceLifeOnCollideLambda);
  BottomMostBoundary->addGenericComponent(reduceLifeOnCollideComponent);
  addObject(BottomMostBoundary);
}
std::shared_ptr<Ball> BreakoutGameLevel::createBallObject() {
  switch (gameDifficulty_) {
    case GameDifficulty::Easy:
    default:
      return std::make_shared<Ball>(*this, 100, 75, EASY_BALL_X, EASY_BALL_Y);
    case GameDifficulty::Medium:
      return std::make_shared<Ball>(*this, 100, 75, MEDIUM_BALL_X,
                                    MEDIUM_BALL_Y);
    case GameDifficulty::Hard:
      return std::make_shared<Ball>(*this, 100, 75, HARD_BALL_X, HARD_BALL_Y);
  }
}

std::shared_ptr<GameObject> BreakoutGameLevel::createLevelIndicatorObject() {
  auto levelIndicator =
      std::make_shared<GameObject>(*this, 10, 10, 50, 50, TextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*levelIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  levelIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Level: " + std::to_string(mLevelNumber);
  auto textComponent = std::make_shared<TextComponent>(
      *levelIndicator, levelMessage, 32, "2DBreakout/Fonts/Gageda.ttf",
      textRenderer);
  levelIndicator->addGenericComponent(textComponent);
  return levelIndicator;
}

std::shared_ptr<GameObject> BreakoutGameLevel::createLivesIndicatorObject() {
  auto livesIndicator =
      std::make_shared<GameObject>(*this, 10, 50, 50, 50, TextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*livesIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  livesIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Lives: " + std::to_string(livesPerGame);
  auto textComponent = std::make_shared<TextComponent>(
      *livesIndicator, levelMessage, 32, "2DBreakout/Fonts/Gageda.ttf",
      textRenderer);
  livesIndicator->addGenericComponent(textComponent);
  auto gameVariableComponent = std::make_shared<GameVariableComponent<int>>(
      *livesIndicator, livesPerGame);
  livesIndicator->addGenericComponent(gameVariableComponent);
  std::weak_ptr<GameVariableComponent<int>> gameVariableComponentWeak(
      gameVariableComponent);
  std::weak_ptr<TextComponent> textComponentWeak(textComponent);
  gameVariableComponent->setUpdateCallBack(
      [gameVariableComponentWeak, textComponentWeak] {
        textComponentWeak.lock()->SetMText(
            "Lives: " +
            std::to_string(gameVariableComponentWeak.lock()->getVariable()));
      });
  return livesIndicator;
}
std::shared_ptr<GameObject> BreakoutGameLevel::createScoreIndicatorObject() {
  auto scoreIndicator =
      std::make_shared<GameObject>(*this, 10, 90, 50, 50, TextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*scoreIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  scoreIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Score: " + std::to_string(livesPerGame);
  auto textComponent = std::make_shared<TextComponent>(
      *scoreIndicator, levelMessage, 32, "2DBreakout/Fonts/Gageda.ttf",
      textRenderer);
  scoreIndicator->addGenericComponent(textComponent);
  auto gameVariableComponent =
      std::make_shared<GameVariableComponent<int>>(*scoreIndicator, 0);
  scoreIndicator->addGenericComponent(gameVariableComponent);
  std::weak_ptr<GameVariableComponent<int>> gameVariableComponentWeak(
      gameVariableComponent);
  std::weak_ptr<TextComponent> textComponentWeak(textComponent);
  gameVariableComponent->setUpdateCallBack(
      [gameVariableComponentWeak, textComponentWeak] {
        textComponentWeak.lock()->SetMText(
            "Score: " +
            std::to_string(gameVariableComponentWeak.lock()->getVariable()));
      });
  return scoreIndicator;
}

bool BreakoutGameLevel::isLevelInProgress() {
  int numLivesLeft = livesIndicator.lock()
                         ->getGenericComponent<GameVariableComponent<int>>()
                         ->getVariable();
  return numLivesLeft > 0 && numBlocksLeft > 0;
}
int BreakoutGameLevel::getScore() {
  return scoreIndicator.lock()
      ->getGenericComponent<GameVariableComponent<int>>()
      ->getVariable();
}
