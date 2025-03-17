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
  auto renderer = ResourcesManager::addResource<QuadRenderer>("main_renderer", QuadRenderer{});

  auto camera = ResourcesManager::addResource<Camera>(
    "main_camera",
    Camera({
      .position = glm::vec2(0.0f),
      .resolution = window.resolution()
    })
  );

  auto font = ResourcesManager::addResource<Font>("dogica", Font{Font::CreateInfo{
    .path = "data/fonts/dogica.ttf",
    .name = "dogica",
    .size = 32,
    .pixelated = true,
  }});

  ResourcesManager::addResource<Font>("dogica_64", Font{Font::CreateInfo{
    .path = "data/fonts/dogica.ttf",
    .name = "dogica_64",
    .size = 64,
    .pixelated = true,
  }});

  ResourcesManager::addResource<Texture>("spritesheet", Texture{{
    .image = "data/textures/spritesheet.png",
    .filtering = Texture::Filtering::Nearest
  }});

  renderer.lock().get()->setup();

  dog = Dog(glm::vec2(50.0f, window.resolution().y * 0.5f - 16.0f));
  dog.instantiate();

  ui = UI(window.resolution());

  obstacleManager = ObstacleManager(window.resolution());
}

void Game::onUpdate()
{
  if(obstacleManager.collided(dog.collider.transform))
  {
    ui.setScene(UI::Scene::GameOver);
    return;
  }

  if(obstacleManager.scored(dog.collider.transform))
  {
    ui.incrementScore();
  }

  dog.update();
  ui.update();
  obstacleManager.update();
}

void Game::onRender()
{
  auto renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  renderer.lock().get()->render();
}