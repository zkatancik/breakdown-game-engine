#include "breakout/LevelData.hpp"

void loadLevel(BreakoutLevelData *levelData, int level) {
  levelData->levelGrid.clear();
  levelData->blocks.clear();

  levelData->levelNumber = level;

  const filesystem::path resPath = getResourcePath("2DBreakout/Levels");
  std::string resourceFilename = (resPath / ("Level" + std::to_string(level) + ".txt")).string();

  std::string line;
  std::ifstream myfile (resourceFilename);
  if (myfile.is_open()) {
    int lineCounter = 0;
    int colCounter = 0;
    while ( std::getline (myfile,line) ) {
      if (lineCounter == 0) {
        levelData->rowCount = std::stoi(line);
        lineCounter++;
        continue;
      } else if (lineCounter == 1) {
        levelData->colCount = std::stoi(line);

        // specify the default value to fill the vector elements
        levelData->levelGrid.resize(levelData->rowCount, std::vector<BreakoutLevelItem>(levelData->colCount, BreakoutLevelItem::NONE));;

        lineCounter++;
        continue;
      } else if (lineCounter == 2) {
        levelData->numOfblocks = std::stoi(line);
        lineCounter++;
        continue;
      }


      // Traverse the string
      colCounter = 0;
      for (auto &ch : line) {

        auto data = BreakoutBlockData();
        if (ch == '1') {
          data.block_Type = BreakoutBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::BLOCKBLUE;
        } else if (ch == '2') {
          data.block_Type = BreakoutBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::BLOCKRED;
        } else if (ch == '3') {
          data.block_Type = BreakoutBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::BLOCKYELLOW;
        } else if (ch == '4') {
          data.block_Type = BreakoutBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::BLOCKGREEN;
        } else if (ch == '5') {
          data.block_Type = BreakoutBlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::BLOCKPURPLE;
        } else if (ch == '.') {
          data.block_Type = BreakoutBlockType::NoBlock;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::NOBLOCK;
        } else if (ch == 'w') {
          data.block_Type = BreakoutBlockType::Wall;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::WALL;
        } else if (ch == 'h') {
          data.block_Type = BreakoutBlockType::HardBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 3][colCounter] = BreakoutLevelItem::HARDBLOCK;
        }

        levelData->blocks.push_back(data);
        colCounter++;

      }

      lineCounter++;
      //std::cout << "\n";

    }

    myfile.close();
  } else {
    std::cout << "Unable to open file \n";
  }
}

void updateCurrentLevel(BreakoutLevelData *levelData, 
                        Vector2D<int> gridPosition,
                        BreakoutLevelItem item) {
  // Update the Level
  if (item != BreakoutLevelItem::NONE) {
    levelData->levelGrid[gridPosition.x][gridPosition.y] = item;

    //std::cout << "EM:[After - updateCurrentLevel]:" << std::endl;

    // Update the Level File
    updateLevelFile(*levelData, gridPosition, item);
  }
}

/**
 * @brief Update the item in the current level.
 *
 * @param levelNumber  the levelNumber.txt to be updated
 * @param gridPosition the position at which to update item
 * @param item the item to add at above position
 */
void updateLevelFile(BreakoutLevelData ld, Vector2D<int> gridPosition, BreakoutLevelItem item) {

  std::cout << "RS:[updateLevelFile]:" << std::endl;

  const filesystem::path resPath = getResourcePath("levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(ld.levelNumber) + ".txt")).string();

  std::string line;
  std::fstream *myfile = ResourceManager::getInstance().openFile(resourceFilename, std::fstream::out | std::fstream::trunc);

  int lineCounter = 0;

  //std::cout << "RS:updateLevelFile:" << std::endl;

  if (myfile->is_open()) {

    *myfile << std::to_string(ld.rowCount) << std::endl;

    *myfile << std::to_string(ld.colCount) << std::endl;

    *myfile << std::to_string(ld.numOfblocks) << std::endl;

    int i = 0;
    int j = 0;
    for (i = 0; i < ld.rowCount; i++)
    {
      for (j = 0; j < ld.colCount; j++)
      {
        *myfile << (char)ld.levelGrid[i][j];
      }

      if (i != ld.rowCount - 1)
      {
        *myfile << std::endl;
      }

      lineCounter++;
    }

    ResourceManager::getInstance().closeFile(resourceFilename);
  } else {

    // Create a new file.
    std::cout << "Unable to open file \n";
    std::cout << "Creating a new file \n";

  }
}
