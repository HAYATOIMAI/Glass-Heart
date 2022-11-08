/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  ゲーム内クラスの処理
 *
 * @author Hayato Imai, Yoshihiro Takahashi, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/GameMain.h"
#include "../Camera/CameraManager.h"
#include "../UI/UI.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../Object/PlayerCreate.h"
#include "../Object/GirlCreate.h"
#include "../Object/StageCreate.h"
#include "../Object/FollowCameraCreate.h"
#include "../Object/CheckPointCreate.h"
#include "../Object/GoalPointCreate.h"

namespace {
  constexpr VECTOR TeamLogoPosition = { 22500.0f, 12600.0f, 200.0f };   //!< チームロゴ画像の描画位置
  constexpr VECTOR TitleLogoPosition = { 25450.0f, 12400.0f, 200.0f };  //!< タイトルロゴ画像の描画位置
  constexpr	int_fast16_t Timer = 60;                                    //!< 経過する時間
  constexpr int_fast16_t TimeLimit = 350;                               //!< 制限時間
  constexpr int_fast32_t UiPosition  = 100;                             //!< UI描画位置
  constexpr int_fast32_t TimerNumberX = 400;                            //!< タイマー数字のX軸描画位置
  constexpr int_fast32_t TimerNumberY = 100;                            //!< タイマー数字のY軸描画位置
  constexpr int_fast32_t NumberInterval = 80;                           //!< タイマー数字の描画間隔
  constexpr int_fast32_t DeathEffectPositionX = 960;                    //!< 死亡時に表示する画像X軸位置
  constexpr int_fast32_t DeathEffectPositionY = 540;                    //!< 死亡時に表示する画像Y軸位置
  constexpr auto EffectExrate = 1.0;                                    //!< 死亡時に表示する画像の拡大率
  constexpr auto TimerExrate = 1.0;                                     //!< タイマー数字の拡大率
  constexpr auto RenderingExrate = 0.05;                                //!< 描画間隔
  constexpr auto MiddlePos = 0.5f;                                      //!< 描画する画像の中心座標
  constexpr auto NotRotate = 0.0f;                                      //!< 描画する画像の回転させる角度
  constexpr auto TeamLogoSize = 800.0f;                                 //!< 画像サイズ
  constexpr auto TitleSize = 1200.0f;                                   //!< 画像サイズ
  constexpr auto TeamLogo = "TeamLogo";                                 //!< リソースマネージャーから呼び出すファイル名
  constexpr auto TitleLogo = "TitleLogo";                               //!< リソースマネージャーから呼び出すファイル名
  constexpr auto Run = "run";                                           //!< 停止するサウンド
  constexpr auto Bgm = "bgm";                                           //!< 停止するサウンド
  constexpr auto Death = "Death";                                       //!< リソースマネージャーから呼び出すファイル名
  constexpr auto PlayerCreator = "Player";                              //!< 生成するオブジェクトの名前
  constexpr auto GirlCreator = "Girl";                                  //!< 生成するオブジェクトの名前
  constexpr auto FollowCameraCreator = "FollowCamera";                  //!< 生成するオブジェクトの名前
  constexpr auto StageCreator = "Stage";                                //!< 生成するオブジェクトの名前
  constexpr auto CheckPointCreator = "CheckPoint";                      //!< 生成するオブジェクトの名前
  constexpr auto GoalPointCreator = "GoalPoint";                        //!< 生成するオブジェクトの名前
  constexpr auto GameClear = "GameClear";                               //!< 遷移するモードの文字列
}

