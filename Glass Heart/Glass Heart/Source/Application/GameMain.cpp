
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
#include "../Mode/ModeClear.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"

using namespace GlassHeart;

/** 実体 */
GameMain _gameMain;
/** コンストラクタ */
GameMain::GameMain() {}
/** デストラクタ */
GameMain::~GameMain() {}
/**  初期化処理 */
bool GameMain::Initialize(HINSTANCE hInstance) {
    if (!base::Initialize(hInstance)) { return false; }

    /** リソースサーバーの取得 */
    auto& res = GetResourceServer();

    /** リソースのカレントフォルダ設定 */
    res.ChangeCurrentFile("resource");
     
    /** マテリアルの自己発光色を暗い青色にする */
#ifdef _DEBUG
    MATERIALPARAM material;
    material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
    material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
    material.Power = 20.0f;
    SetMaterialParam(material);
#endif
    /** 使用する音のテーブル */
    const AppFrame::ResourceServer::SoundMap usesound {
    {"cancel",  {"Sound/SE/SE_Cancel.mp3",true}},
    {"cursor",  {"Sound/SE/SE_Cursor.mp3",true}},
    {"death",   {"Sound/SE/SE_Death.mp3",true}},
    {"jump",    {"Sound/SE/SE_Jump.mp3",true}},
    {"landing", {"Sound/SE/SE_Landing.mp3",true}},
    {"pick",    {"Sound/SE/SE_Pick.mp3",true}},
    {"run",     {"Sound/SE/SE_Run.mp3",true}},
    {"select",  {"Sound/SE/SE_Select.mp3",true}},
    {"walk",    {"Sound/SE/SE_Walk.mp3",true}},
    {"bgm", {"Sound/BGM/BGM01_Ver2.mp3, ", true}}
    };
    /** 音を読み込み */
    res.LoadSounds(usesound);

    // サウンドコンポーネントの取得
    auto& sm = GetSoundManager();
    sm.SetVolume("bgm", 128);

    sm.SetMute(false);

    // オブジェクトサーバーの生成
    _objServer = std::make_unique<Object::ObjectServer>();
    // オブジェクトファクトリーの生成
    _objFactory = std::make_unique<Object::ObjectFactory>(*this);

    // モードサーバーを生成し、AMGモードを登録
    _modeServer = std::make_unique<AppFrame::ModeServer>("Amg", std::make_shared<Mode::ModeAmg>(*this));
    // チームロゴモードを登録
    _modeServer->Register("TeamLogo", std::make_shared<Mode::ModeTeamLogo>(*this));
    // タイトルモードを登録
    _modeServer->Register("Title", std::make_shared<Mode::ModeTitle>(*this));
    // インゲームモードを登録
    _modeServer->Register("InGame", std::make_shared<Mode::ModeGame>(*this));
    // ゲームクリアモードを登録
    _modeServer->Register("GameClear", std::make_shared<GlassHeart::Mode::ModeClear>(*this));

//#ifdef _DEBUG
//    _modeServer = std::make_unique<AppFrame::ModeServer>("InGame", std::make_shared<Mode::ModeGame>(*this));
//    // タイトルモードを登録
//    _modeServer->Register("Title", std::make_shared<Mode::ModeTitle>(*this));
//    // ゲームクリアモードを登録
//    _modeServer->Register("GameClear", std::make_shared<GlassHeart::Mode::ModeClear>(*this));
//#endif // _DEBUG

    return true;
}
/** 解放処理 */
void GameMain::Terminate() {
    base::Terminate();
}
/** 入力処理 */
void GameMain::Input() {
    base::Input();
}
/** 更新処理 */
void GameMain::Process() {
    base::Process();
}
/** 描画処理 */
void GameMain::Render() {
    base::Render();
}
/** メインループ */
void GameMain::Run() {
    base::Run();
}