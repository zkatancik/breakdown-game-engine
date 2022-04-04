// Support Code written by Michael D. Shah
// Updated by Breakdown
// Last Updated: Spring 2022
// Please do not redistribute without asking permission.
#include "base/SDLGraphicsProgram.hpp"
#include "breakout/BreakoutLogic.hpp"

int main(int argc, char** argv) {
  auto logic = std::make_shared<BreakoutLogic>("Breakout By Breakdown");
  // Create an instance of an object for a SDLGraphicsProgram
  SDLGraphicsProgram mySDLGraphicsProgram(logic, 1280, 720);
  // Run our program forever
  mySDLGraphicsProgram.loop();
  // When our program ends, it will exit scope, the
  // destructor will then be called and clean up the program.
  return 0;
}