/** コンストラクタ */
GlassHeart::Mode::ModeGame::ModeGame(Application::GameMain& game) : ModeMain{ game } {}
/** 初期化処理 */
void GlassHeart::Mode::ModeGame::Init() {
  // リソースサーバーを取得
  auto& res = GetResourceServer();
  //リソースマネージャーから登録した画像を取得
  _teamLogo  = res.GetGraph(TeamLogo);
  _titleLogo = res.GetGraph(TitleLogo);
}
/** 入り口処理 */
void GlassHeart::Mode::ModeGame::Enter() {
  // オブジェクトを生成し、管理するマネージャーに登録する
  ObjectRegister();
  // BGMをループ再生
  auto& sm = GetSoundManager();
  sm.PlayLoop(Bgm);
  // タイマーの秒数をセット
  _count = Timer;
  _countSeconds = TimeLimit;
  // UIの入り口処理実行
  auto& ui = GetUI();
  ui.Enter();
  // リソースマネージャーから登録した画像を取得
  _deathDrawHundle = _game.GetResourceServer().GetGraph(Death);
  // 更新処理呼び出し
  Process();
}
/** 入力処理 */
void GlassHeart::Mode::ModeGame::Input(AppFrame::Input::InputManager& input) {
  // オブジェクトの入力処理
  GetObjectServer().Input(input);
}
/** 更新処理 */
void GlassHeart::Mode::ModeGame::Process() {
  // オブジェクトの更新処理
  GetObjectServer().Process();
  // タイマー経過処理
  TimerProcess();
}
/** 描画処理 */
void GlassHeart::Mode::ModeGame::Render() {
  // オブジェクトを描画
  GetObjectServer().Render();
  // UIを描画
  UiRenderring();
  // チームロゴとタイトル画像描画
  DrawBillboard3D(TeamLogoPosition, MiddlePos, MiddlePos, TeamLogoSize, NotRotate, _teamLogo, TRUE);
  DrawBillboard3D(TitleLogoPosition, MiddlePos, MiddlePos, TitleSize, NotRotate, _titleLogo, TRUE);
  // デバッグ用タイマー秒数表示
#ifdef _DEBUG
  auto x = 1000; auto y = 0; auto size = 32;
  auto white = GetColor(255, 255, 255);
  DrawFormatString(x, y, white, "現在の時間: %d秒 ", _countSeconds); y += size;
#endif // DEBUG
}
/** 終了処理 */
void GlassHeart::Mode::ModeGame::Exit() {
  // BGMとSEを停止
  auto& sm = GetSoundManager();
  sm.StopSound(Bgm);
  sm.StopSound(Run);
}
/** オブジェクトを生成、マネージャーに登録する */
void GlassHeart::Mode::ModeGame::ObjectRegister() {
  // ファクトリーの生成
  auto& of = GetObjectFactory();
  auto& os = GetObjectServer();
  // クリエイターの登録
  of.Register(PlayerCreator,       std::make_unique<Object::PlayerCreate>());
  of.Register(GirlCreator,         std::make_unique<Object::GirlCreate>());
  of.Register(FollowCameraCreator, std::make_unique<Object::FollowCameraCreate>());
  of.Register(StageCreator,        std::make_unique<Object::StageCreate>());
  of.Register(CheckPointCreator,   std::make_unique<Object::CheckPointCreate>());
  of.Register(GoalPointCreator,    std::make_unique<Object::GoalPointCreate>());

  auto player = of.Create(PlayerCreator);
  // オブジェクトサーバーに登録
  os.Register(PlayerCreator, player->GetPosition());
  os.Add(std::move(player));

  auto girl = of.Create(GirlCreator);
  os.Register(GirlCreator, girl->GetPosition());
  os.Add(std::move(girl));

  auto followCamera = of.Create(FollowCameraCreator);
  os.Register(FollowCameraCreator, followCamera->GetPosition());
  os.Add(std::move(followCamera));

  auto stage = of.Create(StageCreator);
  os.Add(std::move(stage));

  auto checkPoint = of.Create(CheckPointCreator);
  os.Add(std::move(checkPoint));

  auto goalPoint = of.Create(GoalPointCreator);
  os.Add(std::move(goalPoint));
}
/** タイマー経過処理 */
void GlassHeart::Mode::ModeGame::TimerProcess() {
  // プレイヤーの死亡状態ではない時のみタイマーを回す
  for (auto& itr : GetObjectServer().GetObjectLists()) {
    if (itr->GetObjectType() == Object::ObjectBase::ObjectType::Player) {
      if (itr->GetDeadFlag() == false) {
        // タイマー処理
        if (_count <= Timer) {
          --_count;
        }
        if (_count == 0) {
          _count = Timer;
          --_countSeconds;
        }
        if (_countSeconds < 0) {
          _countSeconds = 0;
        }
        // タイマーがゼロになったらクリアモードへ
        if (_countSeconds == 0) {
          GetModeServer().GoToMode(GameClear);
        }
        GetUI().Process(_countSeconds);
      }
    }
  }
}
/** UIを指定位置に描画 */
void GlassHeart::Mode::ModeGame::UiRenderring() {
  // UIを描画
  GetUI().Render(UiPosition, UiPosition, RenderingExrate);
  // 秒数描画
  GetUI().NumberRender(TimerNumberX, TimerNumberY, NumberInterval, TimerExrate);
  for (auto& itr : GetObjectServer().GetObjectLists()) {
    if (itr->GetObjectType() == Object::ObjectBase::ObjectType::Player) {
      if (itr->GetDeadFlag()) {
        DrawRotaGraph(DeathEffectPositionX, DeathEffectPositionY, EffectExrate, 0.0, _deathDrawHundle, TRUE);
      }
    }
  }
}