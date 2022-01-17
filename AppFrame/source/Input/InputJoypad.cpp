
/*****************************************************************//**
 * @file   InputJoypad.h
 * @brief  ジョイパッドクラスの処理
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "InputJoypad.h"

namespace AppFrame {

    void InputJoypad::Process() {
        auto oldinput = _xInput;
        auto beforeinput = _dInput;

        //! ジョイパッド状態更新
        GetJoypadXInputState(DX_INPUT_PAD1, &_xInput);
        GetJoypadDirectInputState(DX_INPUT_PAD1, &_dInput);

        for (auto i = 0; i < 16; ++i) {
            //! キーのトリガ情報生成(押した瞬間しか反応しないキー情報)
            _triggerKey.Buttons[i] = (_xInput.Buttons[i] ^ oldinput.Buttons[i]) & _xInput.Buttons[i];
        }

        for (auto i = 0; i < 16; ++i) {
            //! キーのトリガ情報生成(押した瞬間しか反応しないキー情報)
            _dTrigger.Buttons[i] = (_dInput.Buttons[i] ^ beforeinput.Buttons[i] & _dInput.Buttons[i]);
        }
    }
}