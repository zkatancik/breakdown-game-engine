#include "custom/TdLevel.hpp"

#include <box2d/b2_body.h>

#include "base/GameVariableComponent.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"

// void TdLevel::initialize() {
//   TdLevelData levelData;
//   loadLevel(&levelData, currentLevelNumber);

//   int rowsOfBlocks = levelData.rowCount;
//   int blocksPerRow = levelData.colCount;
//   Vector2D<int> blockSize = levelData.blockSize;

//   // Create indicators
//   auto keysIndicator = createKeyIndicatorObject();
//   auto levelIndicator = createLevelIndicatorObject();
//   addObject(levelIndicator);
//   addObject(keysIndicator);
//   initialNumExits = 0;

//   // auto background =
//   //     std::make_shared<GameObject>(*this, 0, 0, 1280, 768, TdBGTag);
//   // auto bg_renderer =
//   std::make_shared<TextureRenderComponent>(*background);

//   //
//   bg_renderer->setRenderMode(TextureRenderComponent::RenderMode::WHOLE_WIDTH);
//   // background->setRenderComponent(bg_renderer);
//   // bg_renderer->setTexture(ResourceManager::getInstance().getTexture(
//   //     "Graverunner/graveyardtiles/png/BG.jpg"));

//   // addObject(background);

//   // Place Level Boundaries (need solid physics component to be considered
//   for
//   // collision) Left-most boundary
//   auto leftMostBoundary = std::make_shared<GameObject>(
//       *this, -1, 0, 1, float(rowsOfBlocks * levelData.blockSize.y),
//       TdLevelBoundaryTag);
//   leftMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
//       *leftMostBoundary, b2BodyType::b2_staticBody, false));
//   leftMostBoundary->addGenericComponent(
//       std::make_shared<RemoveOnCollideComponent>(*leftMostBoundary,
//                                                  TdBulletTag));
//   addObject(leftMostBoundary);
//   // Right-most boundary
//   auto rightMostBoundary = std::make_shared<GameObject>(
//       *this, float(blocksPerRow * levelData.blockSize.x), 0, 1,
//       float(rowsOfBlocks * levelData.blockSize.y), TdLevelBoundaryTag);
//   rightMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
//       *rightMostBoundary, b2BodyType::b2_staticBody, false));
//   addObject(rightMostBoundary);
//   rightMostBoundary->addGenericComponent(
//       std::make_shared<RemoveOnCollideComponent>(*rightMostBoundary,
//                                                  TdBulletTag));

//   // Place the game objects/environment (blocks, keys, exit)
//   int y = 0;
//   int count = 1;
//   for (int i = 0; i < rowsOfBlocks; i++) {
//     int x = 0;
//     for (int j = 0; j < blocksPerRow; j++) {
//       auto b = levelData.blocks[(i * blocksPerRow) + j];
//       if (b.block_Type != TdBlockType::NoBlock) {
//         std::shared_ptr<GameObject> obj;
//         if (b.block_Type == TdBlockType::PlainBlock ||
//             b.block_Type == TdBlockType::Wall) {
//           obj = std::make_shared<TdBlock>(*this, x, y, b, blockSize);
//         } else if (b.block_Type == TdBlockType::Key) {
//           obj = std::make_shared<KeyBlock>(*this, x, y, blockSize);
//           auto increaseKeyIndicatorLambda =
//               [&, keysIndicator = std::weak_ptr<GameObject>(keysIndicator)](
//                   Level& level, std::shared_ptr<GameObject> obj) {
//                 auto keysVarComponent =
//                     keysIndicator.lock()
//                         ->getGenericComponent<GameVariableComponent<int>>();
//                 keysVarComponent->setVariable(keysVarComponent->getVariable()
//                 +
//                                               1);
//               };
//           obj->addGenericComponent(
//               std::make_shared<PerformHookOnCollideComponent>(
//                   *obj, TdJackTag, increaseKeyIndicatorLambda));
//         } else if (b.block_Type == TdBlockType::Exit) {
//           obj = std::make_shared<ExitBlock>(*this, x, y, blockSize);
//           initialNumExits++;
//         }
//         addObject(obj);
//       }
//       x = x + blockSize.x;
//     }
//     count++;
//     y = y + blockSize.y;
//   }

