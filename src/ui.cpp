#include "ui.hpp"

UI::UI(glm::vec2 resolution)
{
  _padding = 5.0f;
  _scene = Scene::Pause;

  std::weak_ptr<QuadRenderer> renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  std::weak_ptr<Camera> camera = ResourcesManager::getResource<Camera>("main_camera");
  std::weak_ptr<Font> font = ResourcesManager::getResource<Font>("dogica");

  glm::vec2 scoreTextSize = font.lock().get()->getTextSize("Score: 0");

  _scoreText = Text(Text::CreateInfo{
    .font = font,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(_padding),
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
      .size = scoreTextSize + _padding * 2,
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

  _gameOverBackground = Sprite(Sprite::CreateInfo{
    .frame = {
      .color = Color(0, 0, 0, 150),
      .visibility = Frame::Visibility::Hidden,
    },
    .transform = {
      .position = textPosition - _padding,
      .size = textSize + _padding * 2.0f,
      .layer = 4
    },
    .renderer = renderer,
    .camera = camera,
  });

  _gameOverBackground.instantiate();

  glm::vec2 pauseTextSize = font.lock().get()->getTextSize("Press space");
  glm::vec2 pauseTextPosition = resolution * 0.5f - pauseTextSize * 0.5f;

  _pauseText = Text(Text::CreateInfo{
    .font = font,
    .camera = camera,
    .renderer = renderer,
    .position = pauseTextPosition,
    .value = "Press space",
    .color = Color(255),
    .visibility = Frame::Visibility::Visible,
    .layer = 5,
  });
  _pauseText.instantiate();

  _pauseBackground = Sprite(Sprite::CreateInfo{
    .frame = {
      .color = Color(0, 0, 0, 150),
      .visibility = Frame::Visibility::Visible,
    },
    .transform = {
      .position = pauseTextPosition - _padding,
      .size = pauseTextSize + _padding * 2.0f,
      .layer = 4
    },
    .renderer = renderer,
    .camera = camera,
  });
  _pauseBackground.instantiate();

  fixedText();
}

const UI::Scene &UI::scene()
{
  return _scene;
}

void UI::setScene(Scene scene)
{
  if(_scene == scene) return;

  _scene = scene;

  if(scene == Scene::Play)
  {
    _gameOverBackground.frame.setVisibility(Frame::Visibility::Hidden);
    _gameOverText.setVisibility(Frame::Visibility::Hidden);
    _pauseBackground.frame.setVisibility(Frame::Visibility::Hidden);
    _pauseText.setVisibility(Frame::Visibility::Hidden);
  }

  if(scene == Scene::GameOver)
  {
    _gameOverBackground.frame.setVisibility(Frame::Visibility::Visible);
    _gameOverText.setVisibility(Frame::Visibility::Visible);
    _pauseBackground.frame.setVisibility(Frame::Visibility::Hidden);
    _pauseText.setVisibility(Frame::Visibility::Hidden);
  }

  if(scene == Scene::Pause)
  {
    _gameOverBackground.frame.setVisibility(Frame::Visibility::Hidden);
    _gameOverText.setVisibility(Frame::Visibility::Hidden);
    _pauseBackground.frame.setVisibility(Frame::Visibility::Visible);
    _pauseText.setVisibility(Frame::Visibility::Visible);
  }

  _gameOverBackground.update();
  _gameOverText.update();
  _pauseBackground.update();
  _pauseText.update();
}

void UI::incrementScore()
{
  _score++;

  std::string newValue = "Score: " + std::to_string(_score);
  _scoreText.setValue(newValue);
  _scoreText.update();

  auto font = _scoreText.font();
  glm::vec2 scoreTextSize = font.lock().get()->getTextSize(newValue);

  _scoreBackground.transform.setSize(scoreTextSize + _padding * 2);
  _scoreBackground.update();
}

void UI::reset()
{
  _score = 0;
  _scoreText.setValue("Score: " + std::to_string(_score));
  _scoreText.update();
  setScene(UI::Scene::Pause);
}

void UI::fixedText()
{
  // Fixed Text
  std::weak_ptr<QuadRenderer> renderer = ResourcesManager::getResource<QuadRenderer>("main_renderer");
  std::weak_ptr<Camera> camera = ResourcesManager::getResource<Camera>("main_camera");
  std::weak_ptr<Font> font_8 = ResourcesManager::getResource<Font>("dogica_8");

  float startY = _scoreBackground.transform.size().y + _padding;
  float yPos = startY;
  glm::vec2 commandTextSize = font_8.lock().get()->getTextSize("COMMAND ");
  commandTextSize.x += _padding;

  glm::vec2 spacebarTextSize = font_8.lock().get()->getTextSize("Spacebar");

  float totalHeight = 0.0f;

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(_padding, yPos + _padding),
    .value = "Hotkeys:",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  yPos += commandTextSize.y + _padding * 2;
  totalHeight += commandTextSize.y + _padding * 2;

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(_padding, yPos),
    .value = "COMMAND",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(commandTextSize.x, yPos),
    .value = "KEY",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  yPos += commandTextSize.y + 1.0f;
  totalHeight += commandTextSize.y + 1.0f;

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(_padding, yPos),
    .value = "Flap",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(commandTextSize.x, yPos),
    .value = "Spacebar",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  yPos += commandTextSize.y + 1.0f;
  totalHeight += commandTextSize.y + 1.0f;

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(_padding, yPos),
    .value = "Reset",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(commandTextSize.x, yPos),
    .value = "F1",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  yPos += commandTextSize.y + 1.0f;
  totalHeight += commandTextSize.y + 1.0f;

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(_padding, yPos),
    .value = "Debug",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(commandTextSize.x, yPos),
    .value = "F8",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  yPos += commandTextSize.y + 1.0f;
  totalHeight += commandTextSize.y + 1.0f;

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(_padding, yPos),
    .value = "Pause",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  Text(Text::CreateInfo{
    .font = font_8,
    .camera = camera,
    .renderer = renderer,
    .position = glm::vec2(commandTextSize.x, yPos),
    .value = "ESC",
    .color = Color(255),
    .layer = 5
  }).instantiate();

  totalHeight += commandTextSize.y;

  Sprite(Sprite::CreateInfo{
    .frame = {
      .color = Color(0, 0, 0, 150)
    },
    .transform = {
      .position = glm::vec2(0.0f, startY),
      .size = glm::vec2(
        commandTextSize.x + spacebarTextSize.x + _padding * 2,
        totalHeight + _padding
      ),
      .layer = 4
    },
    .renderer = renderer,
    .camera = camera,
  }).instantiate();
}