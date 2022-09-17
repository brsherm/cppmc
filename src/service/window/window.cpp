#include "window.h"
#include <iostream>

WindowService::WindowService()
{
  if (!glfwInit()) return;
  m_window = glfwCreateWindow(640, 480, config::title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(m_window);
}

WindowService::~WindowService()
{
  glfwTerminate();
}

bool WindowService::shouldClose()
{
  return glfwWindowShouldClose(m_window);
}

bool WindowService::alive()
{
  return !!m_window;
}

void WindowService::swapBuffers()
{
  glfwSwapBuffers(m_window);
}