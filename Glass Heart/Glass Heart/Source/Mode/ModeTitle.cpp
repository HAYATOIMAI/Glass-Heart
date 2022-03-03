
/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  タイトル画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTitle.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

// コンストラクタ
Mode::ModeTitle::ModeTitle(GameMain& game) : ModeMain{ game } {}
// 初期化処理
void Mode::ModeTitle::Init() {
    // 使用する画像のテーブル
    const AppFrame::ResourceServer::GraphMap useGraph{
        {"TitleButton",   {"Title/TitleButton.png", 1, 1, 1920, 1080}},
        {"TitleLogo",     {"Title/TitleLogo.png",   1, 1, 1920, 1080}},
        {"Title",         {"Title/Title.png",       1, 1, 1920, 1080}},
    };

    // リソースサーバーを取得
    auto& res = GetResourceServer();

    // 画像の読み込み
    res.LoadGraphics(useGraph);

    // 画像のハンドルの取得
    _title = res.GetGraph("Title");
    _titleBgHandle = res.GetGraph("TitleBG");
    _titleButtonHandle = res.GetGraph("TitleButton");
    _titleLogo = res.GetGraph("TitleLogo");
}
// 入り口処理
void Mode::ModeTitle::Enter() {}
// 入力処理
void Mode::ModeTitle::Input(AppFrame::InputManager& input) {

    auto [handle, no] = GetGame().GetResourceServer().GetModles("Stage");
    
    if (input.GetJoyPad().GetXinputButtonB()) {
            GetModeServer().GoToMode("Loading");
    }
    /* if (input.GetJoyPad().GetXinputButtonB()) {
        if (CheckHandleASyncLoad(handle) == TRUE) {
            GetModeServer().GoToMode("Loading");
        }
        else if (CheckHandleASyncLoad(handle) == FALSE) {
            GetModeServer().GoToMode("InGame");
        }
    }*/
}
// 更新処理
void Mode::ModeTitle::Process() {}
// 描画処理
void Mode::ModeTitle::Render() {
    DrawGraph(0, 0, _title, FALSE);
}