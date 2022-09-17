#include "window/window.h"
#include "game/game.h"

class Application
{
private:
  WindowService ws;
  Game game;
  int run();
public:
  Application();
  ~Application();
};

