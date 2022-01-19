
/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  ゲーム内クラスの処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/GameMain.h"
#include "../Camera/CameraManager.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"
#include <AppFrame.h>

using namespace GlassHeart::Mode;

//!< コンストラクタ
ModeGame::ModeGame(GameMain& game) : ModeMain{ game } {
}
//!< 初期化処理
void ModeGame::Init() {
    //!< 使用するモデル
    AppFrame::ResourceServer::ModelMap usemap{
    {"Player",    "SDChar/SDChar.mv1"},
    {"SkySphere", "skysphere.mv1"},
    {"Ground",    "ground.mv1"},
    {"Terrain",   "Ground/Ground.mv1"},
    {"Test",      "Test/ST_test.mv1"},
    };
    //!< モデルの読み込み
    GetResourceServer().LoadModels(usemap);
}
//!< 入り口処理
void ModeGame::Enter() {
    // ファクトリの生成とクリエイターの登録
    auto& of = GetObjectFactory();

    of.Register("Player", std::make_unique<Object::PlayerCreate>());
    of.Register("Stage", std::make_unique<Object::StageCreate>());

    auto player = of.Create("Player");

    auto& os = GetObjectServer();

    os.Register("Player", player->GetPosition());
    os.Add(std::move(player));

    auto stage = of.Create("Stage");
    os.Add(std::move(stage));

    Process();
}
//!< 入力処理
void ModeGame::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputStart()) {
        GetModeServer().GoToMode("Title");
    }
    GetObjectServer().Input(input);
}
//!< 更新処理
void ModeGame::Process() {
    GetObjectFactory().UpdateSpawn();
    GetObjectServer().Process();
}
//!< 描画処理
void ModeGame::Render() {
    GetObjectServer().Render();
}
//!< 終了処理
void ModeGame::Exit() {
    //!< オブジェクトを消去
    GetObjectServer().AllClear();
    //!< リソースの消去
    GetResourceServer().AllClear();
    //!< クリエイターを削除
    GetObjectFactory().Clear();
}