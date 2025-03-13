#include <ngyn/ngyn.hpp>

class Game : public ngyn::Engine
{
  public:
  Game() : Engine({
    .window = ngyn::Window{{
      .resizable = true,
      .monitor = 1
    }}
  }){};

  virtual void onSetup();
  virtual void onUpdate();
  virtual void onRender();
};