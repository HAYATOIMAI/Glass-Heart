
/*****************************************************************//**
 * @file   ModeServer.cpp
 * @brief  モードサーバークラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeServer.h"
#include "ModeBase.h"
#include "ModeFade.h"
#include "../Input/InputManager.h"
#include "../Application/GameBase.h"

namespace AppFrame {
	// コンストラクタ
	ModeServer::ModeServer(std::string_view key, std::shared_ptr<ModeBase> mode) {
		Register("FadeIn", std::make_shared<ModeFadeIn>(mode->GetGame()));
		Register("FadeOut", std::make_shared<ModeFadeOut>(mode->GetGame()));
		Register(key, mode);
		PushBack(key);
		PushBack("FadeIn");
	}
	//モードの登録
	void ModeServer::Register(std::string_view key, std::shared_ptr<ModeBase> mode) {
		if (_registry.contains(key.data())) {
			_registry.erase(key.data());
		}
		_registry.emplace(key, mode);
		mode->Init();
	}
	// モードの登録
	void ModeServer::PushBack(std::string_view key) {
		if (!_registry.contains(key.data())) {
			return;   // キーが未登録
		}
		auto pushScene = _registry[key.data()];
		pushScene->Enter();
		_mode.push_back(pushScene);
	}
	// モードのポップバック
	void ModeServer::PopBack() {
		if (_mode.empty()) {
			return;
		}
		_mode.back()->Exit();
		_mode.pop_back();
	}
	// モードの遷移 
	// ↑次のシーン
	// ↑フェードイン
	// ↑現在のシーン
	// ↑フェードアウト：最前面
	void ModeServer::GoToMode(std::string_view key) {
		InsertBelowBack(key.data());  //! 次のシーンを挿入
		InsertBelowBack("FadeIn");    //! フェードインを挿入
		PushBack("FadeOut");          //! フェードアウトをプッシュバック
	}
	// リストの一番後ろ(最前面)のシーンの真下に挿入
	void ModeServer::InsertBelowBack(std::string_view key) {
		if (!_registry.contains(key.data())) {
			return;   //! キーが未登録
		}
		auto insertScene = _registry[key.data()];
		insertScene->Enter();
		_mode.insert(std::prev(_mode.end()), insertScene);
	}
	// 入力処理
	void ModeServer::Input(InputManager& input) {
		if (_mode.empty()) {
			return;
		}
		_mode.back()->Input(input);
	}
	// 更新処理
	void ModeServer::Process() {
		if (_mode.empty()) {
			return;
		}
		_mode.back()->Process();
	}
	// 描画処理
	void ModeServer::Render() const {
		for (auto&& mode : _mode) {
			mode->Render();
		}
	}
}