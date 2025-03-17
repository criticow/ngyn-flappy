#pragma once

#include <ngyn/ngyn.hpp>

using namespace ngyn;

class Obstacle
{
  public:
  Obstacle(glm::vec2 position, glm::vec2 resolution);

  void moveBy(const glm::vec2 &velocity);
  void setPosition(const glm::vec2 &position);

  const glm::vec2 &position();
  const float &pipeWidth();

  private:
  glm::vec2 _position;
  glm::vec2 _resolution;
  float _pipeWidth;
  AnimatedSprite _topHead;
  AnimatedSprite _topBody;

  AnimatedSprite _bottomHead;
  AnimatedSprite _bottomBody;

  void updateSizeAndPosition();

  friend class ObstacleManager;
};