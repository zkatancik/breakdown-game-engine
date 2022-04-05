#include "breakout/LevelData.hpp"

void loadLevel(LevelData *levelData, int level) {
  levelData->blocks.clear();

  const filesystem::path resPath = getResourcePath("2DBreakout/Levels");
  std::string resourceFilename = (resPath / ("Level" + std::to_string(level) + ".txt")).string();

  std::string line;
  std::ifstream myfile (resourceFilename);
  if (myfile.is_open()) {
    int lineCounter = 0;
    while ( std::getline (myfile,line) ) {
      if (lineCounter == 0) {
        levelData->rowCount = std::stoi(line);
        lineCounter++;
        continue;
      } else if (lineCounter == 1) {
        levelData->colCount = std::stoi(line);
        lineCounter++;
        continue;
      } else if (lineCounter == 2) {
        levelData->numOfblocks = std::stoi(line);
        lineCounter++;
        continue;
      }

      // Traverse the string
      for (auto &ch : line) {

        auto data = BlockData();
        if (ch == 'b') {
          //std::cout << ch << " ";
          data.block_Type = BlockType::PlainBlock;
        } else if (ch == ' ') {
          //std::cout << "-" << " ";
          data.block_Type = BlockType::NoBlock;
        } else if (ch == 'w') {
          data.block_Type = BlockType::Wall;
        } else if (ch == 'h') {
          data.block_Type = BlockType::HardBlock;
        }

        levelData->blocks.push_back(data);

      }

      lineCounter++;
      //std::cout << "\n";

    }

    myfile.close();
  } else {
    std::cout << "Unable to open file \n";
  }
}

