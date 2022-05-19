/*****************************************************************//**
 * @file   GameBase.cpp
 * @brief  �A�v���P�[�V�����̊��N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "GameBase.h"
#include "../Input/InputManager.h"
#include "../Resource/ResourceServer.h"
#include "../Mode/ModeServer.h"
#include "../Sound/SoundManager.h"
#include "../Mode/ModeFade.h"
#include "../Utility/Utility.h"
#include <DxLib.h>

namespace {
	constexpr auto ScreenDepth = 32;    //!< �J���[�r�b�g��
}

namespace AppFrame {
	GameBase* GameBase::_gameInstance = nullptr;
	/** �R���X�g���N�^ */
	GameBase::GameBase() {
		//�ÓI�����o�Ɏ����̃N���X��������
		_gameInstance = this;
	}
	/** �f�X�g���N�^ */
	GameBase::~GameBase() {}
	/** ���������� */
	bool GameBase::Initialize(HINSTANCE hInstance) {
		// Log.txt���o�͂��Ȃ�
		SetOutApplicationLogValidFlag(false);

		// �E�B���h�E�̖��O��ݒ肷��
		auto windowName = SetWindowName();
		SetMainWindowText(windowName.c_str());

#ifdef _DEBUG
		Utility::Utility::CheckMemoryLeak();
#endif // _DEBUG

		// ��ʃ��[�h�̂�ݒ�
		SetGraphMode(SetWindowWidthSize(), SetWindowHeightSize(), ScreenDepth);

		ChangeWindowMode(true);

		// Dx���C�u����������
		if (DxLib_Init() == -1) {
			return false;
		}

		// �`����ʂ𗠂ɂ���
		SetDrawScreen(DX_SCREEN_BACK);

		// �y�o�b�t�@��L���ɂ���
		SetUseZBuffer3D(TRUE);

		// �y�o�b�t�@�ւ̏������݂�L���ɂ���
		SetWriteZBuffer3D(TRUE);

		// �C���v�b�g�}�l�[�W���[�̐���
		_inputManage = std::make_unique<Input::InputManager>();

		// ���\�[�X�T�[�o�[�̐���
		_resServer = std::make_unique<Resource::ResourceServer>(*this);

		// �T�E���h�}�l�[�W���[�̐���
		_soundManage = std::make_unique<Sound::SoundManager>(*this);

		return true;
	}
	/** ������� */
	void GameBase::Terminate() {
		// Dx���C�u�����I��
		DxLib_End();
	}
	/** �X�V���� */
	void GameBase::Process() {
		_modeServer->Process();
	}
	/** �`�揈�� */
	void GameBase::Render() {
		ClearDrawScreen();      // ��ʂ��N���A����
		_modeServer->Render();
		ScreenFlip();           // ����ʂ�\������
	}
	/** ���͏��� */
	void GameBase::Input() {
		if (ProcessMessage() == -1) {
			_gameState = GameState::End;
		}
		_inputManage->Process();
		// Back�{�^����ESC�L�[�������ꂽ��Q�[���I��
		if (_inputManage->GetJoyPad().GetXinputBack() || 1 == CheckHitKey(KEY_INPUT_ESCAPE)) {
			_gameState = GameState::End;
		}

		_modeServer->Input(*_inputManage);
	}
	/** ���C�����[�v */
	void GameBase::Run() {
		while (_gameState != GameState::End) {
			Input();    // ����
			Process();  // �X�V
			Render();   // �`��
		}
	}
}