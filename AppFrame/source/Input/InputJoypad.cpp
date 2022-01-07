
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
		auto oldinput = _xinput;
		auto beforeinput = _DInput;

		//! �W���C�p�b�h��ԍX�V
		GetJoypadXInputState(DX_INPUT_PAD1, &_xinput);
		GetJoypadDirectInputState(DX_INPUT_PAD1, &_DInput);

		for (auto i = 0; i < 16; ++i) {
			//! �L�[�̃g���K��񐶐�(�������u�Ԃ����������Ȃ��L�[���)
			_triggerKey.Buttons[i] = (_xinput.Buttons[i] ^ oldinput.Buttons[i]) & _xinput.Buttons[i];
		}

		for (auto i = 0; i < 16; ++i) {
			//! �L�[�̃g���K��񐶐�(�������u�Ԃ����������Ȃ��L�[���)
			_DTrigger.Buttons[i] = (_DInput.Buttons[i] ^ beforeinput.Buttons[i] & _DInput.Buttons[i]);
		}
	}
}