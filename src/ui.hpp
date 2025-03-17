#pragma once

#include <ngyn/ngyn.hpp>

using namespace ngyn;

class UI
{
  public:
  enum Scene
  {
    Play,
    Pause,
    GameOver
  };

  public:
  UI(void) = default;
  UI(glm::vec2 resolution);

  void incrementScore();
  void update();
  void setScene(Scene scene);

  private:
  int _score;
  Text _scoreText;
  Sprite _scoreBackground;
  Scene _scene;

  Text _gameOverText;
  Sprite _gameOverBackground;
};