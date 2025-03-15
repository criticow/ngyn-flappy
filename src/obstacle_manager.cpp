#include "obstacle_manager.hpp"

ObstacleManager::ObstacleManager(glm::vec2 resolution)
{
  _offset = 175.0f;

  for(size_t i = 0; i < 5; i++)
  {
    _obstacles.push_back(Obstacle(glm::vec2((i + 1) * _offset, 0.0f), resolution));
  }
}

void ObstacleManager::update()
{
  float speed = 75.0f + ngTime.getTime() * ngTime.deltaTime();

  for(size_t i = 0; i < _obstacles.size(); i++)
  {
    auto &obstacle = _obstacles[i];

    obstacle.moveBy(glm::vec2(-speed * ngTime.deltaTime(), 0.0f));

    // Pipe left the screen
    if(obstacle.position().x + obstacle.pipeWidth() < 0.0f)
    {
      int previousIndex = i == 0 ? _obstacles.size() -1 : i - 1;
      auto targetPosition = _obstacles[previousIndex].position();

      obstacle.setPosition(glm::vec2(targetPosition.x + _offset, 0.0f));
    }
  }
}