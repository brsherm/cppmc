#include "game.h"
#include <GL/glew.h>
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::update(const long long μs)
{
  std::cout << "it has been " << μs << " μs since the last update began" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT);
}