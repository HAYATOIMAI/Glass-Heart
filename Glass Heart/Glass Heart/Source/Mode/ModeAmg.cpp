/*****************************************************************//**
 * @file   ModeAmg.cpp
 * @brief  AMG画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeAmg.h"
#include "../Application/GameMain.h"

 /** コンストラクタ */
GlassHeart::Mode::ModeAmg::ModeAmg(Application::GameMain& game) : ModeMain{ game } {}
/** 初期化処理 */
void GlassHeart::Mode::ModeAmg::Init() {
	// 使用する画像のテーブル
	const AppFrame::Resource::ResourceServer::GraphMap useGraph{
	{"AMGBg",  {"Amg/AMG.jpg",  1, 1, 1920, 1080} },
	{"0",      {"Numberplate/0.png", 1, 1, 75, 120} },
	{"1",      {"Numberplate/1.png", 1, 1, 75, 120} },
	{"2",      {"Numberplate/2.png", 1, 1, 75, 120} },
	{"3",      {"Numberplate/3.png", 1, 1, 75, 120} },
	{"4",      {"Numberplate/4.png", 1, 1, 75, 120} },
	{"5",      {"Numberplate/5.png", 1, 1, 75, 120} },
	{"6",      {"Numberplate/6.png", 1, 1, 75, 120} },
	{"7",      {"Numberplate/7.png", 1, 1, 75, 120} },
	{"8",      {"Numberplate/8.png", 1, 1, 75, 120} },
	{"9",      {"Numberplate/9.png", 1, 1, 75, 120} },
	{"timer",  {"Numberplate/Timer.png", 1, 1, 2377, 2361}},
	{"Death",  {"BackGround/break.png", 1, 1, 1920, 1080}}
	};

	auto& res = GetResourceServer();
	// 画像の読み込み
	res.LoadGraphics(useGraph);
	// リソースマネージャーから登録した画像を取得
	_titleBgHandle = res.GetGraph("AMGBg");

	// 使用するモデルのテーブル
	AppFrame::Resource::ResourceServer::ModelMap useMap{
	{"Stage", "Stage/Stage04.mv1"},
	{"BackGround", "BackGround/bg.mv1"},
	{"Player", "Boy/PC2_motion.mv1"},
	{"Girl", "Girl/Girl.mv1"},
	};
	// モデルの読み込み
	GetResourceServer().LoadModels(useMap);
	// 非同期読み込み開始
	SetUseASyncLoadFlag(TRUE);
	_fadeCount = 30;
}
/** 入り口処理 */
void GlassHeart::Mode::ModeAmg::Enter() {}
/** 入力処理 */
void GlassHeart::Mode::ModeAmg::Input(AppFrame::Input::InputManager& input) {
	if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
		GetModeServer().GoToMode("TeamLogo");
	}
}
/** 更新処理 */
void GlassHeart::Mode::ModeAmg::Process() {
	if (_fadeCount > 0) {
		--_fadeCount;
	}
}
/** 描画処理 */
void GlassHeart::Mode::ModeAmg::Render() {
	DrawGraph(0, 0, _titleBgHandle, FALSE);
}