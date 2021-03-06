
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
#include "../UI/UI.h"
#include <AppFrame.h>

using namespace GlassHeart;

/** コンストラクタ */
Mode::ModeGame::ModeGame(GameMain& game) : ModeMain{ game } {}
/** 初期化処理 */
void Mode::ModeGame::Init() {
    // リソースサーバーを取得
    auto& res = GetResourceServer();
    // 画像のハンドルの取得
    _teamLogo = res.GetGraph("TeamLogo");
    _titleLogo = res.GetGraph("TitleLogo");
}
/** 入り口処理 */
void Mode::ModeGame::Enter() {
    // ファクトリーの生成とクリエイターの登録
    auto& of = GetObjectFactory();
    auto& os = GetObjectServer();

    of.Register("Player", std::make_unique<Object::PlayerCreate>());
    of.Register("Girl", std::make_unique<Object::GirlCreate>());
    of.Register("FollowCamera", std::make_unique<Object::FollowCameraCreate>());
    of.Register("Stage", std::make_unique<Object::StageCreate>());
    of.Register("CheckPoint", std::make_unique<Object::CheckPointCreate>());
    of.Register("GoalPoint", std::make_unique<Object::GoalPointCreate>());

    auto player = of.Create("Player");

    os.Register("Player", player->GetPosition());
    os.Add(std::move(player));

    auto girl = of.Create("Girl");
    os.Register("Girl", girl->GetPosition());
    os.Add(std::move(girl));

    auto followCamera = of.Create("FollowCamera");
    os.Register("FollowCamera", followCamera->GetPosition());
    os.Add(std::move(followCamera));

    auto stage = of.Create("Stage");
    os.Add(std::move(stage));

    auto checkPoint = of.Create("CheckPoint");
    os.Add(std::move(checkPoint));

    auto goalPoint = of.Create("GoalPoint");
    os.Add(std::move(goalPoint));

    auto& sm = GetSoundManager();
    sm.PlayLoop("bgm");

    _count = 60;
    _countSeconds = 350;

    auto& ui = GetUI();
    ui.Enter();
    
    _deathDrawHundle = _game.GetResourceServer().GetGraph("Death");

    Process();
}
/** 入力処理 */
void Mode::ModeGame::Input(AppFrame::InputManager& input) {
    // オブジェクトの入力処理
    GetObjectServer().Input(input);
}
/** 更新処理 */
void Mode::ModeGame::Process() {
    // オブジェクトの更新処理
    GetObjectServer().Process();
   // タイマー処理
    if (_count <= 60) {
        --_count;
    }
    if (_count == 0) {
        _count = 60;
        --_countSeconds;
    }
    if (_countSeconds < 0) {
        _countSeconds = 0;
    }
    if (_countSeconds == 0) {
        GetModeServer().GoToMode("GameClear");
    }
    GetUI().Process(_countSeconds);
}
/** 描画処理 */
void Mode::ModeGame::Render() {
    // オブジェクトを描画
    GetObjectServer().Render();
    // UIを描画
    GetUI().Render(100, 100, 0.05);
    // 秒数描画
    GetUI().NumberRender(400, 100, 80, 1.0);
    for (auto& itr : GetObjectServer().GetObjectLists()) {
        if (itr->GetObjectType() == Object::ObjectBase::ObjectType::Player) {
            if (itr->GetDeadFlag()) {
                DrawRotaGraph(960, 540, 1.0, 0.0, _deathDrawHundle, TRUE);
            }
        }
    }
    // チームロゴとタイトル画像描画
    DrawBillboard3D(VGet(22500.0f, 12600.0f, 200.0f), 0.5f, 0.5f, 800.0f, 0.0f, _teamLogo, TRUE);
    DrawBillboard3D(VGet(25450.0f, 12400.0f, 200.0f), 0.5f, 0.5f, 1200.0f, 0.0f, _titleLogo, TRUE);
#ifdef _DEBUG
    auto x = 1000; auto y = 0; auto size = 32;
    auto white = GetColor(255, 255, 255);

    //DrawFormatString(x, y, white, "現在の時間: %d ", _count); y += size;
    DrawFormatString(x, y, white, "現在の時間: %d秒 ", _countSeconds); y += size;
#endif // DEBUG
}
/** 終了処理 */
void Mode::ModeGame::Exit() {
    // BGMとSEを停止
    auto& sm = GetSoundManager();
    sm.StopSound("bgm");
    sm.StopSound("run");
}