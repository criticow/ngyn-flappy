#pragma once

#include <ngyn/ngyn.hpp>
#include "dog.hpp"
#include "obstacle_manager.hpp"
#include "ui.hpp"

class Game : public ngyn::Engine
{
  public:
  Game();

  virtual void onSetup();
  virtual void onUpdate();
  virtual void onRender();

  private:
  UI ui;
  Dog dog;
  ObstacleManager obstacleManager;
};