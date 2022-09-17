#include "window/window.h"
#include "src/game/game.h"

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

