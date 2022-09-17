#if !defined(GAME_H)
#define GAME_H

#include "chunk/chunk.h"
#include "graphics/graphics.h"

class Game
{
private:
  GraphicsManager graphics;
  Chunk chunk;
public:
  Game();
  void update(const long long μs);
  ~Game();
};

#endif // GAME_H
