#include "game.hpp"

int main()
{
  ngyn::ngLogger.setFormat("HH:mm:ss");

  Game game;
  game.run();
}