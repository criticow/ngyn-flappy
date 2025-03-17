#pragma once

#include <ngyn/ngyn.hpp>
#include "obstacle.hpp"

class ObstacleManager
{
  public:
  ObstacleManager(void) = default;
  ObstacleManager(glm::vec2 resolution);

  void update();
  bool collided(Transform &transform);
  bool scored(Transform &transform);
  void toggleDebugging();
  void reset();

  private:
  std::vector<Obstacle> _obstacles;
  float _offset;
  int _first;
  glm::vec2 _resolution;

  bool checkCollision(Transform &transform, Transform &transform2);
};