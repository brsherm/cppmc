#include <GLFW/glfw3.h>
#include "src/config/config.h"

class WindowService
{
private:
  GLFWwindow* m_window;
public:
  WindowService();
  ~WindowService();
  bool shouldClose();
  bool alive();
  void swapBuffers();
};