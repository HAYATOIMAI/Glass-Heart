/*****************************************************************//**
 * @file   ModeFade.cpp
 * @brief  ���[�h�̃t�F�[�h�N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeFade.h"
#include "ModeServer.h"
#include <DxLib.h>

namespace AppFrame {

	namespace Mode {
		/** �R���X�g���N�^ */
		ModeFade::ModeFade(GameBase& game) : ModeBase{ game }, _color{ GetColor(0, 0, 0) }{}
		/** �f�X�g���N�^ */
		ModeFade::~ModeFade() {}
		/** ���������� */
		void ModeFade::Init() {
			_color = GetColor(0, 0, 0);
		}
		/** ��������� */
		void ModeFade::Enter() {}
		/** �X�V���� */
		void ModeFade::Process() {}
		/** �`�揈�� */
		void ModeFade::Render() {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
			DrawBox(0, 0, _width, _height, _color, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	} // namespace Mode
} // namespace AppFrame