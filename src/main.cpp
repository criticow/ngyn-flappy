#include <ngyn/ngyn.hpp>
#include "game.hpp"

#ifdef NDEBUG
  #define WIN32_LEAN_AND_MEAN
  #undef APIENTRY
  #include <Windows.h>
#endif

#ifdef _WIN32
  #ifdef NDEBUG
    int WINAPI WinMain(
      HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPSTR lpCmdLine,
      int nCmdShow
    )
    {
      ngyn::ngLogger.setLevel(ngyn::LoggerLevel::Error);
      ngyn::ngLogger.setMode(ngyn::LoggerMode::Quiet);

      Game game;
      game.run();
      return 0;
    }
  #else
    int main()
    {
      ngyn::ngLogger.setFormat("HH:mm:ss");
      Game game;
      game.run();
      return 0;
    }
  #endif
#endif