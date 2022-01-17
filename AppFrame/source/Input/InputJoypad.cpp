
/*****************************************************************//**
 * @file   InputJoypad.h
 * @brief  �W���C�p�b�h�N���X�̏���
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "InputJoypad.h"

namespace AppFrame {

    void InputJoypad::Process() {
        auto oldinput = _xInput;
        auto beforeinput = _dInput;

        //! �W���C�p�b�h��ԍX�V
        GetJoypadXInputState(DX_INPUT_PAD1, &_xInput);
        GetJoypadDirectInputState(DX_INPUT_PAD1, &_dInput);

        for (auto i = 0; i < 16; ++i) {
            //! �L�[�̃g���K��񐶐�(�������u�Ԃ����������Ȃ��L�[���)
            _triggerKey.Buttons[i] = (_xInput.Buttons[i] ^ oldinput.Buttons[i]) & _xInput.Buttons[i];
        }

        for (auto i = 0; i < 16; ++i) {
            //! �L�[�̃g���K��񐶐�(�������u�Ԃ����������Ȃ��L�[���)
            _dTrigger.Buttons[i] = (_dInput.Buttons[i] ^ beforeinput.Buttons[i] & _dInput.Buttons[i]);
        }
    }
}