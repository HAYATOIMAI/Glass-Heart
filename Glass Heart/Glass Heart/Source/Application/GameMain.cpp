/*****************************************************************//**
 * @file   GameMain.cpp
 * @brief  このプロジェクトのメイン処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "GameMain.h"
#include "../Mode/ModeLogo.h"
#include "../Mode/ModeGame.h"
#include "../Mode/ModeTitle.h"
#include "../Mode/ModeTeamLogo.h"
#include "../Mode/ModeClear.h"
#include "../Mode/ModeLoading.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../UI/UI.h"

namespace {
  constexpr int_fast16_t Volume = 128;   //!< 音声のボリューム
  constexpr int_fast16_t SeVolume = 255;
  constexpr auto Amg = "Amg";
  constexpr auto TeamLogo = "TeamLogo";
  constexpr auto Title = "Title";
  constexpr auto Loading = "Loading";
  constexpr auto InGame = "InGame";
  constexpr auto GameClear = "GameClear";
  constexpr auto Resource = "resource";
}
 /** 実体 */
GlassHeart::Application::GameMain _gameMain;
/** コンストラクタ */
GlassHeart::Application::GameMain::GameMain() {}
/** デストラクタ */
GlassHeart::Application::GameMain::~GameMain() {}
/**  初期化処理 */
bool GlassHeart::Application::GameMain::Initialize(HINSTANCE hInstance) {
  if (!base::Initialize(hInstance)) { return false; }

  auto& res = GetResourceServer();
  /** リソースのカレントフォルダ設定 */
  res.ChangeCurrentFile(Resource);
#ifdef _DEBUG
  /** マテリアルの自己発光色を暗い青色にする */
  MATERIALPARAM material;
  material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
  material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
  material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
  material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
  material.Power = 20.0f;
  SetMaterialParam(material);
#endif
  /** 使用する音のテーブル */
  const AppFrame::Resource::ResourceServer::SoundMap useSound {
    // BGM
    {"bgm",      {"Sound/BGM/BGM01_Ver2.mp3",false}},
    {"titleBgm", {"Sound/BGM/titleBGM.mp3",false}},
    // SE
    {"walk",     {"Sound/SE/SE_Walk.wav",true}},
    {"run",      {"Sound/SE/SE_Run.wav",true}},
    {"jump",     {"Sound/SE/SE_Jump.wav",true}},
    {"landing",  {"Sound/SE/SE_Landing.wav",true}},
    {"death",    {"Sound/SE/SE_Death.wav",true}},
    {"select",   {"Sound/SE/SE_Select.wav",true}}
  };
  /** 音を読み込み */
  res.LoadSounds(useSound);
  // サウンドマネージャーの取得
  auto& sm = GetSoundManager();
  sm.SetVolume("bgm",      Volume);
  sm.SetVolume("titleBgm", Volume);
  sm.SetVolume("walk",     Volume);
  sm.SetVolume("run",      SeVolume);
  sm.SetVolume("jump",     SeVolume);
  sm.SetVolume("landing",  SeVolume);
  sm.SetVolume("death",    Volume);
  sm.SetVolume("select",   SeVolume);
#ifndef _DEBUG
  sm.SetMute(false);
#endif // !DEBUG
#ifdef _DEBUG
  sm.SetMute(false);
#endif // DEBUG
  // オブジェクトサーバーの生成
  _objServer = std::make_unique<Object::ObjectServer>();
  // オブジェクトファクトリーの生成
  _objFactory = std::make_unique<Object::ObjectFactory>(*this);
  // ユーザーインターフェース生成
  _ui = std::make_unique<GlassHeart::UI::UI>(*this);
  // モードサーバーを生成し、AMGモードを登録
  _modeServer = std::make_unique<AppFrame::Mode::ModeServer>(Amg, std::make_shared<Mode::ModeLogo>(*this));
  // チームロゴモードを登録
  _modeServer->Register(TeamLogo, std::make_shared<Mode::ModeTeamLogo>(*this));
  // タイトルモードを登録
  _modeServer->Register(Title, std::make_shared<Mode::ModeTitle>(*this));
  //　ローディングモードを登録
  _modeServer->Register(Loading, std::make_shared<Mode::ModeLoading>(*this));
  // インゲームモードを登録
  _modeServer->Register(InGame, std::make_shared<Mode::ModeGame>(*this));
  // ゲームクリアモードを登録
  _modeServer->Register(GameClear, std::make_shared<Mode::ModeClear>(*this));
  return true;
}
/** 解放処理 */
void GlassHeart::Application::GameMain::Terminate() {
  base::Terminate();
}
/** 入力処理 */
void GlassHeart::Application::GameMain::Input() {
  base::Input();
}
/** 更新処理 */
void GlassHeart::Application::GameMain::Process() {
  base::Process();
}
/** 描画処理 */
void GlassHeart::Application::GameMain::Render() {
  base::Render();
}
/** メインループ */
void GlassHeart::Application::GameMain::Run() {
  base::Run();
}