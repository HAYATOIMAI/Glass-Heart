/*****************************************************************//**
 * @file   InputJoypad.h
 * @brief  �W���C�p�b�h�N���X�̏���
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "InputJoypad.h"

namespace AppFrame {

    namespace Input {
        void InputJoypad::Process() {
            auto oldinput = _xInput;

            // �W���C�p�b�h��ԍX�V
            GetJoypadXInputState(DX_INPUT_PAD1, &_xInput);

            SetJoypadDeadZone(DX_INPUT_PAD1, 0.25);

            for (auto i = 0; i < 16; ++i) {
                // �L�[�̃g���K��񐶐�(�������u�Ԃ����������Ȃ��L�[���)
                _xTrigger.Buttons[i] = (_xInput.Buttons[i] ^ oldinput.Buttons[i]) & _xInput.Buttons[i];
            }
        }
    }
}