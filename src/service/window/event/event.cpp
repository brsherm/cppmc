#include "event.h"
#include <iostream>

namespace EventProcessor
{
  void take_key (
    GLFWwindow* window,
    int key,
    int scan_code,
    int action,
    int mods
  ){
    if (action == GLFW_PRESS) {
      input.keys_held.insert(key);
    }
    if (action == GLFW_RELEASE) {
      input.keys_held.erase(key);
    }
  }

  void take_mouse_movement (GLFWwindow* window, double xpos, double ypos)
  {
    input.mouse_moving = true;
    input.pmouseX = input.mouseX;
    input.pmouseY = input.mouseY;
    input.mouseX = xpos;
    input.mouseY = ypos;
  }

  void reset()
  {
    input.mouse_moving = false;
    input.pmouseX = input.mouseX;
    input.pmouseY = input.mouseY;
    input.window_resizing = false;
  }

  void take_mouse_click (GLFWwindow* window, int button, int action, int mods)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      if (action == GLFW_PRESS) {
        input.is_left_click_held = true;
      } else {
        input.is_left_click_held = false;
      }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      if (action == GLFW_PRESS) {
        input.is_right_click_held = true;
      } else {
        input.is_right_click_held = false;
      }
    }
  }

  void take_window_resize(GLFWwindow* window, int width, int height)
  {
    input.window_resizing = true;
  }
}