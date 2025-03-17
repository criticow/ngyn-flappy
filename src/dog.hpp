#pragma once

#include <ngyn/ngyn.hpp>

using namespace ngyn;

class Dog : public AnimatedSprite
{
  public:
  Dog(void) = default;
  Dog(glm::vec2 position);

  void update();
  void instantiate();

  Sprite collider;

  bool isDead;

  private:
  float speed;
  float targetY;
  bool falling;
};