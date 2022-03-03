
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

    //!< 使用するモデル
    AppFrame::ResourceServer::ModelMap usemap{
    {"Player",    "Boy/PC2_motion.mv1"},
    {"Stage", "Stage/Zenhan01.mv1"},
    };
    //!< モデルの読み込み
    GetResourceServer().LoadModels(usemap);
    // 非同期読み込み開始
    SetUseASyncLoadFlag(TRUE);
}
/** 入り口処理 */
void Mode::ModeAmg::Enter() {
    
}
/** 入力処理 */
void Mode::ModeAmg::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("TeamLogo");
    }
}
/** 更新処理 */ 
void Mode::ModeAmg::Process() {
    //_alpha = (_alpha + 8) % 255;
}
/** 描画処理 */
void Mode::ModeAmg::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
    /*SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/
}