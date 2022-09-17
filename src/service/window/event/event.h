#if !defined(EVENT_H)
#define EVENT_H

#include <GLFW/glfw3.h>
#include <set>

namespace EventProcessor
{
  void take_key(GLFWwindow* window, int key, int scan_code, int action, int mods);
  void take_mouse_movement(GLFWwindow* window, double xpos, double ypos);
  void take_mouse_click(GLFWwindow* window, int button, int action, int mods);
  void take_window_resize(GLFWwindow* window, int width, int height);
  void reset();

  struct Input {
    std::set<int> keys_held;
    bool mouse_moving;
    bool is_left_click_held;
    bool is_right_click_held;
    bool window_resizing;
    GLFWwindow* window;
    double mouseX, mouseY, pmouseX, pmouseY;
  };
  
  Input input;
};
#endif // EVENT_H