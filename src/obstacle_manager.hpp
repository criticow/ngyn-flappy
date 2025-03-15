#pragma once

#include <ngyn/ngyn.hpp>
#include "obstacle.hpp"

class ObstacleManager
{
  public:
  ObstacleManager(void) = default;
  ObstacleManager(glm::vec2 resolution);

  void update();

  private:
  std::vector<Obstacle> _obstacles;
  float _offset;
};