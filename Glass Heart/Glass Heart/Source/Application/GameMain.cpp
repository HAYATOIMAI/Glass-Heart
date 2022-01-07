
/*****************************************************************//**
 * @file   GameMain.cpp
 * @brief  このプロジェクトのメイン処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "GameMain.h"
#include "../Mode/ModeAmg.h"
#include "../Mode/ModeGame.h"
#include "../Mode/ModeTitle.h"
#include "../Mode/ModeTeamLogo.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"

using namespace GlassHeart;

/** 実体 */
GameMain _gameMain;

GameMain::GameMain() {
}

GameMain::~GameMain() {
}

//!< 初期化処理
bool GameMain::Initialize(HINSTANCE hInstance) {
    if (!base::Initialize(hInstance)) { return false; }

    //!< リソースサーバーの取得
    auto& res = GetResourceServer();

    //!< リソースのカレントフォルダ設定
    res.ChangeCurrentFile("resource");

    // マテリアルの自己発光色を暗い青色にする
#ifdef _DEBUG
    MATERIALPARAM material;
    material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
    material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
    material.Power = 20.0f;
    SetMaterialParam(material);
#endif

    //!< 使用する音のテーブル
    const AppFrame::ResourceServer::SoundMap usesound{
    {"damage", {"damage.wav", true}},
    {"bgm1", {"sublight.wav", false}},
    {"bgm2", {"stage1.mid", false}},
    };

    //!< 音を読み込み
    res.LoadSounds(usesound);

    //!< サウンドコンポーネントの取得
    auto& sm = GetSoundManager();
    sm.SetVolume("damage", 128);

#ifdef _DEBUG
    sm.SetMute(true);
#else
    sm.SetMute(false);
#endif // DEBUG

    //!< オブジェクトサーバーの生成
    _objServer = std::make_unique<GlassHeart::Object::ObjectServer>();
    //!< オブジェクトファクトリーの生成
    _objFactory = std::make_unique<GlassHeart::Object::ObjectFactory>(*this);

    //!< モードサーバーを生成し、AMGモードを登録
    _modeServer = std::make_unique<AppFrame::ModeServer>("Amg", std::make_shared<GlassHeart::Mode::ModeAmg>(*this));
    // チームロゴモードを登録
    _modeServer->Register("TeamLogo", std::make_shared<GlassHeart::Mode::ModeTeamLogo>(*this));
    // タイトルモードを登録
    _modeServer->Register("Title", std::make_shared<GlassHeart::Mode::ModeTitle>(*this));
    // インゲームモードを登録
    _modeServer->Register("InGame", std::make_shared<GlassHeart::Mode::ModeGame>(*this));

    return true;
}
//!< 解放処理
void GameMain::Terminate() {
    base::Terminate();
}
//!< 入力処理
void GameMain::Input() {
    base::Input();
    
}
//!< 更新処理
void GameMain::Process() {
    base::Process();
    
}
//!< 描画処理
void GameMain::Render() {
    base::Render();
    _modeServer->Render();
}
//!< メインループ
void GameMain::Run() {
    base::Run();
}