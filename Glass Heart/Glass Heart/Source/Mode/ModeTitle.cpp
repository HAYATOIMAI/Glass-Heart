
/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  タイトル画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTitle.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Mode;

//!< コンストラクタ
ModeTitle::ModeTitle(GameMain& game) : ModeMain{ game } {
}
//!< 初期化処理
void ModeTitle::Init() {
    //! 使用する画像のテーブル
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"GameTitle",        {"GameTitle.png",        1, 1, 1553, 224}},
    {"LeftClickToStart", {"LeftClickToStart.png", 1, 1, 1135, 107}},
    };

    //!< リソースサーバーを取得
    auto& res = GetResourceServer();

    //!< 画像の読み込み
    res.LoadGraphics(useGraph);

    //!< 画像のハンドルの取得
    _titleBgHandle = res.GetGraph("GameTitle");

    //!< サウンドマネージャーを取得
    auto& sm = GetSoundManager();
    sm.PlayLoop("bgm1");
    sm.SetVolume("bgm1", 50);

}
//!< 入り口処理
void ModeTitle::Enter() {
}
//!< 入力処理
void ModeTitle::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("InGame");
    }
}
//!< 更新処理
void ModeTitle::Process() {
}
//!< 描画処理
void ModeTitle::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
    //SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawGraph(0, 0, _gameTitleHandle, TRUE);
}