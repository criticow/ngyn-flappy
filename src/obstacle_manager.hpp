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

  private:
  std::vector<Obstacle> _obstacles;
  float _offset;
  int _first;

  bool checkCollision(Transform &transform, Transform &transform2);
};