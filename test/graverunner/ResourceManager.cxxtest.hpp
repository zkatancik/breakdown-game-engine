#include <SDL.h>
#include <cxxtest/TestSuite.h>

#include <string>

#include "graverunner/ResourceManager.hpp"

class ResourceManagerTestSuite : public CxxTest::TestSuite {
 public:
  const float EPSILON = 0.001f;
  const int screenWidth = 1280;
  const int screenHeight = 720;
  SDL_Window* testWindow = nullptr;
  SDL_Renderer* testRenderer = nullptr;

  static ResourceManagerTestSuite* createSuite() {
    auto suite = new ResourceManagerTestSuite();
    int success = 0;
    success += SDL_Init(SDL_INIT_EVERYTHING);
    success += TTF_Init();
    success += Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TS_ASSERT_EQUALS(success, 0);

    suite->testWindow = SDL_CreateWindow(
        "ResourceManager Test Window", 100, 100, suite->screenWidth,
        suite->screenHeight, SDL_WINDOW_HIDDEN);
    TS_ASSERT_DIFFERS(suite->testWindow, nullptr);

    suite->testRenderer =
        SDL_CreateRenderer(suite->testWindow, -1, SDL_RENDERER_ACCELERATED);
    TS_ASSERT_DIFFERS(suite->testRenderer, nullptr);
    return suite;
  }

  static void destroySuite(ResourceManagerTestSuite* suite) {
    SDL_DestroyRenderer(suite->testRenderer);
    // Destroy window
    SDL_DestroyWindow(suite->testWindow);
    Mix_CloseAudio();
    Mix_Quit();
    // Point gWindow to NULL to ensure it points to nothing.
    suite->testRenderer = nullptr;
    suite->testWindow = nullptr;
    // Quit SDL subsystems
    SDL_Quit();
  }

  // --------------------- ResourceManager TESTS
  // -----------------------------------

  void testStartup() {
    {
      bool hasStarted = ResourceManager::getInstance().startUp(nullptr);
      TS_ASSERT_EQUALS(hasStarted, false);
    }
    {
      auto testWindow = SDL_CreateWindow("ResourceManager Test Window", 100,
                                         100, 500, 500, SDL_WINDOW_HIDDEN);
      TS_ASSERT_DIFFERS(testWindow, nullptr);

      auto testRenderer =
          SDL_CreateRenderer(testWindow, -1, SDL_RENDERER_ACCELERATED);
      TS_ASSERT_DIFFERS(testRenderer, nullptr);
      ResourceManager& resourceManager = ResourceManager::getInstance();
      bool hasStarted = resourceManager.startUp(testRenderer);
      auto renderer = resourceManager.getRenderer();
      auto missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_EQUALS(hasStarted, true);
      TS_ASSERT_EQUALS(renderer, testRenderer);
      TS_ASSERT_DIFFERS(missingTexture, nullptr);
    }
  }

  void testInstanceUniqueness() {
    {
      ResourceManager& resourceManager1 = ResourceManager::getInstance();
      ResourceManager& resourceManager2 = ResourceManager::getInstance();
      TS_ASSERT_EQUALS(&resourceManager1, &resourceManager2);
    }
  }

  void testBMPTextureFetching() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeInsertion = textureMap->size();
      SDL_Texture* texture =
          resourceManager.getBMPTexture("should_not_be_found.bmp");
      int sizeAfterInsertion = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_EQUALS(texture, missingTexture);
      TS_ASSERT_EQUALS(sizeBeforeInsertion + 1, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeQuery = textureMap->size();
      SDL_Texture* texture =
          resourceManager.getBMPTexture("should_not_be_found.bmp");
      int sizeAfterQuery = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_EQUALS(texture, missingTexture);
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
  }

