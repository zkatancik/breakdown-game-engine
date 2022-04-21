#include "custom/LevelData.hpp"

#include <filesystem>
#include <fstream>

#include "base/ResPath.hpp"
#include "base/ResourceManager.hpp"

TdLevelItem getEnemy(const std::string& enemyTypeStr) {
  if (enemyTypeStr == "S")
    return TdLevelItem::SCORPIONS;
  else if (enemyTypeStr == "W")
    return TdLevelItem::WIZARD;
  else if (enemyTypeStr == "O")
    return TdLevelItem::OGRE;
  else if (enemyTypeStr == "HS")
    return TdLevelItem::HELMETSWORDSMAN;
  else if (enemyTypeStr == "HO")
    return TdLevelItem::HELMETOGRE;
  else if (enemyTypeStr == "SC")
    return TdLevelItem::SWORDCAT;
  else if (enemyTypeStr == "ETC")
    return TdLevelItem::ETCAT;
  else if (enemyTypeStr == "MO")
    return TdLevelItem::MOONOGRE;
  else if (enemyTypeStr == "ETS")
    return TdLevelItem::ETSHURIKEN;
  else if (enemyTypeStr == "HOS")
    return TdLevelItem::HELMETOGRESWORDSMAN;
  else
    return TdLevelItem::NONE;
}

