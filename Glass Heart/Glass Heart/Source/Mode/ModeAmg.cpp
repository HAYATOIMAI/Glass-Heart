
/*****************************************************************//**
 * @file   ModeAmg.cpp
 * @brief  AMG画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeAmg.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Mode;

//!< コンストラクタ
ModeAmg::ModeAmg(GameMain& game) : ModeBase{ game } {
}
//!< 初期化処理
void ModeAmg::Init() {
	//! 使用する画像のテーブル
	const AppFrame::ResourceServer::GraphMap useGraph{
	{"AMGBg",          {"Amg.png",          1, 1, 1920, 1080}}
	};

	//!< リソースサーバーを取得
	auto& res = GetResourceServer();

	//!< 画像の読み込み
	res.LoadGraphics(useGraph);

	//!< 画像のハンドルの取得
	_titleBgHandle = res.GetGraph("AMGBg");

	//!< サウンドマネージャーを取得
	auto& sm = GetSoundManager();
	sm.PlayLoop("bgm1");
	sm.SetVolume("bgm1", 50);

}
//!< 入り口処理
void ModeAmg::Enter() {
	_alpha = 0;
}
//!< 入力処理
void ModeAmg::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputButtonB()) {
		GetModeServer().GoToMode("TeamLogo");
		_alpha = 255;
	}
}
//!< 更新処理
void ModeAmg::Process() {
	_alpha = (_alpha + 8) % 255;
}
//!< 描画処理
void ModeAmg::Render() {
	DrawGraph(0, 0, _titleBgHandle, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}