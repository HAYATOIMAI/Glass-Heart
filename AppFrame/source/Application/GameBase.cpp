
/*****************************************************************//**
 * @file   GameBase.cpp
 * @brief  アプリケーションの基底クラスの処理
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

	constexpr auto SCREENWIDTH  = 1920;   //!< 画面の横幅
	constexpr auto SCREENHEIGHT = 1080;  //!< 画面の縦幅
	constexpr auto SCREENDEPTH  = 32;     //!< カラービット数
}

namespace AppFrame {

	GameBase* GameBase::_gameInstance = nullptr;

	GameBase::GameBase() {
		//静的メンバに自分のクラス情報を入れる
		_gameInstance = this;
	}

	GameBase::~GameBase() {
	}

	bool GameBase::Initialize(HINSTANCE hInstance) {

		//! ウィンドウのタイトルを設定する
		SetMainWindowText("Glass Heart");

		//! 画面モードのを設定
		SetGraphMode(SCREENWIDTH, SCREENHEIGHT, SCREENDEPTH);

#ifndef _DEBUG
		//! Releaseビルド時にウィンドウモードを解除する
		ChangeWindowMode(false);
#endif // !_DEBUG
#ifdef _DEBUG
		//! Debugビルド時にウィンドウモードに指定する
		ChangeWindowMode(true);
#endif // DEBUG

		//! Dxライブラリ初期化
		if (DxLib_Init() == -1) {
			return false;
		}

		SetBackgroundColor(0, 0, 255);

		//! 描画先画面を裏にする
		SetDrawScreen(DX_SCREEN_BACK);

		//! Ｚバッファを有効にする
		SetUseZBuffer3D(TRUE);

		//! Ｚバッファへの書き込みを有効にする
		SetWriteZBuffer3D(TRUE);

		//! インプットマネージャーの生成
		_inputManage = std::make_unique<InputManager>();

		//! リソースサーバーの生成
		_resServer = std::make_unique<ResourceServer>(*this);

		//! サウンドマネージャーの生成
		_soundManage = std::make_unique<SoundManager>(*this);

		return true;
	}
	void GameBase::Terminate() {
		//! Dxライブラリ終了
		DxLib_End();
	}

	void GameBase::Process() {
		_modeServer->Process();
	}

	void GameBase::Render() {
		ClearDrawScreen();      //!< 画面をクリアする
		_modeServer->Render();
		ScreenFlip();           //!< 裏画面を表示する
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
		//! メインループ
		while (_gameState != GameState::End) {
			Input();    //!< 入力
			Process();  //!< 更新
			Render();   //!< 描画
		}
	}
}

