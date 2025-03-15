#pragma once

#include <ngyn/ngyn.hpp>
#include "dog.hpp"
#include "pipe.hpp"

class Game : public ngyn::Engine
{
  public:
  Game();

  virtual void onSetup();
  virtual void onUpdate();
  virtual void onRender();

  private:
  Dog dog;
};