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

  float pipeWidth = 32.0f;

  // Get a random height for the open space between pipes
  float openingHeight = random::getFloat(pipeWidth * 2, pipeWidth * 4);

  float minPipeHeight = pipeWidth * 3;
  float maxPipeHeight = window.resolution().y - minPipeHeight - openingHeight;

  // Get a random height for the top pipe based on the opening
  float topHeight = random::getFloat(minPipeHeight, maxPipeHeight);
  float bottomHeight = window.resolution().y - topHeight - openingHeight;

  LOGGER_DEBUG("{}", topHeight + bottomHeight + openingHeight);

  Pipe{{
    .position = glm::vec2(500.0f, 0.0f),
    .size = glm::vec2(pipeWidth, topHeight)
  }};

  Pipe{{
    .position = glm::vec2(500.0f, topHeight + openingHeight),
    .size = glm::vec2(pipeWidth, bottomHeight)
  }};
}

void Game::onUpdate()
{
  if(!dog.isDead)
  {
    dog.update();
  }
}

void Game::onRender()
{
  auto renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  renderer.lock().get()->render();
}