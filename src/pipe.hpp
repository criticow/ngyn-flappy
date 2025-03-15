#pragma once

#include <ngyn/ngyn.hpp>

using namespace ngyn;

class Pipe
{
  public:
  struct CreateInfo
  {
    glm::vec2 position;
    glm::vec2 size;
  };

  public:
  Pipe(CreateInfo createInfo);

  private:
  glm::vec2 _position;
  AnimatedSprite _head;
  AnimatedSprite _body;
};