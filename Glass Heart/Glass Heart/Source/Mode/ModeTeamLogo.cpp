
/*****************************************************************//**
 * @file   ModeTeamLogo.cpp
 * @brief  チームロゴ画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTeamLogo.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Mode;

//!< コンストラクタ
ModeTeamLogo::ModeTeamLogo(GameMain& game) : ModeMain{ game }
{
}
void ModeTeamLogo::Init() {
	//!< 使用する画像のテーブル
	const AppFrame::ResourceServer::GraphMap useGraph{
	{"TitleBg",          {"TitleBg.png",          1, 1, 1920, 1080}} };

	//!< リソースサーバーを取得
	auto& res = GetResourceServer();

	//!< 画像の読み込み
	res.LoadGraphics(useGraph);

	//!< 画像のハンドルの取得
	_titleBgHandle = res.GetGraph("TitleBg");

	//!< サウンドマネージャーを取得
	auto& sm = GetSoundManager();
	sm.PlayLoop("bgm1");
	sm.SetVolume("bgm1", 50);
}
//!< 入り口処理
void ModeTeamLogo::Enter() {
}
//!< 入力処理
void ModeTeamLogo::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputButtonB()) {
		GetModeServer().GoToMode("Title");
	}
}
//!< 更新処理
void ModeTeamLogo::Process() {
	//_alpha = (_alpha + 8) % 255;
}
//!< 描画処理
void ModeTeamLogo::Render() {
	DrawGraph(0, 0, _titleBgHandle, FALSE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
}