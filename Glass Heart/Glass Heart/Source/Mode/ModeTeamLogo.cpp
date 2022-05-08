/*****************************************************************//**
 * @file   ModeTeamLogo.cpp
 * @brief  チームロゴ画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTeamLogo.h"
#include "../Application/GameMain.h"

/** コンストラクタ */
GlassHeart::Mode::ModeTeamLogo::ModeTeamLogo(Application::GameMain& game) : Mode::ModeMain{ game }{}
/** 初期化処理 */
void GlassHeart::Mode::ModeTeamLogo::Init() {
    // 使用する画像のテーブル
    const AppFrame::Resource::ResourceServer::GraphMap useGraph{
    {"TeamLogo",          {"TeamLogo/TeamLogo.png",          1, 1, 1920, 1080}} 
    };

    auto& res = GetResourceServer();
    // 画像の読み込み
    res.LoadGraphics(useGraph);
    // リソースマネージャーから登録した画像を取得
    _teamLogo = res.GetGraph("TeamLogo");
    _fadeCount = 30;
}
/** 入り口処理 */
void GlassHeart::Mode::ModeTeamLogo::Enter() {}
/** 入力処理 */
void GlassHeart::Mode::ModeTeamLogo::Input(AppFrame::Input::InputManager& input) {
    // Bボタンが押された又は一定時間経過したらタイトルへ遷移
    if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
        GetModeServer().GoToMode("Title");
    }
}
/** 更新処理 */
void GlassHeart::Mode::ModeTeamLogo::Process() {
    if (_fadeCount > 0) {
        --_fadeCount;
    }
}
/** 描画処理 */
void GlassHeart::Mode::ModeTeamLogo::Render() {
    DrawGraph(0, 0, _teamLogo, FALSE);
}