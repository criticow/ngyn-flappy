#include "ui.hpp"

UI::UI(glm::vec2 resolution)
{
  _scene = Scene::Pause;

  std::weak_ptr<QuadRenderer> renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  std::weak_ptr<Camera> camera = ResourcesManager::getResource<Camera>("main_camera");
  std::weak_ptr<Font> font = ResourcesManager::getResource<Font>("dogica");

  _scoreText = Text(Text::CreateInfo{
    .font = font,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(0.0f),
    .value = "Score: 0",
    .color = Color(255),
    .layer = 5
  });

  _scoreText.instantiate();

  _scoreBackground = Sprite(Sprite::CreateInfo{
    .frame = {
      .color = Color(0, 0, 0, 150)
    },
    .transform = {
      .size = glm::vec2(200.0f, 40.0f),
      .layer = 4
    },
    .renderer = renderer,
    .camera = camera,
  });

  _scoreBackground.instantiate();

  _score = 0;

  std::weak_ptr<Font> font_64 = ResourcesManager::getResource<Font>("dogica_64");

  glm::vec2 textSize = font_64.lock().get()->getTextSize("GAME OVER");
  glm::vec2 textPosition = resolution * 0.5f - textSize * 0.5f;

  _gameOverText = Text(Text::CreateInfo{
    .font = font_64,
    .camera = camera,
    .renderer = renderer,
    .position = textPosition,
    .value = "GAME OVER",
    .color = Color(255),
    .visibility = Frame::Visibility::Hidden,
    .layer = 5,
  });

  _gameOverText.instantiate();

  float padding = 5.0f;

  _gameOverBackground = Sprite(Sprite::CreateInfo{
    .frame = {
      .color = Color(0, 0, 0, 150),
      .visibility = Frame::Visibility::Hidden,
    },
    .transform = {
      .position = textPosition - padding,
      .size = textSize + padding * 2.0f,
      .layer = 4
    },
    .renderer = renderer,
    .camera = camera,
  });

  _gameOverBackground.instantiate();
}

void UI::setScene(Scene scene)
{
  if(_scene == scene) return;

  _scene = scene;

  if(scene == Scene::GameOver)
  {
    _gameOverBackground.frame.setVisibility(Frame::Visibility::Visible);
    _gameOverText.setVisibility(Frame::Visibility::Visible);

    _gameOverBackground.update();
    _gameOverText.update();
  }
}

void UI::incrementScore()
{
  _score++;
  _scoreText.setValue("Score: " + std::to_string(_score));
}

void UI::update()
{
  _scoreText.update();
}