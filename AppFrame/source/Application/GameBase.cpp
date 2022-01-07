
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

namespace {

	constexpr auto SCREENWIDTH  = 1920;   //!< ��ʂ̉���
	constexpr auto SCREENHEIGHT = 1080;  //!< ��ʂ̏c��
	constexpr auto SCREENDEPTH  = 32;     //!< �J���[�r�b�g��
}

namespace AppFrame {

	GameBase* GameBase::_gameInstance = nullptr;

	GameBase::GameBase() {
		//�ÓI�����o�Ɏ����̃N���X��������
		_gameInstance = this;
	}

	GameBase::~GameBase() {
	}

	bool GameBase::Initialize(HINSTANCE hInstance) {

		//! �E�B���h�E�̃^�C�g����ݒ肷��
		SetMainWindowText("Glass Heart");

		//! ��ʃ��[�h�̂�ݒ�
		SetGraphMode(SCREENWIDTH, SCREENHEIGHT, SCREENDEPTH);

#ifndef _DEBUG
		//! Release�r���h���ɃE�B���h�E���[�h����������
		ChangeWindowMode(false);
#endif // !_DEBUG
#ifdef _DEBUG
		//! Debug�r���h���ɃE�B���h�E���[�h�Ɏw�肷��
		ChangeWindowMode(true);
#endif // DEBUG

		//! Dx���C�u����������
		if (DxLib_Init() == -1) {
			return false;
		}

		SetBackgroundColor(0, 0, 255);

		//! �`����ʂ𗠂ɂ���
		SetDrawScreen(DX_SCREEN_BACK);

		//! �y�o�b�t�@��L���ɂ���
		SetUseZBuffer3D(TRUE);

		//! �y�o�b�t�@�ւ̏������݂�L���ɂ���
		SetWriteZBuffer3D(TRUE);

		//! �C���v�b�g�}�l�[�W���[�̐���
		_inputManage = std::make_unique<InputManager>();

		//! ���\�[�X�T�[�o�[�̐���
		_resServer = std::make_unique<ResourceServer>(*this);

		//! �T�E���h�}�l�[�W���[�̐���
		_soundManage = std::make_unique<SoundManager>(*this);

		return true;
	}
	void GameBase::Terminate() {
		//! Dx���C�u�����I��
		DxLib_End();
	}

	void GameBase::Process() {
		_modeServer->Process();
	}

	void GameBase::Render() {
		ClearDrawScreen();      //!< ��ʂ��N���A����
		_modeServer->Render();
		ScreenFlip();           //!< ����ʂ�\������
	}

	void GameBase::Input() {
		if (ProcessMessage() == -1) {
			_gameState = GameState::End;
		}
		_inputManage->Process();
#ifdef _DEBUG
		if (1 == CheckHitKey(KEY_INPUT_ESCAPE)) {
			_gameState = GameState::End;
		}
#endif // DEBUG
		_modeServer->Input(*_inputManage);
	}

	void GameBase::Run() {
		//! ���C�����[�v
		while (_gameState != GameState::End) {
			Input();    //!< ����
			Process();  //!< �X�V
			Render();   //!< �`��
		}
	}
}