//   // Place Jack
//   auto jack = std::make_shared<Jack>(
//       *this, blockSize.x * levelData.playerStartPosition.x,
//       blockSize.y * levelData.playerStartPosition.y, blockSize.x,
//       blockSize.y);
//   mJack = std::weak_ptr(jack);
//   addObject(jack);

//   // Place Enemies end points
//   for (size_t i = 0; i < levelData.enemyStartPositions.size(); i = i + 2) {
//     std::vector<std::pair<float, float>> maleZombie1Path = {
//         {levelData.enemyStartPositions[i + 1].x * blockSize.x,
//          levelData.enemyStartPositions[i + 1].y * blockSize.y}};

//     std::shared_ptr<PatrolZombie> maleZombie =
//     std::make_shared<PatrolZombie>(
//         *this, blockSize.x * levelData.enemyStartPositions[i].x,
//         blockSize.y * levelData.enemyStartPositions[i].y, blockSize.x,
//         blockSize.y, maleZombie1Path, jack);
//     addObject(maleZombie);
//   }

//   // Place Follower Enemies end points
//   for (size_t i = 0; i < levelData.followerEnemyStartPositions.size();
//        i = i + 2) {
//     std::vector<std::pair<float, float>> maleZombie1Path = {
//         {levelData.followerEnemyStartPositions[i + 1].x * blockSize.x,
//          levelData.followerEnemyStartPositions[i + 1].y * blockSize.y}};

//     std::shared_ptr<FollowerZombie> maleZombie =
//         std::make_shared<FollowerZombie>(
//             *this, blockSize.x * levelData.followerEnemyStartPositions[i].x,
//             blockSize.y * levelData.followerEnemyStartPositions[i].y,
//             blockSize.x, blockSize.y, maleZombie1Path, jack);
//     addObject(maleZombie);
//   }
// }

// bool TdLevel::isLevelWon() const {
//   int curNumExits = 0;
//   bool blocksPresent = false;
//   for (const auto& gameobj : getGameObjects()) {
//     if (gameobj.get()->tag() == TdExitTag) {
//       curNumExits++;
//     }
//     blocksPresent = true;
//   }
//   return blocksPresent && curNumExits < initialNumExits;
// }

// bool TdLevel::isLevelInProgress() const {
//   return mJack.lock()->isAlive() && !isLevelWon();
// }

// std::shared_ptr<GameObject> TdLevel::createLevelIndicatorObject() {
//   auto levelIndicator =
//       std::make_shared<GameObject>(*this, 10, 10, 50, 50, BaseTextTag);
//   auto textRenderer =
//   std::make_shared<TextureRenderComponent>(*levelIndicator);

//   textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
//   levelIndicator->setRenderComponent(textRenderer);
//   std::string levelMessage = "Level: " + std::to_string(currentLevelNumber);
//   auto textComponent = std::make_shared<TextComponent>(
//       *levelIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
//       textRenderer);
//   levelIndicator->addGenericComponent(textComponent);
//   return levelIndicator;
// }

// std::shared_ptr<GameObject> TdLevel::createKeyIndicatorObject() {
//   auto scoreIndicator =
//       std::make_shared<GameObject>(*this, 10, 50, 50, 50, BaseTextTag);
//   auto textRenderer =
//   std::make_shared<TextureRenderComponent>(*scoreIndicator);

//   textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
//   scoreIndicator->setRenderComponent(textRenderer);
//   std::string levelMessage = "Keys Collected: 0";
//   auto textComponent = std::make_shared<TextComponent>(
//       *scoreIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
//       textRenderer);
//   scoreIndicator->addGenericComponent(textComponent);
//   auto gameVariableComponent =
//       std::make_shared<GameVariableComponent<int>>(*scoreIndicator, 0);
//   scoreIndicator->addGenericComponent(gameVariableComponent);
//   std::weak_ptr<GameVariableComponent<int>> gameVariableComponentWeak(
//       gameVariableComponent);
//   std::weak_ptr<TextComponent> textComponentWeak(textComponent);
//   gameVariableComponent->setUpdateCallBack(
//       [gameVariableComponentWeak, textComponentWeak] {
//         textComponentWeak.lock()->SetMText(
//             "Keys Collected: " +
//             std::to_string(gameVariableComponentWeak.lock()->getVariable()));
//       });
//   return scoreIndicator;
// }
