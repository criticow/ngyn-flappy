#include <ngyn/ngyn.hpp>

using namespace ngyn;

class Bird : public AnimatedSprite
{
  public:
  Bird();

  void update();

  bool isDead;

  private:
  float speed;
  float targetY;
  bool falling;
};