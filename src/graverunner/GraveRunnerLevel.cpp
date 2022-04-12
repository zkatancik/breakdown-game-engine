#include <box2d/b2_body.h>
#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/Tag.hpp"
#include "graverunner/Jack.hpp"
#include "graverunner/FollowerZombie.hpp"
#include "graverunner/PatrolZombie.hpp"
#include "graverunner/GraveRunnerBlock.hpp"
#include "graverunner/KeyBlock.hpp"
#include "graverunner/ExitBlock.hpp"
#include "base/GameVariableComponent.hpp"

void GraveRunnerLevel::initialize() {
  GraveRunnerLevelData levelData;
  loadLevel(&levelData, currentLevelNumber);

  int rowsOfBlocks = levelData.rowCount;
  int blocksPerRow = levelData.colCount;
  Vector2D<int> blockSize = levelData.blockSize;

  // Create indicators
  auto keysIndicator = createKeyIndicatorObject();
  auto levelIndicator = createLevelIndicatorObject();
  addObject(levelIndicator);
  addObject(keysIndicator);
  initialNumExits = 0;

  auto background =
      std::make_shared<GameObject>(*this, 0, 0, 1280, 768, GraveRunnerBGTag);
  auto bg_renderer = std::make_shared<TextureRenderComponent>(*background);

  bg_renderer->setRenderMode(TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  background->setRenderComponent(bg_renderer);
  bg_renderer->setTexture(ResourceManager::getInstance().getTexture(
      "Graverunner/graveyardtiles/png/BG.jpg"));

  addObject(background);

  // Place Level Boundaries (need solid physics component to be considered for
  // collision) Left-most boundary
  auto leftMostBoundary = std::make_shared<GameObject>(
      *this, -1, 0, 1, float(rowsOfBlocks * levelData.blockSize.y),
      GraveRunnerLevelBoundaryTag);
  leftMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *leftMostBoundary, b2BodyType::b2_staticBody, false));
  leftMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*leftMostBoundary, GraveRunnerBulletTag));
  addObject(leftMostBoundary);
  // Right-most boundary
  auto rightMostBoundary = std::make_shared<GameObject>(
      *this, float(blocksPerRow * levelData.blockSize.x), 0, 1,
      float(rowsOfBlocks * levelData.blockSize.y), GraveRunnerLevelBoundaryTag);
  rightMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *rightMostBoundary, b2BodyType::b2_staticBody, false));
  addObject(rightMostBoundary);
  rightMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*rightMostBoundary,
                                                 GraveRunnerBulletTag));

  // Place the game objects/environment (blocks, keys, exit)
  int y = 0;
  int count = 1;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = 0;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = levelData.blocks[(i * blocksPerRow) + j];
      if (b.block_Type != GraveRunnerBlockType::NoBlock) {
        std::shared_ptr<GameObject> obj;
        if (b.block_Type == GraveRunnerBlockType::PlainBlock ||
        b.block_Type == GraveRunnerBlockType::Wall) {
          obj = std::make_shared<GraveRunnerBlock>(*this, x, y, b, blockSize);
        } else if (b.block_Type == GraveRunnerBlockType::Key) {
          obj = std::make_shared<KeyBlock>(*this, x, y, blockSize);
          auto increaseKeyIndicatorLambda =
              [&, keysIndicator = std::weak_ptr<GameObject>(keysIndicator)](
                  Level &level, std::shared_ptr<GameObject> obj) {
            auto keysVarComponent =
                keysIndicator.lock()
                ->getGenericComponent<GameVariableComponent<int>>();
            keysVarComponent->setVariable(keysVarComponent->getVariable() + 1);
          };
          obj->addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(*obj, GraveRunnerJackTag, increaseKeyIndicatorLambda));
        } else if (b.block_Type == GraveRunnerBlockType::Exit) {
          obj = std::make_shared<ExitBlock>(*this, x, y, blockSize);
          initialNumExits++;
        }
        addObject(obj);
      }
      x = x + blockSize.x;
    }
    count++;
    y = y + blockSize.y;
  }

  // Place Jack
  auto jack = std::make_shared<Jack>(
      *this, blockSize.x * levelData.playerStartPosition.x,
      blockSize.y * levelData.playerStartPosition.y, blockSize.x, blockSize.y);
  mJack = std::weak_ptr(jack);
  addObject(jack);

  // Place Enemies end points
  for (size_t i = 0; i < levelData.enemyStartPositions.size(); i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {levelData.enemyStartPositions[i + 1].x * blockSize.x,
         levelData.enemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<PatrolZombie> maleZombie =
        std::make_shared<PatrolZombie>(*this, blockSize.x * levelData.enemyStartPositions[i].x,
                        blockSize.y * levelData.enemyStartPositions[i].y,
                        blockSize.x, blockSize.y, maleZombie1Path, jack);
    addObject(maleZombie);
  }

  // Place Follower Enemies end points
  for (size_t i = 0; i < levelData.followerEnemyStartPositions.size();
       i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {levelData.followerEnemyStartPositions[i + 1].x * blockSize.x,
         levelData.followerEnemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<FollowerZombie> maleZombie =
        std::make_shared<FollowerZombie>(
            *this,
            blockSize.x * levelData.followerEnemyStartPositions[i].x,
            blockSize.y * levelData.followerEnemyStartPositions[i].y,
            blockSize.x, blockSize.y, maleZombie1Path, jack);
    addObject(maleZombie);
  }
}

bool GraveRunnerLevel::isLevelWon() const {
  int curNumExits = 0;
  bool blocksPresent = false;
  for (const auto& gameobj : getGameObjects()) {
    if (gameobj.get()->tag() == GraveRunnerExitTag) {
      curNumExits++;
    }
    blocksPresent = true;
  }
  return blocksPresent && curNumExits < initialNumExits;
}

bool GraveRunnerLevel::isLevelInProgress() const {
  return mJack.lock()->isAlive() && !isLevelWon();
}

std::shared_ptr<GameObject> GraveRunnerLevel::createLevelIndicatorObject() {
  auto levelIndicator =
      std::make_shared<GameObject>(*this, 10, 10, 50, 50, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*levelIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  levelIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Level: " + std::to_string(currentLevelNumber);
  auto textComponent = std::make_shared<TextComponent>(
      *levelIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
      textRenderer);
  levelIndicator->addGenericComponent(textComponent);
  return levelIndicator;
}

std::shared_ptr<GameObject> GraveRunnerLevel::createKeyIndicatorObject() {
  auto scoreIndicator =
      std::make_shared<GameObject>(*this, 10, 50, 50, 50, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*scoreIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  scoreIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Keys Collected: 0";
  auto textComponent = std::make_shared<TextComponent>(
      *scoreIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
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
            "Keys Collected: " +
            std::to_string(gameVariableComponentWeak.lock()->getVariable()));
      });
  return scoreIndicator;
}
