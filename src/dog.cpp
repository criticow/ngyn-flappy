#include "dog.hpp"

Dog::Dog(glm::vec2 position) : AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .texture = ResourcesManager::getResource<Texture>("spritesheet"),
      .index = 1,
      .size = glm::vec2(32.0f)
    },
    .transform = {
      .position = position,
      .size = glm::vec2(50.0f)
    }
  }}
{
  setRenderer(ResourcesManager::getResource<QuadRenderer>("main_renderer"));
  setCamera(ResourcesManager::getResource<Camera>("main_camera"));

  setAnimation(Animation{
    .name = "flap",
    .duration = 500.0f,
    .frames = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    .repeat = true
  });

  speed = 150.0f;
  targetY = 0.0f;
  falling = true;
  isDead = false;
}

void Dog::update()
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
    stop();
    velocity.y -= speed * 1.5 * ngTime.deltaTime();

    // Reached the top of the screen
    if(position.y + velocity.y <= 0.0f)
    {
      falling = true;
      targetY = 0.0f;
      position.y = 0.0f;
      transform.setPosition(position);

      play("flap");
    }
  }

  if(position.y <= targetY)
  {
    falling = true;
    targetY = 0.0f;

    play("flap");
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