#include "obstacle_manager.hpp"

ObstacleManager::ObstacleManager(glm::vec2 resolution)
{
  _resolution = resolution;
  reset();
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

bool ObstacleManager::scored(Transform &transform)
{
  auto obstacle = _obstacles[_first];

  // Dog has passed the pipe without colliding
  if(transform.position().x > obstacle.position().x + obstacle.pipeWidth())
  {
    _first == _obstacles.size() - 1 ? _first = 0 : _first++;

    return true;
  }

  return false;
}

bool ObstacleManager::collided(Transform &transform)
{
  auto obstacle = _obstacles[_first];
  
  bool topBody = checkCollision(transform, obstacle._topBody.transform);
  bool bottomBody = checkCollision(transform, obstacle._bottomBody.transform);

  // if(topBody || bottomBody)
  // {
  //   return true;
  // }

  // Dog fell of the window boundaries
  if(transform.position().y > _resolution.y)
  {
    return true;
  }

  return false;
}

bool ObstacleManager::checkCollision(Transform &transform, Transform &transform2)
{
  bool leftEdge = transform.position().x < transform2.position().x + transform2.size().x;
  bool rightEdge = transform.position().x + transform.size().x > transform2.position().x;
  bool bottomEdge = transform.position().y < transform2.position().y + transform2.size().y;
  bool topEdge = transform.position().y + transform.size().y > transform2.position().y;

  return leftEdge && rightEdge && bottomEdge && topEdge;
}

void ObstacleManager::toggleDebugging()
{
  for(auto &obstacle : _obstacles)
  {
    obstacle.toggleDebugging();
  }
}

void ObstacleManager::reset()
{
  _offset = 175.0f;
  _first = 0;

  float start = _offset * 2.0f;

  for(size_t i = 0; i < 5; i++)
  {
    glm::vec2 position((i + 1) * _offset + start, 0.0f);

    _obstacles.size() < 5 ?
      _obstacles.push_back(Obstacle(position, _resolution)) :
      _obstacles[i].setPosition(position);
  }

  update();
}