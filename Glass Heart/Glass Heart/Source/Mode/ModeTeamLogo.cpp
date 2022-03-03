
/*****************************************************************//**
 * @file   ModeTeamLogo.cpp
 * @brief  チームロゴ画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTeamLogo.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

/** コンストラクタ */
Mode::ModeTeamLogo::ModeTeamLogo(GameMain& game) : Mode::ModeMain{ game }{}
/** 初期化処理 */
void Mode::ModeTeamLogo::Init() {
    // 使用する画像のテーブル
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"TitleBg",          {"TeamLogo/kane.png",          1, 1, 1920, 1080}} };
    // リソースサーバーを取得
    auto& res = GetResourceServer();
    // 画像の読み込み
    res.LoadGraphics(useGraph);
    // 画像のハンドルの取得
    _titleBgHandle = res.GetGraph("TitleBg");
}
/** 入り口処理 */
void Mode::ModeTeamLogo::Enter() {
}
/** 入力処理 */
void Mode::ModeTeamLogo::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("Title");
    }
}
/** 更新処理 */
void Mode::ModeTeamLogo::Process() {
    //_alpha = (_alpha + 8) % 255;
}
/** 描画処理 */
void Mode::ModeTeamLogo::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
}