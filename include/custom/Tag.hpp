#ifndef TD_TAG
#define TD_TAG
#include "base/Tag.hpp"

// The tags in our Tower Defense game.
const static int TdBGTag = hash("TdBackground");
const static int TdBlockTag = hash("TdBlock");
const static int TdEndBlockTag = hash("TdEndBlock");
const static int TdEnemyTag = hash("TdEnemy");
const static int TdBulletTag = hash("TdBullet");
const static int TdToolbarTag = hash("TdToolbarTag");
const static int TdRockThrowerTowerTag = hash("TdRockThrowerTower");
const static int TdAntiTankTowerTag = hash("TdAntiTankTowerTag");
const static int TdEditButtonTag = int(hash("TdEditButton"));
const static int TdStartWaveButtonTag = int(hash("TdStartWaveButton"));
#endif