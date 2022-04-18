#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ResPath.hpp"
#include "SDL_DEBUG.hpp"
#include "TinyMath.hpp"

// Use size_t to keep track of resource IDs in the release version; Use normal
// strings for the debug version
#ifdef _DEBUG
typedef std::string resourceId_t;
#else
typedef std::size_t resourceId_t;
#endif

enum Language { ENGLISH = 0, SPANISH };

/**
 * @brief A class for managing game resources.  Allows access to resources
 * and makes sure there is only one copy of each resource loaded at a
 * time.
 */
class ResourceManager {
 private:
  ResourceManager() = default;  // Private Singleton
  ~ResourceManager() = default;
  ResourceManager(ResourceManager const &) = delete;  // Avoid copy constructor.
  void operator=(ResourceManager const &) =
      delete;                                    // Don't allow copy assignment.
  ResourceManager(ResourceManager &&) = delete;  // Avoid move constructor.
  void operator=(ResourceManager &&) = delete;   // Don't allow move assignment.

  /**
   * @brief Unloads the given texture from the texture map given its string id.
   * If the texture is not present in the texture map this function does
   * nothing. This is made private to keep the hashing mechanism abstracted away
   * from the user.
   * @param id the string id of the entry in the texture map
   */
  void unloadTextureWithId(const resourceId_t &id);

  void unloadMusicWithId(const resourceId_t &id);

  void unloadChunkWithId(const resourceId_t &id);

  void closeFileWithId(const resourceId_t &id);

  /**
   * @brief Gets the string id of an image Texture inside the texture map.
   * This function is kept private to prevent users from using the generated
   * string id directly.
   * @param filename path to the image resource; can be either relative to the
   * resourcePath or absolute
   * @return the string id of the image texture in the texture map
   */
  static inline resourceId_t getImageTextureId(const std::string &filename) {
    const filesystem::path resPath = getResourcePath("");

    std::string resourceFilename = (resPath / filename).u8string();
    std::string stringId = u8"image texture//" + resourceFilename;
#ifdef _DEBUG
    return stringId;
#else
    return hash(stringId);
#endif
  }

  /**
   * @brief Gets the string id of a TTF Text Texture inside the texture map.
   * This function is kept private to prevent users from using the generated
   * string id directly.
   * @param message the text contents of the texture
   * @param fontFile the path to the TTF font resource. Can be either relative
   * to the resourcePath or absolute
   * @param color color of the text
   * @param fontSize size of the font
   * @return the string id of the TTF Text texture in the texture map
   */
  static inline resourceId_t getTTFTextTextureId(const std::string &message,
                                                 const std::string &fontFile,
                                                 SDL_Color color,
                                                 int fontSize) {
    const filesystem::path resPath = getResourcePath("");

    std::string resourceFilename = (resPath / fontFile).u8string();
    std::string stringId = u8"standard text//" + message + resourceFilename +
                           std::to_string(color.r) + std::to_string(color.g) +
                           std::to_string(color.b) + std::to_string(color.a) +
                           std::to_string(fontSize);
#ifdef _DEBUG
    return stringId;
#else
    return hash(stringId);
#endif
  }

  static inline resourceId_t getSoundId(const std::string &filename) {
    const filesystem::path resPath = getResourcePath("");

    const std::string resourceFilename = (resPath / filename).u8string();
#ifdef _DEBUG
    return resourceFilename;
#else
    return hash(resourceFilename);
#endif
  }

  static inline resourceId_t getFStreamId(const filesystem::path &path) {
#ifdef _DEBUG
    return path.string();
#else
    return hash(path.string());
#endif
  }

 public:
  /**
   * @brief Fetches the singleton instance of the resource manager. Creates the
   * resource manager on the first invocation, and returns the previously
   * allocated invocation on consecutive invocations. Note that this function,
   * does not initialize the ResourceManager, but merely allocates memory for
   * it. Call startUp after the first invocation of this function to initialize
   * the singleton instance.
   * @return the ResourceManager instance for the program
   */
  static ResourceManager &getInstance();

  /**
   * @brief On the first invocation, initializes the singleton resource manager.
   * On subsequent invocations, does nothing.
   * @param renderer the renderer of the window, used to render textures and
   * other objects
   * @return true if the ResourceManager is started, false if not.
   */
  bool startUp(SDL_Renderer *renderer);

  /**
   * @return true if the ResourceManager has been initialized, false if not.
   */
  bool hasStarted();

