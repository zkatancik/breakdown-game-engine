#include "editor/TdEnemyEditor.hpp"

#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"

#include "base/Collection.hpp"
#include "editor/TDEnemyCounter.hpp"

void TdEnemyEditor::initialize() {
  loadLevel(&mLevelData, mLevelNumber);
  // Add buttons here:

  int y = 10;
  mCounters.clear();
  for (size_t i = 0; i < mLevelData.enemyWaves.size(); i++) {
    // Add wave label
    auto label = std::make_shared<GameObject>(*this, 2, y, 50, 50, BaseTextTag);
    auto textRenderer = std::make_shared<TextureRenderComponent>(*label);

    textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
    label->setRenderComponent(textRenderer);
    std::string levelMessage = "Wave " + std::to_string(i);
    auto textComponent = std::make_shared<TextComponent>(
        *label, levelMessage, 32, "TD2D/Fonts/madera-tygra.ttf",
        textRenderer);
    label->addGenericComponent(textComponent);
    addObject(label);
    int x = 150;
    mCounters.push_back(std::vector<EnemyCounter>());
    for (int j = 0; j < itemVector.size(); j++) {
      auto it = mLevelData.enemyWaves[i].find(itemVector[j]);
      mCounters[i].push_back(EnemyCounter(*this, x, y, mLevelData.blockSize, itemVector[j],
                                 (it != mLevelData.enemyWaves[i].end()) ? it->second : 0));
      x = x + 250;
      if ((j + 1) % 5 == 0) {
        x = 150;
        y += 80;
      }
    }
  }
  auto editButtonHook = [&] {
    std::vector<std::map<TdLevelItem, int>> waveInfo;
    for (int i = 0; i < mCounters.size(); i++) {
      waveInfo.emplace_back();
      for (int j = 0; j < mCounters[i].size(); j++) {
        waveInfo[i].insert(std::make_pair(mCounters[i][j].getEnemyItem(), mCounters[i][j].getCount()));
      }
    }
    updateEnemiesLevelFile(waveInfo, mLevelNumber);
  };

  addObject(std::make_shared<TdButton>(*this, 1500, 500, 64, 32, "Edit Wave", editButtonHook));
}

void TdEnemyEditor::refreshLevelEditor() {
}
