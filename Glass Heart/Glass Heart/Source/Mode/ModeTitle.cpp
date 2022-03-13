
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
         {"TitleExit",     {"Title/TitleExit.png",   1, 1, 1920, 1080}},
         {"TitleLogo",     {"Title/TitleLogo.png",   1, 1, 1920, 1080}},
         {"TitleBg",       {"Title/TitleBG.png",     1, 1, 1920, 1080}},
         {"TitlePlate",    {"Title/TitlePlate.png",  1, 1, 1920, 1080}},
         {"TitlePlate2",   {"Title/TitlePlate2.png", 1, 1, 1920, 1080}},
    };

    // リソースサーバーを取得
    auto& res = GetResourceServer();

    // 画像の読み込み
    res.LoadGraphics(useGraph);

    //!< 画像のハンドルの取得
    _titleButton = res.GetGraph("TitleButton");
    _titleExit = res.GetGraph("TitleExit");
    _titleLogo = res.GetGraph("TitleLogo");
    _titleBg = res.GetGraph("TitleBg");
    _titlePlate = res.GetGraph("TitlePlate");
    _titlePlate2 = res.GetGraph("TitlePlate2");
}
// 入り口処理
void Mode::ModeTitle::Enter() {
    _alpha = 0;
    _x = -1920;
    auto& sm = GetSoundManager();
    sm.PlayLoop("titleBgm");
}
// 入力処理
void Mode::ModeTitle::Input(AppFrame::InputManager& input) {

    auto [handle, no] = GetGame().GetResourceServer().GetModles("Stage");

    if (input.GetJoyPad().GetXinputButtonB()) {
        auto& sm = GetSoundManager();
        sm.Play("select");
        GetModeServer().GoToMode("Loading");
        _alpha = 255;
    }

    auto center = 0;
    auto leftEnd = -1920;

    if (input.GetJoyPad().GetXTriggerLeft() || input.GetJoyPad().GetXTriggerLeftShoulder()) {
        if (_x != center) {
            _x = center;
        }
        else if (_x == center) {
            _x = leftEnd;
        }
        //if (_x2 != center) {
        //    if (_x < center) {
        //        _x = center;
        //    }
        //    else {
        //        _x = leftEnd;
        //        _x2 = center;
        //    }
        //}
        //else if (_x2 < rightEnd) {
        //    _x2 = rightEnd;
        //}
    }
    if (input.GetJoyPad().GetXTriggerRight() || input.GetJoyPad().GetXTriggerRightShoulder()) {
        if (_x != center) {
            _x = center;
        }
        else if (_x == center) {
            _x = leftEnd;
        }
        //if (_x != center) {
        //    if (_x2 > center) {
        //        _x2 = center;
        //    }
        //    else {
        //        _x2 = rightEnd;
        //        _x = center;
        //    }
        //}
        //else if (_x < rightEnd) {
        //    _x = leftEnd;
        //}
    }
}
// 更新処理
void Mode::ModeTitle::Process() {
    _alpha = (_alpha + 2) % 255;
}
// 描画処理
void Mode::ModeTitle::Render() {

    DrawGraph(0, 0, _titleBg, TRUE);
    DrawGraph(0, 0, _titleLogo, TRUE);
    DrawGraph(0, 0, _titleExit, TRUE);
    if (_x != 0) {
        DrawGraph(0, 0, _titlePlate, TRUE);
    }
    DrawGraph(_x, 0, _titlePlate2, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawGraph(0, 0, _titleButton, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Mode::ModeTitle::Exit() {
    auto& sm = GetSoundManager();
    sm.StopSound("titleBgm");
}
