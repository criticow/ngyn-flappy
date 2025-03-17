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
  void setScene(Scene scene);
  const Scene &scene();

  void reset();

  private:
  int _score;
  Text _scoreText;
  Sprite _scoreBackground;
  Scene _scene;

  Text _gameOverText;
  Sprite _gameOverBackground;

  Text _pauseText;
  Sprite _pauseBackground;
};