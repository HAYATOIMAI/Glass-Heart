
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

using namespace GlassHeart;

int Mode::ModeMain::_count;
int Mode::ModeMain::_countSeconds;
int Mode::ModeMain::_countMinutes;

//!< コンストラクタ
Mode::ModeGame::ModeGame(GameMain& game) : ModeMain{ game } {}
//!< 初期化処理
void Mode::ModeGame::Init() {
    //!< 使用するモデル
    AppFrame::ResourceServer::ModelMap usemap{
    {"Player",    "Boy/PC2_motion.mv1"},
    //{"SkySphere", "skysphere.mv1"},
    /*{"Ground",    "ground.mv1"},
    {"Terrain",   "Ground/Ground.mv1"},
    {"Test",      "Test/ST_test.mv1"},*/
    {"Stage", "Test/Zenhan.mv1"},
    };
    //!< モデルの読み込み
    GetResourceServer().LoadModels(usemap);
}
//!< 入り口処理
void Mode::ModeGame::Enter() {
    // ファクトリの生成とクリエイターの登録
    auto& of = GetObjectFactory();

    of.Register("Player", std::make_unique<Object::PlayerCreate>());
    of.Register("FollowCamera", std::make_unique<Object::FollowCameraCreate>());
    of.Register("Stage", std::make_unique<Object::StageCreate>());
    of.Register("CheckPoint", std::make_unique<Object::CheckPointCreate>());
    of.Register("GoalPoint", std::make_unique<Object::GoalPointCreate>());

    auto player = of.Create("Player");

    auto& os = GetObjectServer();

    os.Register("Player", player->GetPosition());
    os.Add(std::move(player));

    auto followCamera = of.Create("FollowCamera");
    os.Register("FollowCamera", followCamera->GetPosition());
    os.Add(std::move(followCamera));

    auto stage = of.Create("Stage");
    os.Add(std::move(stage));

    auto checkPoint = of.Create("CheckPoint");
    os.Add(std::move(checkPoint));

    auto& sm = GetSoundManager();

    sm.PlayLoop("bgm3");

    _count = 0;
    _countSeconds = 0;
    _countMinutes = 0;

    Process();
}
//!< 入力処理
void Mode::ModeGame::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputStart()) {
        GetModeServer().GoToMode("Title");
    }
    GetObjectServer().Input(input);
}
//!< 更新処理
void Mode::ModeGame::Process() {
    GetObjectFactory().UpdateSpawn();
    GetObjectServer().Process();

    if (_count < 60) {
        ++_count;
    }
    if (_count == 60) {
        _count = 0;
        ++_countSeconds;
    }
    if (_countSeconds == 60) {
        _countSeconds = 0;
        ++_countMinutes;
    }
}
//!< 描画処理
void Mode::ModeGame::Render() {
    GetObjectServer().Render();

#ifdef _DEBUG
    auto x = 1000; auto y = 0; auto size = 32;
    auto white = GetColor(255, 255, 255);

    // 現在の時間(仮)
    DrawFormatString(x, y, white, "現在の時間: %d ", _count); y += size;
    DrawFormatString(x, y, white, "現在の時間: %d秒 ", _countSeconds); y += size;
    DrawFormatString(x, y, white, "現在の時間: %d分 ", _countMinutes); y += size;
#endif // DEBUG
}
//!< 終了処理
void Mode::ModeGame::Exit() {
    ////!< オブジェクトを消去
    //GetObjectServer().AllClear();
    ////!< リソースの消去
    //GetResourceServer().AllClear();
    ////!< クリエイターを削除
    //GetObjectFactory().Clear();
}