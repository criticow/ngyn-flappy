#include "obstacle.hpp"

Obstacle::Obstacle(glm::vec2 position, glm::vec2 resolution)
{
  _position = position;
  _resolution = resolution;
  _pipeWidth = 32.0f;

  auto renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  auto camera = ResourcesManager::getResource<Camera>("main_camera");

  auto texture = ResourcesManager::getResource<Texture>("spritesheet");

  _topBody = AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .texture = texture,
      .index = 13,
      .size = glm::vec2(32.0f),
    },
    .transform = {
      .size = glm::vec2(_pipeWidth)
    },
    .renderer = renderer,
    .camera = camera
  }};

  // float yPos = createInfo.position.y > 0.0f ? createInfo.position.y - createInfo.size.x : createInfo.size.y - createInfo.size.x;

  _topHead = AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .texture = texture,
      .index = 14,
      .size = glm::vec2(32.0f)
    },
    .transform = {
      .size = glm::vec2(_pipeWidth),
      .layer = 1
    },
    .renderer = renderer,
    .camera = camera
  }};

  _bottomBody = AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .texture = texture,
      .index = 13,
      .size = glm::vec2(32.0f),
    },
    .transform = {
      .size = glm::vec2(_pipeWidth)
    },
    .renderer = renderer,
    .camera = camera
  }};

  // float yPos = createInfo.position.y > 0.0f ? createInfo.position.y - createInfo.size.x : createInfo.size.y - createInfo.size.x;

  _bottomHead = AnimatedSprite{Sprite::CreateInfo{
    .frame = {
      .texture = texture,
      .index = 14,
      .size = glm::vec2(32.0f)
    },
    .transform = {
      .size = glm::vec2(_pipeWidth),
      .layer = 1
    },
    .renderer = renderer,
    .camera = camera
  }};

  updateSizeAndPosition();

  _topHead.instantiate();
  _topBody.instantiate();

  _bottomHead.instantiate();
  _bottomBody.instantiate();
}

void Obstacle::updateSizeAndPosition()
{
  // Get a random height for the open space between pipes
  float openingHeight = random::getFloat(_pipeWidth * 2, _pipeWidth * 4);

  float minPipeHeight = _pipeWidth * 3;
  float maxPipeHeight = _resolution.y - minPipeHeight - openingHeight;

  // Get a random height for the top pipe based on the opening
  float topHeight = random::getFloat(minPipeHeight, maxPipeHeight);
  float bottomHeight = _resolution.y - topHeight - openingHeight;

  _topBody.transform.setPosition(_position);
  _topBody.transform.setSize(glm::vec2(_pipeWidth, topHeight));
  _topHead.transform.setPosition(glm::vec2(_position.x, topHeight - _pipeWidth));

  _bottomBody.transform.setPosition(glm::vec2(_position.x, topHeight + openingHeight));
  _bottomBody.transform.setSize(glm::vec2(_pipeWidth, bottomHeight));
  _bottomHead.transform.setPosition(glm::vec2(_position.x, topHeight + openingHeight - _pipeWidth));
}

const glm::vec2 &Obstacle::position()
{
  return _position;
}

const float &Obstacle::pipeWidth()
{
  return _pipeWidth;
}

void Obstacle::moveBy(const glm::vec2 &velocity)
{
  _topBody.moveBy(velocity);
  _topHead.moveBy(velocity);
  _topHead.update();
  _topBody.update();

  _bottomBody.moveBy(velocity);
  _bottomHead.moveBy(velocity);
  _bottomHead.update();
  _bottomBody.update();

  _position = _topBody.transform.position();
}

void Obstacle::setPosition(const glm::vec2 &position)
{
  _position = position;

  updateSizeAndPosition();

  _topHead.update();
  _topBody.update();

  _bottomHead.update();
  _bottomBody.update();
}
