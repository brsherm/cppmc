#include "game.h"
#include <GL/glew.h>
#include "src/logging/logger.h"

Game::Game() :
  chunk(0, 0)
{
  Graphics::ChunkLoader loader;
  graphics.load_chunk(chunk, loader);
}

Game::~Game()
{
  Graphics::ChunkUnloader unloader;
  graphics.unload_chunk(chunk, unloader);
}

void Game::update(const long long μs)
{
  glClear(GL_COLOR_BUFFER_BIT);
  graphics.draw();
}