#include "game.hpp"

using namespace ngyn;

void Game::onSetup()
{
  auto quadRenderer = ResourcesManager::addResource<QuadRenderer>("main_renderer", QuadRenderer{});

  ResourcesManager::addResource<Camera>(
    "main_camera",
    Camera({
      .position = glm::vec2(0.0f),
      .resolution = window.resolution()
    })
  );

  quadRenderer.lock().get()->setup();

  bird = Bird();
  bird.instantiate();
}

void Game::onUpdate()
{
  if(!bird.isDead)
  {
    bird.update();
  }
}

void Game::onRender()
{
  auto renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  renderer.lock().get()->render();
}