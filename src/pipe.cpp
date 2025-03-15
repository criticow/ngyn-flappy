#include "pipe.hpp"

Pipe::Pipe(CreateInfo createInfo)
{
  auto renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  auto camera = ResourcesManager::getResource<Camera>("main_camera");

  auto texture = ResourcesManager::getResource<Texture>("spritesheet");

  _body = AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .texture = texture,
      .index = 13,
      .size = glm::vec2(32.0f),
    },
    .transform = {
      .position = glm::vec2(createInfo.position),
      .size = glm::vec2(createInfo.size)
    },
    .renderer = renderer,
    .camera = camera
  }};

  float yPos = createInfo.position.y > 0.0f ? createInfo.position.y - createInfo.size.x : createInfo.size.y - createInfo.size.x;

  _head = AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .texture = texture,
      .index = 14,
      .size = glm::vec2(32.0f)
    },
    .transform = {
      .position = glm::vec2(createInfo.position.x, yPos),
      .size = glm::vec2(createInfo.size.x),
      .layer = 1
    },
    .renderer = renderer,
    .camera = camera
  }};

  _head.instantiate();
  _body.instantiate();
}