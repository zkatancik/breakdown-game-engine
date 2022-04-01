// Support Code written by Michael D. Shah
// Updated by Breakdown
// Last Updated: Spring 2022
// Please do not redistribute without asking permission.

#include "base/SDLGraphicsProgram.hpp"
#include "graverunner/GraveRunnerLogic.hpp"
#include <memory>

int main(int argc, char** argv) {
  // Create an instance of an object for a SDLGraphicsProgram
  auto logic = std::make_shared<GraveRunnerLogic>();
  SDLGraphicsProgram mySDLGraphicsProgram(logic, 1280, 768);
  // Run our program forever
  mySDLGraphicsProgram.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}
