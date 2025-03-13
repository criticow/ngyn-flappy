#include "bird.hpp"

Bird::Bird() : AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .color = Color(255, 0, 0)
    },
    .transform = {
      .position = glm::vec2(150.0f),
      .size = glm::vec2(50.0f)
    }
  }}
{
  setRenderer(ResourcesManager::getResource<QuadRenderer>("main_renderer"));
  setCamera(ResourcesManager::getResource<Camera>("main_camera"));

  speed = 350.0f;
  targetY = 0.0f;
  falling = true;
  isDead = false;
}

void Bird::update()
{
  if(falling && ngInput.pressed("KEY_SPACE"))
  {
    targetY = transform.position().y - speed / 2.3;

    falling = false;
  }

  glm::vec2 velocity(0.0f);

  auto position = transform.position();
  auto size = transform.size();

  if(!falling && position.y >= targetY)
  {
    velocity.y -= speed * 1.5 * ngTime.deltaTime();

    // Reached the top of the screen
    if(position.y + velocity.y <= 0.0f)
    {
      falling = true;
      targetY = 0.0f;
      position.y = 0.0f;
      transform.setPosition(position);
    }
  }

  if(position.y <= targetY)
  {
    falling = true;
    targetY = 0.0f;
  }

  if(falling)
  {
    velocity.y = speed * ngTime.deltaTime();

    // Reached the bottom of the screen
    if(position.y + velocity.y + size.y >= 720.0f)
    {
      isDead = true;
    }
  }

  moveBy(velocity);

  AnimatedSprite::update();
}