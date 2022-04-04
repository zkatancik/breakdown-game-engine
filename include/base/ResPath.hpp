// code derived from TwinklebearDev SDL 2.0 Tutorial
// https://www.willusher.io/pages/sdl2/

#ifndef RES_PATH_HPP
#define RES_PATH_HPP

#include <SDL.h>

#include <filesystem>
#include <iostream>
#include <string>
namespace filesystem = std::filesystem;

/**
 * @brief Get the filesystem path to the resources directory, with optional sub directory to include in the path as well.
 * 
 * @param subDir Subdirectory path from resources root, will be appended to output path. Can be empty string
 * @return filesystem::path to the resources root directory
 */
filesystem::path getResourcePath(const filesystem::path &subDir = "");

#endif
