#pragma once

#include <ngyn/ngyn.hpp>
#include "dog.hpp"
#include "obstacle_manager.hpp"

class Game : public ngyn::Engine
{
  public:
  Game();

  virtual void onSetup();
  virtual void onUpdate();
  virtual void onRender();

  private:
  Dog dog;
  ObstacleManager obstacleManager;
};