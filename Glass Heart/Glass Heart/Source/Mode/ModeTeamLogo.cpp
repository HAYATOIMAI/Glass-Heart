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
Mode::ModeTeamLogo::ModeTeamLogo(Application::GameMain& game) : Mode::ModeMain{ game }{}
/** 初期化処理 */
void Mode::ModeTeamLogo::Init() {
    // 使用する画像のテーブル
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"TeamLogo",          {"TeamLogo/TeamLogo.png",          1, 1, 1920, 1080}} };

    auto& res = GetResourceServer();
    // 画像の読み込み
    res.LoadGraphics(useGraph);
    // リソースマネージャーから登録した画像を取得
    _teamLogo = res.GetGraph("TeamLogo");
    _fadeCount = 30;

    //// 使用するモデル
    //AppFrame::ResourceServer::ModelMap useModel{
    //};
    //// モデルの読み込み
    //GetResourceServer().LoadModels(useModel);
}
/** 入り口処理 */
void Mode::ModeTeamLogo::Enter() {
}
/** 入力処理 */
void Mode::ModeTeamLogo::Input(AppFrame::InputManager& input) {
    // Bボタンが押された又は一定時間経過したらタイトルへ遷移
    if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
        GetModeServer().GoToMode("Title");
    }
}
/** 更新処理 */
void Mode::ModeTeamLogo::Process() {
    if (_fadeCount > 0) {
        --_fadeCount;
    }
}
/** 描画処理 */
void Mode::ModeTeamLogo::Render() {
    DrawGraph(0, 0, _teamLogo, FALSE);
}