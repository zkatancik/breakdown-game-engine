#include "base/ResourceManager.hpp"

ResourceManager &ResourceManager::getInstance() {
  static ResourceManager *instance = new ResourceManager();
  return *instance;
}

bool ResourceManager::startUp(SDL_Renderer *renderer) {
  if (!hasStarted_) {
    if (renderer == nullptr) return false;
    renderer_ = renderer;
    missing_texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET, 1024, 1024);
    if (missing_texture_ == nullptr) return false;
    if (SDL_SetRenderTarget(renderer_, missing_texture_) == -1) return false;
    if (SDL_SetRenderDrawColor(renderer_, 0xFF, 0x00, 0xFF, 0xFF) == -1)
      return false;
    if (SDL_RenderClear(renderer_) == -1) return false;
    if (SDL_SetRenderTarget(renderer_, nullptr) == -1) return false;
    hasStarted_ = true;
  }
  return hasStarted_;
}

bool ResourceManager::hasStarted() { return hasStarted_; }

void ResourceManager::shutDown() {
  if (hasStarted_) {
    unloadAllTexture();
    unloadAllMusic();
    unloadAllChunk();
    closeAllfiles();

    if (missing_texture_ != nullptr) {
      SDL_DestroyTexture(missing_texture_);
      missing_texture_ = nullptr;
    }
    if (renderer_ != nullptr) {
      renderer_ = nullptr;
    }
    hasStarted_ = false;
  }
}

SDL_Texture *ResourceManager::getBMPTexture(const std::string &filename) {
  const filesystem::path resPath = getResourcePath("");

  std::string resourceFilename = (resPath / filename).string();
  const resourceId_t resourceId = getImageTextureId(resourceFilename);
  auto it = textures_.find(resourceId);
  if (it != textures_.end()) {
    return it->second;
  } else {
    SDL_Texture *texture = nullptr;

    SDL_Surface *bmpSurface = SDL_LoadBMP(resourceFilename.c_str());
    if (bmpSurface == nullptr) {
      SDL_Log("Failed to allocate surface");
      texture = missing_texture_;
    } else {
      texture = SDL_CreateTextureFromSurface(renderer_, bmpSurface);
      SDL_FreeSurface(bmpSurface);
    }

    textures_.insert(std::make_pair(resourceId, texture));

    return texture;
  }
}

SDL_Texture *ResourceManager::getTexture(const std::string &filename) {
  const filesystem::path resPath = getResourcePath("");

  std::string resourceFilename = (resPath / filename).string();
  const resourceId_t resourceId = getImageTextureId(resourceFilename);

  auto it = textures_.find(resourceId);
  if (it != textures_.end()) {
    return it->second;
  } else {
    SDL_Texture *texture = nullptr;
    texture = IMG_LoadTexture(renderer_, resourceFilename.c_str());

    if (texture == nullptr) {
      SDL_Log("Failed to allocate surface at %s. Triggered at: %s, line %d",
              resourceFilename.c_str(), __FILE__, __LINE__);
      texture = missing_texture_;
    }

    textures_.insert(std::make_pair(resourceId, texture));

    return texture;
  }
}

SDL_Texture *ResourceManager::getTextTexture(const std::string &message,
                                             const std::string &fontFile,
                                             SDL_Color color, int fontSize) {
  // Fetch the font absolute path
  const filesystem::path resPath = getResourcePath("fonts");

  std::string resourceFilename = (resPath / fontFile).u8string();

  // Create the string id for the text
  const resourceId_t resourceId =
      getTTFTextTextureId(message, resourceFilename, color, fontSize);

  auto texture_it = textures_.find(resourceId);
  if (texture_it != textures_.end()) return texture_it->second;

  SDL_Texture *texture;
  TTF_Font *font = TTF_OpenFont(resourceFilename.c_str(), fontSize);
  if (font == nullptr) {
    SDL_Log("Failed to read font from %s", resourceFilename.c_str());
    textures_.insert(std::make_pair(resourceId, missing_texture_));
    return missing_texture_;
  }
  // We need to first render to a surface as that's what TTF_RenderText
  // returns, then load that surface into a texture
  SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);
  if (surf == nullptr) {
    SDL_Log("Failed to make a surface from font located at %s",
            resourceFilename.c_str());
    TTF_CloseFont(font);
    textures_.insert(std::make_pair(resourceId, missing_texture_));
    return missing_texture_;
  }
  texture = SDL_CreateTextureFromSurface(renderer_, surf);
  if (texture == nullptr) {
    SDL_Log("Failed to create a texture from font located at %s",
            resourceFilename.c_str());
    texture = missing_texture_;
  }
  // Clean up the surface
  SDL_FreeSurface(surf);
  // Close the font
  TTF_CloseFont(font);
  // Cache the texture
  textures_.insert(std::make_pair(resourceId, texture));
  return texture;
}

std::string ResourceManager::getFont(const std::string &filename) {
  const filesystem::path resPath = getResourcePath("fonts");

  std::string resource_filename = (resPath / filename).string();

  return resource_filename;
}

