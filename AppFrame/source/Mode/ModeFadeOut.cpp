/*********************************************************************
 * @file   ModeFadeOut.cpp
 * @brief  �t�F�[�h�A�E�g�N���X�̏���
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#include "ModeFadeOut.h"
#include "ModeServer.h"
#include <DxLib.h>

namespace {
	constexpr float ALPHA_MIN = 0.f;        //!< �A���t�@�l�Œ�l
	constexpr float ALPHA_MAX = 255.f;     //!< �A���t�@�l�ő�l
	constexpr float FADE_TIME = 75.555f;  //!< �Ó]����
	constexpr float ALPHA_DELTA = (ALPHA_MAX / FADE_TIME);  //!< �A���t�@�l�̍���
}

namespace AppFrame {
	namespace Mode {
		/** �R���X�g���N�^ */
		ModeFadeOut::ModeFadeOut(GameBase& game) : ModeFade{ game } {}
		/** �f�X�g���N�^ */
		ModeFadeOut::~ModeFadeOut() {}
		/** ��������� */
		void ModeFadeOut::Enter() {
			_alpha = ALPHA_MIN;
			_deltaAlpha = ALPHA_DELTA;
		}
		/** �X�V���� */
		void ModeFadeOut::Process() {
			_alpha += _deltaAlpha;
			if (_alpha >= ALPHA_MAX) {
				_alpha = ALPHA_MAX;
				GetModeServer().PopBack(); // FadeOut���g���|�b�v�o�b�N
				GetModeServer().PopBack(); // FadeOut���̃V�[�����ꏏ�Ƀ|�b�v�o�b�N
			}
		}
	} // namespace Mode
} // namespace AppFrame 