/*****************************************************************//**
 * @file   InputJoypad.h
 * @brief  ジョイパッドクラスの処理
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "InputJoypad.h"

namespace {
  constexpr auto Zone = 0.25;
}

namespace AppFrame {
  namespace Input {
    void InputJoypad::Process() {
      auto oldinput = _xInput;

      // ジョイパッド状態更新
      GetJoypadXInputState(DX_INPUT_PAD1, &_xInput);
      // デッドゾーンを設定
      SetJoypadDeadZone(DX_INPUT_PAD1, Zone);

      for (auto i = 0; i < 16; ++i) {
        // キーのトリガ情報生成(押した瞬間しか反応しないキー情報)
        _xTrigger.Buttons[i] = (_xInput.Buttons[i] ^ oldinput.Buttons[i]) & _xInput.Buttons[i];
      }
    }
  }
}