Mix_Music *ResourceManager::getMusic(const std::string &path) {
  const filesystem::path resPath = getResourcePath("2DPlatformer_SFX");

  const std::string resourceFilename = (resPath / path).string();
  const resourceId_t resourceId = getSoundId(resourceFilename);

  auto music_it = music_.find(resourceId);
  if (music_it != music_.end()) return music_it->second;

  Mix_Music *music = Mix_LoadMUS(resourceFilename.c_str());
  if (music == nullptr) {
    SDL_Log("Failed to load music at %s. Triggered at: %s, line %d",
            resourceFilename.c_str(), __FILE__, __LINE__);
  }

  music_.insert(std::make_pair(resourceId, music));
  return music;
}

Mix_Chunk *ResourceManager::getChunk(const std::string &path) {
  const filesystem::path resPath = getResourcePath("2DPlatformer_SFX");

  const std::string resourceFilename = (resPath / path).string();
  const resourceId_t resourceId = getSoundId(resourceFilename);

  auto chunk_it = chunk_.find(resourceId);
  if (chunk_it != chunk_.end()) return chunk_it->second;

  Mix_Chunk *chunk = Mix_LoadWAV(resourceFilename.c_str());
  if (chunk == nullptr) {
    SDL_Log("Failed to load chunk at %s. Triggered at: %s, line %d",
            resourceFilename.c_str(), __FILE__, __LINE__);
  }

  chunk_.insert(std::make_pair(resourceId, chunk));
  return chunk;
}

void ResourceManager::unloadImageTexture(const std::string &filename) {
  unloadTextureWithId(getImageTextureId(filename));
}

void ResourceManager::unloadTTFTextTexture(const std::string &message,
                                           const std::string &fontFile,
                                           SDL_Color color, int fontSize) {
  unloadTextureWithId(getTTFTextTextureId(message, fontFile, color, fontSize));
}

void ResourceManager::unloadMusic(const std::string &path) {
  unloadMusicWithId(getSoundId(path));
}

void ResourceManager::unloadChunk(const std::string &path) {
  unloadChunkWithId(getSoundId(path));
}

void ResourceManager::unloadTextureWithId(const resourceId_t &id) {
  auto it = textures_.find(id);
  if (it != textures_.end()) {
    // Don't allocate if the texture is the missing_texture or if it's nullptr
    // and already deallocated
    if (it->second != missing_texture_ || it->second != nullptr)
      SDL_DestroyTexture(it->second);
    textures_.erase(it->first);
  }
}

void ResourceManager::unloadMusicWithId(const resourceId_t &id) {
  auto it = music_.find(id);
  if (it != music_.end()) {
    if (it->second != nullptr) Mix_FreeMusic(it->second);
    music_.erase(it->first);
  }
}

void ResourceManager::unloadChunkWithId(const resourceId_t &id) {
  auto it = chunk_.find(id);
  if (it != chunk_.end()) {
    if (it->second != nullptr) Mix_FreeChunk(it->second);
    chunk_.erase(it->first);
  }
}

void ResourceManager::closeFileWithId(const resourceId_t &id) {
  auto it = fstream_.find(id);
  if (it != fstream_.end()) {
    if (it->second.second != nullptr) {
      it->second.second->close();
      delete it->second.second;
    }
    fstream_.erase(it->first);
  }
}

inline void ResourceManager::unloadAllTexture() {
  while (!textures_.empty()) unloadTextureWithId(textures_.begin()->first);
}

inline void ResourceManager::unloadAllMusic() {
  while (!music_.empty()) unloadMusicWithId(music_.begin()->first);
}

void ResourceManager::unloadAllChunk() {
  while (!chunk_.empty()) unloadChunkWithId(chunk_.begin()->first);
}

void ResourceManager::closeAllfiles() {
  while (!fstream_.empty()) closeFileWithId(fstream_.begin()->first);
}