void loadLevel(TdLevelData *levelData, int level) {
  levelData->levelGrid.clear();
  levelData->placableBlockGrid.clear();
  levelData->levelNumber = level;

  const filesystem::path resPath = getResourcePath("TD2D/Levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(levelData->levelNumber) + ".txt"))
          .string();

  std::string towerMapFilename =
      (resPath /
       ("level" + std::to_string(levelData->levelNumber) + "-TowerMap.txt"))
          .string();

  std::string line;
  std::string towerMapline;
  std::fstream *myfile = ResourceManager::getInstance().openFile(
      resourceFilename, std::ios_base::in);
  std::fstream *towerMapfile = ResourceManager::getInstance().openFile(
      towerMapFilename, std::ios_base::in);

  if (myfile->is_open() && towerMapfile->is_open()) {
    int lineCounter = 0;
    int colCounter = 0;
    std::string x;
    std::string y;

    while (std::getline(*myfile, line) &&
           std::getline(*towerMapfile, towerMapline)) {
      if (lineCounter == 0) {
        levelData->rowCount = std::stoi(line);
        lineCounter++;
        continue;
      } else if (lineCounter == 1) {
        levelData->colCount = std::stoi(line);
        // Resize and fill with default level items
        levelData->levelGrid.resize(
            levelData->rowCount, std::vector<TdBlockData>(levelData->colCount));

        levelData->placableBlockGrid.resize(
            levelData->rowCount, std::vector<TdBlockData>(levelData->colCount));

        lineCounter++;
        continue;
      } else if (lineCounter == 2) {
        x = line;
        lineCounter++;
        continue;
      } else if (lineCounter == 3) {
        y = line;
        lineCounter++;
        continue;
      }
      // Done reading metadata, parse & add level items

      levelData->blockSize = Vector2D<int>(std::stoi(x), std::stoi(y));
      colCounter = 0;
      char ch = 0;
      char tmch = 0;

      // Traverse the string
      for (size_t idx = 0; idx < line.size(); idx++) {
        ch = line[idx];
        tmch = towerMapline[idx];

        auto data = TdBlockData();
        auto towerPlacableData = TdBlockData();

        // Read Level File.
        if (ch == '.') {
          data.levelItemType = TdLevelItem::PLAINBLOCK;
          data.blockNumber = ch;
        } else if (ch == '0') {
          data.levelItemType = TdLevelItem::PATHBLOCK0;
          data.blockNumber = ch;
        } else if (ch == '1') {
          data.levelItemType = TdLevelItem::PATHBLOCK1;
          data.blockNumber = ch;
        } else if (ch == '2') {
          data.levelItemType = TdLevelItem::PATHBLOCK2;
          data.blockNumber = ch;
        } else if (ch == '3') {
          data.levelItemType = TdLevelItem::PATHBLOCK3;
          data.blockNumber = ch;
        } else if (ch == '4') {
          data.levelItemType = TdLevelItem::PATHBLOCK4;
          data.blockNumber = ch;
        } else if (ch == '5') {
          data.levelItemType = TdLevelItem::PATHBLOCK5;
          data.blockNumber = ch;
        } else if (ch == '6') {
          data.levelItemType = TdLevelItem::PATHBLOCK6;
          data.blockNumber = ch;
        } else if (ch == '7') {
          data.levelItemType = TdLevelItem::PATHBLOCK7;
          data.blockNumber = ch;
        } else if (ch == '8') {
          data.levelItemType = TdLevelItem::PATHBLOCK8;
          data.blockNumber = ch;
        } else if (ch == '9') {
          data.levelItemType = TdLevelItem::PATHBLOCK9;
          data.blockNumber = ch;
        } else if (ch == 'A') {
          data.levelItemType = TdLevelItem::PATHBLOCKA;
          data.blockNumber = ch;
        } else if (ch == 'T') {
          data.levelItemType = TdLevelItem::ROCKTHROWER;
          data.blockNumber = ch;
        } else {
          std::cerr << "Error- Failed to parse character \"" << ch
                    << "\" in level file at (" << lineCounter << ","
                    << colCounter << ")" << std::endl;
        }

        // Read Tower Map.
        if (tmch == 'X') {
          data.isTowerPlacable = false;

          towerPlacableData.levelItemType = TdLevelItem::NOBLOCK;
          towerPlacableData.isTowerPlacable = false;
          towerPlacableData.blockNumber = ch;

        } else if (tmch == 'O') {
          data.isTowerPlacable = true;

          towerPlacableData.levelItemType = TdLevelItem::PLACETOWER;
          towerPlacableData.isTowerPlacable = true;
          towerPlacableData.blockNumber = ch;

        } else if (tmch == 'S') {
          // Enemy start position
          data.isTowerPlacable = false;

          towerPlacableData.levelItemType = TdLevelItem::START;
          towerPlacableData.isTowerPlacable = false;
          towerPlacableData.blockNumber = ch;

          levelData->startPosition = Vector2D<int>(colCounter, lineCounter - 4);

        } else if (tmch == 'E') {
          // Enemy end position
          data.isTowerPlacable = false;

          towerPlacableData.levelItemType = TdLevelItem::END;
          towerPlacableData.isTowerPlacable = false;
          towerPlacableData.blockNumber = ch;

          levelData->endPosition = Vector2D<int>(colCounter, lineCounter - 4);

        } else {
          std::cerr << "Error- Failed to parse character \"" << tmch
                    << "\" in tower map file at (" << lineCounter << ","
                    << colCounter << ")" << std::endl;
        }

        levelData->levelGrid[lineCounter - 4][colCounter] = data;
        levelData->placableBlockGrid[lineCounter - 4][colCounter] =
            towerPlacableData;

        colCounter++;
      }

      lineCounter++;
    }

    ResourceManager::getInstance().closeFile(resourceFilename);
    ResourceManager::getInstance().closeFile(towerMapFilename);
  } else {
    std::cerr << "Unable to open level file and/or tower map file at "
              << resourceFilename << " and " << towerMapFilename << std::endl;
  }
  // Load in enemy waves from file

  std::string enemiesFilename =
      (resPath /
      ("level" + std::to_string(levelData->levelNumber) + "-enemies.txt"))
      .string();

  std::string enemyMapLine;
  std::fstream *enemyFile = ResourceManager::getInstance().openFile(
      enemiesFilename, std::ios_base::in);

  if (enemyFile->is_open()) {
    while (std::getline(*enemyFile, enemyMapLine)) {
      // A map representing each wave
      std::map<TdLevelItem, int> waveInfo;
      // Extract map entries
      // Code from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
      size_t pos = 0;
      std::string mapElement;
      while ((pos = enemyMapLine.find(',')) != std::string::npos) {
        mapElement = enemyMapLine.substr(0, pos);
        // Find the enemy type and number of enemies in the wave
        size_t colonPos = mapElement.find(':');
        std::string enemyTypeStr = mapElement.substr(0, colonPos);
        int numEnemies = std::stoi(mapElement.substr(colonPos + 1, std::string::npos));
        // Find the appropriate Enum for enemyType String
        waveInfo.insert(std::make_pair(getEnemy(enemyTypeStr), numEnemies));
        enemyMapLine.erase(0, pos + 1);
      }
      levelData->enemyWaves.push_back(waveInfo);
    }
    ResourceManager::getInstance().closeFile(enemiesFilename);

    // Load Enemy Paths
    std::string enemiesPathFilename =
      (resPath /
      ("level" + std::to_string(levelData->levelNumber) + "-enemyPaths.txt"))
      .string();
  
    std::string enemyPathLine;
    std::fstream *enemyPathFile = ResourceManager::getInstance().openFile(
      enemiesPathFilename, std::ios_base::in);
  
    if (enemyPathFile->is_open()) {
      while (std::getline(*enemyPathFile, enemyPathLine)) {
        // Read Line
        std::vector<Vector2D<int>> linePath;
        size_t pos = 0;
        std::string mapElement;

        while ((pos = enemyPathLine.find(';')) != std::string::npos) {
          mapElement = enemyPathLine.substr(0, pos);
      
          // Find the enemy type and number of enemies in the wave
          size_t colonPos = mapElement.find(',');

          int x = std::stoi(mapElement.substr(0, colonPos));
          int y = std::stoi(mapElement.substr(colonPos + 1, std::string::npos));
          // Find the appropriate Enum for enemyType String
          linePath.push_back(Vector2D<int>(y,x));
          enemyPathLine.erase(0, pos + 1);
        }
        levelData->enemyPossiblePaths.push_back(linePath);
      }
    } else {
      std::cerr << "Failed to open enemies path file at " << enemiesPathFilename << std::endl;
    }

    ResourceManager::getInstance().closeFile(enemiesPathFilename);
  }
  else {
    std::cerr << "Failed to open enemies file at " << enemiesFilename << std::endl;
  }
}

std::string getItemChar(
    TdLevelItem item) {
  switch (item) {
    // case TdLevelItem::NONE:
    //   return "";
    case TdLevelItem::NOBLOCK:
      return "X";
    case TdLevelItem::PLAINBLOCK:
      return ".";
    case TdLevelItem::PATHBLOCK0:
      return "0";
    case TdLevelItem::PATHBLOCK1:
      return "1";
    case TdLevelItem::PATHBLOCK2:
      return "2";
    case TdLevelItem::PATHBLOCK3:
      return "3";
    case TdLevelItem::PATHBLOCK4:
      return "4";
    case TdLevelItem::PATHBLOCK5:
      return "5";
    case TdLevelItem::PATHBLOCK6:
      return "6";
    case TdLevelItem::PATHBLOCK7:
      return "7";
    case TdLevelItem::PATHBLOCK8:
      return "8";
    case TdLevelItem::PATHBLOCK9:
      return "9";
    case TdLevelItem::PATHBLOCKA:
      return "A";
    case TdLevelItem::PLACETOWER:
      return "O";
    case TdLevelItem::ROCKTHROWER:
      return "T";
    case TdLevelItem::END:
      return "E";
    case TdLevelItem::START:
    case TdLevelItem::SCORPIONS:
      return "S";
    case TdLevelItem::WIZARD:
      return "W";
    case TdLevelItem::OGRE:
      return "O";
    case TdLevelItem::HELMETSWORDSMAN:
      return "HS";
    case TdLevelItem::HELMETOGRE:
      return "HO";
    case TdLevelItem::SWORDCAT:
      return "SC";
    case TdLevelItem::ETCAT:
      return "ETC";
    case TdLevelItem::MOONOGRE:
      return "MO";
    case TdLevelItem::ETSHURIKEN:
      return "ETS";
    case TdLevelItem::HELMETOGRESWORDSMAN:
      return "HOS";
    default:
      std::cerr << "Failed to get Tower Defense block key for item "
                << static_cast<int>(item) << std::endl;
      return "";
  }
}

void updateCurrentLevel(TdLevelData *levelData, 
                        Vector2D<int> gridPosition,
                        TdLevelItem item) {
  // Update the Level
  if (item != TdLevelItem::NONE) {
    // Level Grid
    if (item == TdLevelItem::PLAINBLOCK
        || item == TdLevelItem::NOBLOCK
        || item == TdLevelItem::ROCKTHROWER
        || item == TdLevelItem::PATHBLOCK0
        || item == TdLevelItem::PATHBLOCK1
        || item == TdLevelItem::PATHBLOCK2
        || item == TdLevelItem::PATHBLOCK3
        || item == TdLevelItem::PATHBLOCK4
        || item == TdLevelItem::PATHBLOCK5
        || item == TdLevelItem::PATHBLOCK6
        || item == TdLevelItem::PATHBLOCK7
        || item == TdLevelItem::PATHBLOCK8
        || item == TdLevelItem::PATHBLOCK9
        || item == TdLevelItem::PATHBLOCKA) {
      
      auto data = TdBlockData();
      if (item == TdLevelItem::NOBLOCK)
      {
        data.levelItemType = TdLevelItem::PLAINBLOCK;
      } else {
        data.levelItemType = item;
      }
      data.blockNumber = getItemChar(data.levelItemType);
      data.isTowerPlacable = levelData->placableBlockGrid[gridPosition.x][gridPosition.y].isTowerPlacable;
      levelData->levelGrid[gridPosition.x][gridPosition.y] = data;
      // Update the Level File
      updateLevelFile(*levelData, gridPosition, data.levelItemType);
    } 
    
    // Placeable Grid (Tower Map)
    if (item == TdLevelItem::PLACETOWER
        || item == TdLevelItem::START
        || item == TdLevelItem::NOBLOCK
        || item == TdLevelItem::END) {
      auto towerPlacableData = TdBlockData();
      towerPlacableData.levelItemType = item;
      towerPlacableData.blockNumber = getItemChar(towerPlacableData.levelItemType);
      towerPlacableData.isTowerPlacable = false;
      if (towerPlacableData.levelItemType == TdLevelItem::PLACETOWER)
      {
        towerPlacableData.isTowerPlacable = true;
      }
      levelData->placableBlockGrid[gridPosition.x][gridPosition.y] = towerPlacableData;
      // Update the Level File
      updateLevelFile(*levelData, gridPosition, towerPlacableData.levelItemType);
    }
  }
}

void updateLevelFile(TdLevelData ld, Vector2D<int> gridPosition, TdLevelItem item) {
  const filesystem::path resPath = getResourcePath("TD2D/levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(ld.levelNumber) + ".txt")).string();
  
  std::string towerMapFilename =
      (resPath / ("level" + std::to_string(ld.levelNumber) + "-TowerMap.txt")).string();
  
  std::string line;
  std::fstream *myfile = ResourceManager::getInstance().openFile(resourceFilename, std::fstream::out | std::fstream::trunc);
  std::fstream *towerMapfile = ResourceManager::getInstance().openFile(towerMapFilename, std::fstream::out | std::fstream::trunc);

  int lineCounter = 0;

  if (myfile->is_open() && towerMapfile->is_open()) {

    *myfile << std::to_string(ld.rowCount) << std::endl;
    *towerMapfile << std::to_string(ld.rowCount) << std::endl;

    *myfile << std::to_string(ld.colCount) << std::endl;
    *towerMapfile << std::to_string(ld.colCount) << std::endl;

    *myfile << std::to_string(ld.blockSize.x) << std::endl;
    *towerMapfile << std::to_string(ld.blockSize.x) << std::endl;

    *myfile << std::to_string(ld.blockSize.y) << std::endl;
    *towerMapfile << std::to_string(ld.blockSize.y) << std::endl;

    int i = 0;
    int j = 0;
    for (i = 0; i < ld.rowCount; i++)
    {
      for (j = 0; j < ld.colCount; j++)
      {
        if (getItemChar(ld.levelGrid[i][j].levelItemType) == "")
        {
          std::cout << "Why is" << std::to_string(i) << "," << std::to_string(j) << " None?\n";
        }

        *myfile << getItemChar(ld.levelGrid[i][j].levelItemType);
        *towerMapfile << getItemChar(ld.placableBlockGrid[i][j].levelItemType);
      }

      if (i != ld.rowCount - 1)
      {
        *myfile << std::endl;
        *towerMapfile << std::endl;
      }

      lineCounter++;
    }

    ResourceManager::getInstance().closeFile(resourceFilename);
    ResourceManager::getInstance().closeFile(towerMapFilename);
  } else {

    // Create a new file.
    std::cout << "Unable to open file \n";
    std::cout << "Creating a new file \n";

  }
}