  /**
   * @brief Shuts down the singleton ResourceManager by deallocating all the
   * pre-allocated textures. Does not deallocate the renderer. After
   * deallocating the textures, empties the texture map and sets missing texture
   * to nullptr. Subsequent allocation of this function do nothing.
   */
  void shutDown();

  /**
   * @brief Fetches the SDL_Texture associated with the given filename. If not
   * already in the texture map, loads the texture from the given filename. If
   * the texture fails to load for any reason, a warning is logged, and the
   * missing texture is instead return and associated with the filename in the
   * texture map. If the filename is in the texture map, the previously loaded
   * texture is returned.
   * @param filename location of the texture. Can be both absolute path or
   * relative to the resourcePath
   * @return the requested texture if loaded successfully, the default missing
   * texture if loading the texture fails for any reason
   */
  SDL_Texture *getBMPTexture(const std::string &filename);

  /**
   * @brief Fetches the SDL_Texture associated with the given filename. If not
   * already in the texture map, loads the texture from the given filename. If
   * the texture fails to load for any reason, a warning is logged, and the
   * missing texture is instead return and associated with the filename in the
   * texture map. If the filename is in the texture map, the previously loaded
   * texture is returned.
   * @param filename location of the texture. Can be both absolute path or
   * relative to the resourcePath
   * @return the requested texture if loaded successfully, the default missing
   * texture if loading the texture fails for any reason
   */
  SDL_Texture *getTexture(const std::string &filename);

  /**
   * @brief Returns a TTF text texture, specified with the passed argument. On
   * the first invocation, the texture is created and cached in the texture map.
   * In subsequent calls, the cached texture is returned.
   * @param message the text contents of the texture
   * @param fontFile the path to the TTF font resource. Can be either relative
   * to the resourcePath or absolute
   * @param color color of the text
   * @param fontSize size of the font
   * @return SDL_Texture containing the TTF text message
   */
  SDL_Texture *getTextTexture(const std::string &message,
                              const std::string &fontFile, SDL_Color color,
                              int fontSize);

  std::string getFont(const std::string &filename);

  Mix_Music *getMusic(const std::string &path);

  Mix_Chunk *getChunk(const std::string &path);

  std::string getTranslation(const std::string &message, Language language);

  /**
   * @brief Removes the image texture associated with the filename from the
   * texture map of the ResourceManager. If the filename is not present in the
   * texture map, this function does not do anything.
   * @param filename the requested texture to be removed from the texture map.
   * The filename can be both relative to the resourcePath or absolute path.
   */
  void unloadImageTexture(const std::string &filename);

  /**
   * @brief Removes the TTF text texture associated with the passed arguments
   * from the texture map of the ResourceManager. If it is not present in the
   * texture map, this function does not do anything.
   * @param message the text contents of the texture
   * @param fontFile the path to the TTF font resource. Can be either relative
   * to the resourcePath or absolute
   * @param color color of the text
   * @param fontSize size of the font
   * @return the string id of the TTF Text texture in the texture map
   */
  void unloadTTFTextTexture(const std::string &message,
                            const std::string &fontFile, SDL_Color color,
                            int fontSize);

  void unloadMusic(const std::string &path);

  void unloadChunk(const std::string &path);

  /**
   * Convenience method to unload all textures inside the texture map.
   */
  inline void unloadAllTexture();

  inline void unloadAllMusic();

  inline void unloadAllChunk();

  inline void closeAllfiles();

  std::fstream *openFile(const std::string &path,
                         std::ios_base::openmode flags = std::ios_base::in |
                                                         std::ios_base::out);

  void closeFile(const std::string &path);

  inline const SDL_Renderer *getRenderer() { return renderer_; }

#ifdef _TEST
  inline const std::map<resourceId_t, SDL_Texture *> *getTexturesMap() {
    return &textures_;
  }
  inline const std::map<resourceId_t, Mix_Music *> *getMusicMap() {
    return &music_;
  }
  inline const std::map<resourceId_t, Mix_Chunk *> *getChunkMap() {
    return &chunk_;
  }
  inline const SDL_Texture *getMissingTexture() { return missing_texture_; }
#endif

