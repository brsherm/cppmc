#include "application.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "src/config/config.h"
#include "src/logging/logger.h"

Application::Application()
{
  if (!ws.alive()) return;
  logger::init_map();
  run();
}

Application::~Application()
{
}

int Application::run()
{
  auto t1 = std::chrono::high_resolution_clock::now();
  auto t2 = t1;
  while (1) {
    if (ws.shouldClose()) break;
    t1 = t2;
    t2 = std::chrono::high_resolution_clock::now();
    long long μs = std::chrono::duration_cast<
      std::chrono::microseconds
    >(t2 - t1).count();
    game.update(μs);
    logger::write();
    ws.swapBuffers();
    glfwPollEvents();
  }
  return 0;
}