  void testImageTextureFetching() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeInsertion = textureMap->size();
      SDL_Texture* texture =
          resourceManager.getTexture("should_not_be_found.png");
      int sizeAfterInsertion = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_EQUALS(texture, missingTexture);
      TS_ASSERT_EQUALS(sizeBeforeInsertion + 1, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeQuery = textureMap->size();
      SDL_Texture* texture =
          resourceManager.getTexture("should_not_be_found.png");
      int sizeAfterQuery = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_EQUALS(texture, missingTexture);
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
    /* TODO- Flakey
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeInsertion = textureMap->size();
      SDL_Texture* texture = resourceManager.getTexture("exit.png");
      int sizeAfterInsertion = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_DIFFERS(texture, missingTexture);
      TS_ASSERT_DIFFERS(texture, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeInsertion + 1, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeQuery = textureMap->size();
      SDL_Texture* texture = resourceManager.getTexture("exit.png");
      int sizeAfterQuery = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_DIFFERS(texture, missingTexture);
      TS_ASSERT_DIFFERS(texture, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }*/
  }

  void testTextureDeletion() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadImageTexture("should_not_be_found.png");
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval - 1, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadImageTexture("should_not_be_found.png");
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadImageTexture("should_not_be_found.bmp");
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval - 1, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadImageTexture("should_not_be_found.bmp");
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadImageTexture("exit.png");
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval - 1, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadImageTexture("exit.png");
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval, sizeAfterRemoval);
    }
  }

  void testFontTextureFetching() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeInsertion = textureMap->size();
      SDL_Texture* texture = resourceManager.getTextTexture(
          "Test Message", "should_not_be_found.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterInsertion = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_EQUALS(texture, missingTexture);
      TS_ASSERT_EQUALS(sizeBeforeInsertion + 1, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeQuery = textureMap->size();
      SDL_Texture* texture = resourceManager.getTextTexture(
          "Test Message", "should_not_be_found.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterQuery = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_EQUALS(texture, missingTexture);
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeInsertion = textureMap->size();
      SDL_Texture* texture = resourceManager.getTextTexture(
          "Test Message", "kenpixel_mini_square.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterInsertion = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_DIFFERS(texture, missingTexture);
      TS_ASSERT_DIFFERS(texture, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeInsertion + 1, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeQuery = textureMap->size();
      SDL_Texture* texture = resourceManager.getTextTexture(
          "Test Message", "kenpixel_mini_square.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterQuery = textureMap->size();
      const SDL_Texture* missingTexture = resourceManager.getMissingTexture();
      TS_ASSERT_DIFFERS(texture, missingTexture);
      TS_ASSERT_DIFFERS(texture, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
  }

  void testFontTextureDeletion() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadTTFTextTexture(
          "Test Message", "should_not_be_found.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval - 1, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadTTFTextTexture(
          "Test Message", "should_not_be_found.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadTTFTextTexture(
          "Test Message", "kenpixel_mini_square.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval - 1, sizeAfterRemoval);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto textureMap = resourceManager.getTexturesMap();
      int sizeBeforeRemoval = textureMap->size();
      resourceManager.unloadTTFTextTexture(
          "Test Message", "kenpixel_mini_square.ttf", {255, 255, 255, 0}, 32);
      int sizeAfterRemoval = textureMap->size();
      TS_ASSERT_EQUALS(sizeBeforeRemoval, sizeAfterRemoval);
    }
  }

  void testMusicFetching() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeInsertion = musicMap->size();
      Mix_Music* music = resourceManager.getMusic("should_not_be_found.mp3");
      int sizeAfterInsertion = musicMap->size();
      TS_ASSERT_EQUALS(music, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeInsertion + 1, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeInsertion = musicMap->size();
      Mix_Music* music = resourceManager.getMusic("should_not_be_found.mp3");
      int sizeAfterInsertion = musicMap->size();
      TS_ASSERT_EQUALS(music, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeInsertion, sizeAfterInsertion);
    }

    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeQuery = musicMap->size();
      auto music = resourceManager.getMusic(
          "251461__joshuaempyre__arcade-music-loop.wav");
      int sizeAfterQuery = musicMap->size();
      TS_ASSERT_DIFFERS(music, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeQuery + 1, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeQuery = musicMap->size();
      auto music = resourceManager.getMusic(
          "251461__joshuaempyre__arcade-music-loop.wav");
      int sizeAfterQuery = musicMap->size();
      TS_ASSERT_DIFFERS(music, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
  }

  void testMusicDeletion() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeQuery = musicMap->size();
      resourceManager.unloadMusic("should_not_be_found.mp3");
      int sizeAfterQuery = musicMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery - 1, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeQuery = musicMap->size();
      resourceManager.unloadMusic("should_not_be_found.mp3");
      int sizeAfterQuery = musicMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeQuery = musicMap->size();
      resourceManager.unloadMusic(
          "251461__joshuaempyre__arcade-music-loop.wav");
      int sizeAfterQuery = musicMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery - 1, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto musicMap = resourceManager.getMusicMap();
      int sizeBeforeQuery = musicMap->size();
      resourceManager.unloadMusic(
          "251461__joshuaempyre__arcade-music-loop.wav");
      int sizeAfterQuery = musicMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
  }

  void testChunkFetching() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeInsertion = chunkMap->size();
      Mix_Chunk* chunk = resourceManager.getChunk("should_not_be_found.wav");
      int sizeAfterInsertion = chunkMap->size();
      TS_ASSERT_EQUALS(chunk, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeInsertion + 1, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeInsertion = chunkMap->size();
      Mix_Chunk* chunk = resourceManager.getChunk("should_not_be_found.wav");
      int sizeAfterInsertion = chunkMap->size();
      TS_ASSERT_EQUALS(chunk, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeInsertion, sizeAfterInsertion);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeQuery = chunkMap->size();
      auto chunk = resourceManager.getChunk("BrickHit_SFX.mp3");
      int sizeAfterQuery = chunkMap->size();
      TS_ASSERT_DIFFERS(chunk, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeQuery + 1, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeQuery = chunkMap->size();
      auto chunk = resourceManager.getChunk("BrickHit_SFX.mp3");
      int sizeAfterQuery = chunkMap->size();
      TS_ASSERT_DIFFERS(chunk, nullptr);
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
  }

  void testChunkDeletion() {
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeQuery = chunkMap->size();
      resourceManager.unloadChunk("should_not_be_found.wav");
      int sizeAfterQuery = chunkMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery - 1, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeQuery = chunkMap->size();
      resourceManager.unloadChunk("should_not_be_found.wav");
      int sizeAfterQuery = chunkMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeQuery = chunkMap->size();
      resourceManager.unloadChunk("BrickHit_SFX.mp3");
      int sizeAfterQuery = chunkMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery - 1, sizeAfterQuery);
    }
    {
      ResourceManager& resourceManager = ResourceManager::getInstance();
      auto chunkMap = resourceManager.getChunkMap();
      int sizeBeforeQuery = chunkMap->size();
      resourceManager.unloadChunk("BrickHit_SFX.mp3");
      int sizeAfterQuery = chunkMap->size();
      TS_ASSERT_EQUALS(sizeBeforeQuery, sizeAfterQuery);
    }
  }

  void testShutDown() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    for (int i = 0; i < 10; i++) {
      auto i_string = std::to_string(i);
      resourceManager.getTexture(i_string + ".png");
      resourceManager.getTextTexture("Test Message", i_string + ".tff",
                                     {255, 255, 255, 0}, 32);
      resourceManager.getMusic(i_string + ".mp3");
      resourceManager.getChunk(i_string + ".wav");
    }

    resourceManager.shutDown();
    auto textureMap = resourceManager.getTexturesMap();
    auto musicMap = resourceManager.getMusicMap();
    auto chunkMap = resourceManager.getChunkMap();
    auto renderer = resourceManager.getRenderer();
    auto missingTexture = resourceManager.getMissingTexture();
    TS_ASSERT_EQUALS(resourceManager.hasStarted(), false);
    TS_ASSERT_EQUALS(textureMap->empty(), true);
    TS_ASSERT_EQUALS(musicMap->empty(), true);
    TS_ASSERT_EQUALS(chunkMap->empty(), true);
    TS_ASSERT_EQUALS(renderer, nullptr);
    TS_ASSERT_EQUALS(missingTexture, nullptr);
  }
};