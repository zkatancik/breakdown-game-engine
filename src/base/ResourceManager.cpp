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
  const filesystem::path resPath = getResourcePath("");

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
  const filesystem::path resPath = getResourcePath("");

  std::string resource_filename = (resPath / filename).string();

  return resource_filename;
}

Mix_Music *ResourceManager::getMusic(const std::string &path) {
  const filesystem::path resPath = getResourcePath("");

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
  const filesystem::path resPath = getResourcePath("");

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


    // std::cout << "LevelGRID:" << "\n";
    // for (std::vector<LevelItem> row: levelData->levelGrid)
    // {
    //     for (LevelItem val: row) {
    //         std::cout << val << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
//    closeFile(resourceFilename);
//  } else {
//    std::cout << "Unable to open file \n";
//  }
//}

//void ResourceManager::updateLevelFile(LevelData ld,
//                                      Vector2D<int> gridPosition, LevelItem item) {
//
//}

std::string ResourceManager::getTranslation(const std::string &message,
                                            Language language) {
  // Strip away symbols
  std::vector<int> separators{0};
  std::string numbers{"0123456789"};
  for (unsigned int i = 0; i < message.size(); i++) {
    for (char number : numbers) {
      if (message[i] == number)
        separators.push_back(int(i));
    }
  }
  separators.push_back(int(message.size()));
  std::stringstream out;
  for (unsigned int i = 0; i < separators.size() - 1; i++) {
    std::string subMessage = message.substr(separators[i], separators[i + 1] - separators[i]);
    if (subMessage.size() == 1 || subMessage.empty()) {
      out << subMessage;
      continue;
    }
    auto it = localization_.find(subMessage);
    if (it == localization_.end()) {
      std::cerr << "Couldn't find '" << subMessage << "' in the localization database." << std::endl;
      out << subMessage;
    }
    else if (language == Language::ENGLISH)
      out << subMessage;
    else {
      auto subMessage_it = it->second.find(language);
      if (subMessage_it == it->second.end()) {
        std::cerr << "Message '" << subMessage << "' doesn't have translation in "
        << language << std::endl;
        out << subMessage;
      }
      out << subMessage_it->second;
    }
    if (i != 0 && i != message.size())
      out << message[separators[i]];
  }
  return out.str();
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