#ifndef TIME_HPP
#define TIME_HPP

#include <SDL.h>

class Time {
 private:
  Time() = default;  // Private Singleton
  ~Time() = default;
  Time(Time const &) = delete;            // Avoid copy constructor.
  void operator=(Time const &) = delete;  // Don't allow copy assignment.
  Time(Time &&) = delete;                 // Avoid move constructor.
  void operator=(Time &&) = delete;       // Don't allow move assignment.

 public:
 private:
  Uint32 ticks;
};

#endif