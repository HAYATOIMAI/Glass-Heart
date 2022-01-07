
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
		auto oldinput = _xinput;
		auto beforeinput = _DInput;

		//! ジョイパッド状態更新
		GetJoypadXInputState(DX_INPUT_PAD1, &_xinput);
		GetJoypadDirectInputState(DX_INPUT_PAD1, &_DInput);

		for (auto i = 0; i < 16; ++i) {
			//! キーのトリガ情報生成(押した瞬間しか反応しないキー情報)
			_triggerKey.Buttons[i] = (_xinput.Buttons[i] ^ oldinput.Buttons[i]) & _xinput.Buttons[i];
		}

		for (auto i = 0; i < 16; ++i) {
			//! キーのトリガ情報生成(押した瞬間しか反応しないキー情報)
			_DTrigger.Buttons[i] = (_DInput.Buttons[i] ^ beforeinput.Buttons[i] & _DInput.Buttons[i]);
		}
	}
}