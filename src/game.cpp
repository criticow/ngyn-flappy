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

  ResourcesManager::addResource<Font>("dogica_8", Font{Font::CreateInfo{
    .path = "data/fonts/dogica.ttf",
    .name = "dogica_8",
    .size = 8,
    .pixelated = true,
  }});

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

  dog = Dog(glm::vec2(
    window.resolution().x * 0.5f - 16.0f,
    window.resolution().y * 0.5f - 16.0f
  ));

  dog.instantiate();

  ui = UI(window.resolution());

  obstacleManager = ObstacleManager(window.resolution());
}

void Game::onUpdate()
{
  if(ngInput.pressed("KEY_F8"))
  {
    dog.toggleDebugging();
    obstacleManager.toggleDebugging();
  }

  if(ngInput.pressed("KEY_F1"))
  {
    dog.reset();
    obstacleManager.reset();
    ui.reset();
  }

  if(ui.scene() == UI::Scene::Pause && ngInput.pressed("KEY_SPACE"))
  {
    ui.setScene(UI::Scene::Play);
  }

  if(ui.scene() == UI::Scene::Play && ngInput.pressed("KEY_ESCAPE"))
  {
    ui.setScene(UI::Scene::Pause);
  }

  if(ui.scene() == UI::Scene::Pause)
  {
    return;
  }

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
  obstacleManager.update();
}

void Game::onRender()
{
  auto renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  renderer.lock().get()->render();
}