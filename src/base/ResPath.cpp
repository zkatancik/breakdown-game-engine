#include "base/ResPath.hpp"

/*
 * Get the resource path for resources located in res/subDir
 */
filesystem::path getResourcePath(const filesystem::path &subDir) {
  // This will hold the base resource path: Lessons/res/
  // We give it static lifetime so that we'll only need to call
  // SDL_GetBasePath once to get the executable path
  static filesystem::path baseRes;
  if (baseRes.empty()) {
    // SDL_GetBasePath will return NULL if something went wrong in retrieving
    // the path
    char *basePath = SDL_GetBasePath();
    if (basePath) {
      baseRes = basePath;
      SDL_free(basePath);
    } else {
      std::cerr << "Error getting resource path: " << SDL_GetError()
                << std::endl;
      return "";
    }
    // We replace the last bin/ with res/ to get the the resource path
    size_t pos = baseRes.string().rfind("bin");
    baseRes = filesystem::absolute(
        filesystem::path(baseRes.string().substr(0, pos)) / "res");
  }
  // If we want a specific subdirectory path in the resource directory
  // append it to the base path. This would be something like
  // Lessons/res/Lesson0
  return subDir.empty() ? baseRes : baseRes / subDir;
}