 private:
#ifndef _DEBUG
  static std::hash<std::string> hash;
#endif
  bool hasStarted_ = false;
  SDL_Renderer *renderer_ = nullptr;
  SDL_Texture *missing_texture_ = nullptr;
  std::map<resourceId_t, SDL_Texture *> textures_;
  std::map<resourceId_t, Mix_Music *> music_;
  std::map<resourceId_t, Mix_Chunk *> chunk_;
  std::map<resourceId_t, std::pair<std::ios_base::openmode, std::fstream *>>
      fstream_;
  std::map<std::string, std::map<Language, std::string>> localization_{
      {u8"START", {{Language::SPANISH, u8"COMIENZO"}}},
      {u8"SELECT DIFFICULTY", {{Language::SPANISH, u8"SELECCIONE DIFICULTAD"}}},
      {u8"CHANGE LANGUAGE", {{Language::SPANISH, u8"CAMBIAR IDIOMA"}}},
      {u8"EASY", {{Language::SPANISH, u8"FÁCIL"}}},
      {u8"MEDIUM", {{Language::SPANISH, u8"MEDIO"}}},
      {u8"HARD", {{Language::SPANISH, u8"DURO"}}},
      {u8"RETURN", {{Language::SPANISH, u8"REGRESO"}}},
      {u8"Return", {{Language::SPANISH, u8"Regreso"}}},
      {u8"ENGLISH", {{Language::SPANISH, u8"INGLÉS"}}},
      {u8"SPANISH", {{Language::SPANISH, u8"ESPAÑOL"}}},
      {u8"Level: ", {{Language::SPANISH, u8"Nivel"}}},
      {u8"Score: ", {{Language::SPANISH, u8"Puntaje"}}},
      {u8"Lives: ", {{Language::SPANISH, u8"Vidas"}}},
      {u8"LEVEL CLEARED!", {{Language::SPANISH, u8"NIVEL COMPLETADO!"}}},
      {u8"YOU LOST", {{Language::SPANISH, u8"PERDISTE"}}},
      {u8"Highest Ever", {{Language::SPANISH, u8"El mas alto de todos"}}},
      {u8"ENTER", {{Language::SPANISH, u8"ENTRAR"}}},
      {u8"New High Score!", {{Language::SPANISH, u8"Nuevo record!"}}},
      {u8"Enter your name:", {{Language::SPANISH, u8"Introduzca su nombre:"}}},
      {u8"NEXT LEVEL", {{Language::SPANISH, u8"SIGUIENTE NIVEL"}}},
      {u8"LEVEL EDITOR", {{Language::SPANISH, u8"EDITOR DE NIVELES"}}},
      {u8"GAME OVER!", {{Language::SPANISH, u8"JUEGO TERMINADO!"}}},
      {u8"GraveRunner", {{Language::SPANISH, u8"GraveRunner"}}},
      {u8"YOUR SCORE: ", {{Language::SPANISH, u8"TU PUNTUACIÓN: "}}},
      {u8"HOW TO PLAY", {{Language::SPANISH, u8"CÓMO JUGAR"}}},
      {u8"Select Level:", {{Language::SPANISH, u8"Elegir Nivel:"}}},
      {u8"Breakout", {{Language::SPANISH, u8"Breakout"}}},
      {u8"How to Play", {{Language::SPANISH, u8"Cómo jugar"}}},
      {u8"Space - Shoot", {{Language::SPANISH, u8"Espacio - disparar"}}},
      {u8"Down Arrow - Slide (Can kill enemy while sliding)", {{Language::SPANISH, u8"Flecha hacia abajo: deslizamiento (puede matar al enemigo mientras se desliza)"}}},
      {u8"Arrow Keys - Jump, Left and Right", {{Language::SPANISH, u8"Teclas de flecha - Saltar, Izquierda y Derecha"}}},
      {u8"Grey block takes ", {{Language::SPANISH, u8"El bloque gris toma"}}},
      {u8"3 hits", {{Language::SPANISH, u8"3 golpes"}}},
      {u8"Black walls do not break", {{Language::SPANISH, u8"Las paredes negras no se rompen"}}},
      {u8"Arrow Keys - Left and Right", {{Language::SPANISH, u8"Teclas de flecha: izquierda y derecha"}}},
      {u8"GraveRunner", {{Language::SPANISH, u8"GraveRunner"}}},
      {u8"Select Game:", {{Language::SPANISH, u8"Elegir Juego:"}}},
      {u8"Keys Collected: ", {{Language::SPANISH, u8"Teclas recogidas: "}}},
      {u8"Tower Hour", {{Language::SPANISH, u8"Tower Hour"}}},
      {u8"Health: ", {{Language::SPANISH, u8"Salud: "}}},
      {u8"Wave Number: ", {{Language::SPANISH, u8"Número de onda: "}}},
      {u8"Tower Defense", {{Language::SPANISH, u8"Tower Defense"}}},
      {u8"Coins: ", {{Language::SPANISH, u8"Monedas: "}}},
      {u8"Start Wave!", {{Language::SPANISH, u8"Onda de Inicio!"}}}
  };
};
#endif
