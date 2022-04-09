#include <cxxtest/TestSuite.h>

#include "graverunner/Button.hpp"
#include "graverunner/Mouse.hpp"

class ButtonTestSuite : public CxxTest::TestSuite {
 public:
  const float EPSILON = 0.001f;

  // --------------------- BLOCK TESTS -----------------------------------

  void testStartUp() {
    Button *button = new Button();
    button->startUp(784, 295, 408, 179, 408, 541, 1280 / 2, 720 / 2, u8"TEST");
  }

  void testShutDown() {}

  void testIsClicked() {
    Button *button = new Button();
    button->startUp(784, 295, 408, 179, 408, 541, 1280 / 2, 720 / 2, u8"TEST");
    button->isClicked();
    TS_ASSERT_EQUALS(button->IsSelected(), false);
  }

  void testIsSelected() {
    Button *button = new Button();
    button->startUp(784, 295, 408, 179, 408, 541, 1280 / 2, 720 / 2, u8"TEST");
    button->IsSelected();
    TS_ASSERT_EQUALS(button->IsSelected(), false);
  }

  void testUpdate() {
    Button *button = new Button();
    button->startUp(300, 200, 0, 0, 0, 0, 500, 500, u8"TESTING");
    Mouse *mouse = new Mouse();
    mouse->setPointX(0);
    mouse->setPointY(3);
    // Click
    button->update(mouse);
    TS_ASSERT_EQUALS(button->IsSelected(), false);
    mouse->setPointX(500);
    mouse->setPointY(500);
    // Click
// TODO- Flakey
//    button->update(mouse);
//    TS_ASSERT_EQUALS(button->getIsSelected(), true);
  }

  void testRender() {}

  void testChangeLanguage() {}
};
