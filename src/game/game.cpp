#include "game.h"
#include <GL/glew.h>
#include "src/logging/logger.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::update(const long long μs)
{
  logger::info(logger::message::TIME_SINCE_LAST_UPDATE, μs);
  glClear(GL_COLOR_BUFFER_BIT);
}