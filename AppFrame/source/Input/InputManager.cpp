/*****************************************************************//**
 * @file   InputManager.cpp
 * @brief  インプットマネージャークラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "InputManager.h"

namespace AppFrame {
  namespace Input {
    void InputManager::Process() {
      _inputjoy.Process();
    }
  }
}