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
#include "../Utility/Utility.h"
#include <DxLib.h>

namespace {
	constexpr auto ScreenDepth = 32;    //!< カラービット数
}

namespace AppFrame {
	GameBase* GameBase::_gameInstance = nullptr;
	/** コンストラクタ */
	GameBase::GameBase() {
		//静的メンバに自分のクラス情報を入れる
		_gameInstance = this;
	}
	/** デストラクタ */
	GameBase::~GameBase() {}
	/** 初期化処理 */
	bool GameBase::Initialize(HINSTANCE hInstance) {
		// Log.txtを出力しない
		SetOutApplicationLogValidFlag(false);

		// ウィンドウの名前を設定する
		auto windowName = SetWindowName();
		SetMainWindowText(windowName.c_str());

#ifdef _DEBUG
		Utility::Utility::CheckMemoryLeak();
#endif // _DEBUG

		// 画面モードのを設定
		SetGraphMode(SetWindowWidthSize(), SetWindowHeightSize(), ScreenDepth);

		ChangeWindowMode(true);

		// Dxライブラリ初期化
		if (DxLib_Init() == -1) {
			return false;
		}

		// 描画先画面を裏にする
		SetDrawScreen(DX_SCREEN_BACK);

		// Ｚバッファを有効にする
		SetUseZBuffer3D(TRUE);

		// Ｚバッファへの書き込みを有効にする
		SetWriteZBuffer3D(TRUE);

		// インプットマネージャーの生成
		_inputManage = std::make_unique<Input::InputManager>();

		// リソースサーバーの生成
		_resServer = std::make_unique<Resource::ResourceServer>(*this);

		// サウンドマネージャーの生成
		_soundManage = std::make_unique<Sound::SoundManager>(*this);

		return true;
	}
	/** 解放処理 */
	void GameBase::Terminate() {
		// Dxライブラリ終了
		DxLib_End();
	}
	/** 更新処理 */
	void GameBase::Process() {
		_modeServer->Process();
	}
	/** 描画処理 */
	void GameBase::Render() {
		ClearDrawScreen();      // 画面をクリアする
		_modeServer->Render();
		ScreenFlip();           // 裏画面を表示する
	}
	/** 入力処理 */
	void GameBase::Input() {
		if (ProcessMessage() == -1) {
			_gameState = GameState::End;
		}
		_inputManage->Process();
		// BackボタンかESCキーが押されたらゲーム終了
		if (_inputManage->GetJoyPad().GetXinputBack() || 1 == CheckHitKey(KEY_INPUT_ESCAPE)) {
			_gameState = GameState::End;
		}

		_modeServer->Input(*_inputManage);
	}
	/** メインループ */
	void GameBase::Run() {
		while (_gameState != GameState::End) {
			Input();    // 入力
			Process();  // 更新
			Render();   // 描画
		}
	}
}