void ResourceManager::loadLevel(LevelData *levelData, int level) {
  
  levelData->levelGrid.clear();
  levelData->blocks.clear();
  levelData->enemyStartPositions.clear();

  levelData->levelNumber = level;

  const filesystem::path resPath = getResourcePath("levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(levelData->levelNumber) + ".txt")).string();

  std::string line;
  std::fstream *myfile = openFile(resourceFilename, std::ios_base::in);
  if (myfile->is_open()) {
    int lineCounter = 0;
    int colCounter = 0;
    std::string x;
    std::string y;
    while (std::getline(*myfile, line)) {
      if (lineCounter == 0) {
        levelData->rowCount = std::stoi(line);
        lineCounter++;
        continue;
      } else if (lineCounter == 1) {
        levelData->colCount = std::stoi(line);

        // specify the default value to fill the vector elements
        levelData->levelGrid.resize(levelData->rowCount, std::vector<LevelItem>(levelData->colCount, LevelItem::NONE));;

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

      levelData->blockSize = Vector2D<int>(std::stoi(x), std::stoi(y));
      //std::cout << "RS::Level Grid Row Size:" << levelData->levelGrid.size() << "\n";
      //std::cout << "RS::Level Grid Row Size:" << levelData->levelGrid[0].size() << "\n";
      //std::cout << "RS::Linecounter:" << std::to_string(lineCounter) << "\n";

      // Traverse the string
      colCounter = 0;

      for (auto &ch : line) {
        auto data = BlockData();
        if (ch == '1') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILE1;
        } else if (ch == '2') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILE2;
        } else if (ch == '3') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILE3;
        } else if (ch == 'X') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILEX;
        } else if (ch == 'Y') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILEY;
        } else if (ch == 'Z') {
          data.block_Type = BlockType::PlainBlock;
          data.blockNumber = ch;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::TILEZ;
        } else if (ch == '.') {
          data.block_Type = BlockType::NoBlock;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::NOBLOCK;
        } else if (ch == 'W') {
          data.block_Type = BlockType::Wall;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::WALL;
        } else if (ch == 'H') {
          data.block_Type = BlockType::HardBlock;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::HARDBLOCK;
        } else if (ch == 'K') {
          data.block_Type = BlockType::Key;
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::KEY;
        } else if (ch == 'E') {
          // Enemy start position
          data.block_Type = BlockType::NoBlock;
          levelData->enemyStartPositions.push_back(
              Vector2D<int>(colCounter, lineCounter - 4));
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::PATROLZOMBIE;
        } else if (ch == 'F') {
          // Follower Enemy start position
          data.block_Type = BlockType::NoBlock;
          levelData->followerEnemyStartPositions.push_back(
              Vector2D<int>(colCounter, lineCounter - 4));
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::FOLLOWZOMBIE;
        } else if (ch == 'P') {
          data.block_Type = BlockType::NoBlock;
          levelData->playerStartPosition =
              Vector2D<int>(colCounter, lineCounter - 4);
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::JACK;
        } else if (ch == 'G') {
          data.block_Type = BlockType::Exit;
          levelData->levelEndPosition =
              Vector2D<int>(colCounter, lineCounter - 4);
          levelData->levelGrid[lineCounter - 4][colCounter] = LevelItem::EXIT;
        }

        levelData->blocks.push_back(data);
        colCounter++;
      }

      lineCounter++;
      
    }

    // std::cout << "LevelGRID:" << "\n";
    // for (std::vector<LevelItem> row: levelData->levelGrid)
    // {
    //     for (LevelItem val: row) {
    //         std::cout << val << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
    closeFile(resourceFilename);
  } else {
    std::cout << "Unable to open file \n";
  }
}

void ResourceManager::updateLevelFile(LevelData ld,
                                      Vector2D<int> gridPosition, LevelItem item) {

  std::cout << "RS:[updateLevelFile]:" << std::endl;

  const filesystem::path resPath = getResourcePath("levels");
  std::string resourceFilename =
      (resPath / ("level" + std::to_string(ld.levelNumber) + ".txt")).string();

  std::string line;
  std::fstream *myfile = openFile(resourceFilename, std::fstream::out | std::fstream::trunc);

  int lineCounter = 0;
  int colNumber = 0;

  //std::cout << "RS:updateLevelFile:" << std::endl;
  
  if (myfile->is_open()) {

    *myfile << std::to_string(ld.rowCount) << std::endl;
  
    *myfile << std::to_string(ld.colCount) << std::endl;
  
    *myfile << std::to_string(ld.blockSize.x) << std::endl;
  
    *myfile << std::to_string(ld.blockSize.y) << std::endl;

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
    
    closeFile(resourceFilename);
  } else {

    // Create a new file.
    std::cout << "Unable to open file \n";
    std::cout << "Creating a new file \n";
  
  }
}

std::string ResourceManager::getTranslation(const std::string &message,
                                            Language language) {
  auto it = localization_.find(message);
  if (it == localization_.end()) {
    std::cerr << "Couldn't find '" << message << "' in the localization database."
              << std::endl;
    return message;
  }
  if (language == Language::ENGLISH)
    return message;
  else {
    auto message_it = it->second.find(language);
    if (message_it == it->second.end()) {
      std::cerr << "Message '" << message << "' doesn't have translation in "
                << language << std::endl;
      return message;
    }
    return message_it->second;
  }
}

std::fstream *ResourceManager::openFile(const std::string &path,
                                        std::ios_base::openmode flags) {
  resourceId_t fileId = getFStreamId(filesystem::path{path});
  auto it = fstream_.find(fileId);

  if (it != fstream_.end()) {
    // If the flags match, return the fstream
    if (it->second.first == flags) return it->second.second;
    // If the flags don't match, close the fstream and delete it.
    else {
      it->second.second->close();
      delete it->second.second;
      fstream_.erase(it);
    }
  }
  auto *f = new std::fstream(path, flags);
  fstream_.insert({fileId, {flags, f}});
  return f;
}

void ResourceManager::closeFile(const std::string &path) {
  resourceId_t fileId = getFStreamId(filesystem::path{path});
  closeFileWithId(fileId);
}