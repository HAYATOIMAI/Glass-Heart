
/*****************************************************************//**
 * @file   ModeAmg.cpp
 * @brief  AMG画面クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeAmg.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

/** コンストラクタ */
Mode::ModeAmg::ModeAmg(GameMain& game) : ModeMain{ game } {}
/** 初期化処理 */
void Mode::ModeAmg::Init() {
    
    // 使用する画像のテーブル
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"AMGBg",          {"Amg/AMG.jpg",          1, 1, 1920, 1080}}
    };
    // リソースサーバーを取得
    auto& res = GetResourceServer();

    // 画像の読み込み
    res.LoadGraphics(useGraph);

    // 画像のハンドルの取得
    _titleBgHandle = res.GetGraph("AMGBg");

    AppFrame::ResourceServer::GraphMap usegramap{
        {"0", {"Numberplate/0.png",1,1,75,120} },
        {"1", {"Numberplate/1.png",1,1,75,120} },
        {"2", {"Numberplate/2.png",1,1,75,120} },
        {"3", {"Numberplate/3.png",1,1,75,120} },
        {"4", {"Numberplate/4.png",1,1,75,120} },
        {"5", {"Numberplate/5.png",1,1,75,120} },
        {"6", {"Numberplate/6.png",1,1,75,120} },
        {"7", {"Numberplate/7.png",1,1,75,120} },
        {"8", {"Numberplate/8.png",1,1,75,120} },
        {"9", {"Numberplate/9.png",1,1,75,120} },
        {"timer",{"Numberplate/Timer.png",1,1,2377,2361}},
        {"Death",{"BackGround/break.png",1,1,1920,1080}}
    };
    GetResourceServer().LoadGraphics(usegramap);

    //!< 使用するモデル
    AppFrame::ResourceServer::ModelMap usemap{
    {"Stage", "Stage/Stage04.mv1"},
    {"BackGround", "BackGround/bg.mv1"},
    };
    // モデルの読み込み
    GetResourceServer().LoadModels(usemap);
    // 非同期読み込み開始
    SetUseASyncLoadFlag(TRUE);
    _fadeCount = 30;
}
/** 入り口処理 */
void Mode::ModeAmg::Enter() {}
/** 入力処理 */
void Mode::ModeAmg::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
        GetModeServer().GoToMode("TeamLogo");
    }
}
/** 更新処理 */ 
void Mode::ModeAmg::Process() {
    if (_fadeCount > 0) {
        --_fadeCount;
    }
}
/** 描画処理 */
void Mode::ModeAmg::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
}