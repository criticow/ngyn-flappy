#include "game.hpp"

using namespace ngyn;

Game::Game() : Engine({
  .window = ngyn::Window{{
    .resolution = glm::vec2(640.0f, 360.0f),
    .resizable = true,
    .monitor = 1
  }}
}){};

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

  ResourcesManager::addResource<Texture>("spritesheet", Texture{{
    .image = "data/textures/spritesheet.png",
    .filtering = Texture::Filtering::Nearest
  }});

  quadRenderer.lock().get()->setup();

  dog = Dog(glm::vec2(50.0f, window.resolution().y * 0.5f - 16.0f));
  dog.instantiate();

  obstacleManager = ObstacleManager(window.resolution());
}

void Game::onUpdate()
{
  if(!dog.isDead)
  {
    dog.update();
  }

  obstacleManager.update();
}

void Game::onRender()
{
  auto renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  renderer.lock().get()->render();
}