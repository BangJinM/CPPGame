
#include "BaseApplication.h"
namespace GameEngine{
  bool BaseApplication::m_bQuit = false;
  void BaseApplication::Finalize() {}

  void BaseApplication::Tick() {}

  int BaseApplication::Initialize() {
      std::cout << m_Config;
      return 0;
  }

  bool BaseApplication::IsQuit() {
      return m_bQuit;
  }

  BaseApplication::BaseApplication(GfxConfiguration& cfg)
    :m_Config(cfg)
  {

  }
}
