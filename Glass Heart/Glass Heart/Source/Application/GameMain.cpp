
/*****************************************************************//**
 * @file   GameMain.cpp
 * @brief  ���̃v���W�F�N�g�̃��C������
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

/** ���� */
GameMain _gameMain;
/** �R���X�g���N�^ */
GameMain::GameMain() {}
/** �f�X�g���N�^ */
GameMain::~GameMain() {}
/**  ���������� */
bool GameMain::Initialize(HINSTANCE hInstance) {
    if (!base::Initialize(hInstance)) { return false; }

    /** ���\�[�X�T�[�o�[�̎擾 */
    auto& res = GetResourceServer();

    /** ���\�[�X�̃J�����g�t�H���_�ݒ� */
    res.ChangeCurrentFile("resource");
     
    /** �}�e���A���̎��Ȕ����F���Â��F�ɂ��� */
#ifdef _DEBUG
    MATERIALPARAM material;
    material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
    material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
    material.Power = 20.0f;
    SetMaterialParam(material);
#endif
    /** �g�p���鉹�̃e�[�u�� */
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
    /** ����ǂݍ��� */
    res.LoadSounds(usesound);

    // �T�E���h�R���|�[�l���g�̎擾
    auto& sm = GetSoundManager();
    sm.SetVolume("bgm", 128);

    sm.SetMute(false);

    // �I�u�W�F�N�g�T�[�o�[�̐���
    _objServer = std::make_unique<Object::ObjectServer>();
    // �I�u�W�F�N�g�t�@�N�g���[�̐���
    _objFactory = std::make_unique<Object::ObjectFactory>(*this);

    // ���[�h�T�[�o�[�𐶐����AAMG���[�h��o�^
    _modeServer = std::make_unique<AppFrame::ModeServer>("Amg", std::make_shared<Mode::ModeAmg>(*this));
    // �`�[�����S���[�h��o�^
    _modeServer->Register("TeamLogo", std::make_shared<Mode::ModeTeamLogo>(*this));
    // �^�C�g�����[�h��o�^
    _modeServer->Register("Title", std::make_shared<Mode::ModeTitle>(*this));
    // �C���Q�[�����[�h��o�^
    _modeServer->Register("InGame", std::make_shared<Mode::ModeGame>(*this));
    // �Q�[���N���A���[�h��o�^
    _modeServer->Register("GameClear", std::make_shared<GlassHeart::Mode::ModeClear>(*this));

//#ifdef _DEBUG
//    _modeServer = std::make_unique<AppFrame::ModeServer>("InGame", std::make_shared<Mode::ModeGame>(*this));
//    // �^�C�g�����[�h��o�^
//    _modeServer->Register("Title", std::make_shared<Mode::ModeTitle>(*this));
//    // �Q�[���N���A���[�h��o�^
//    _modeServer->Register("GameClear", std::make_shared<GlassHeart::Mode::ModeClear>(*this));
//#endif // _DEBUG

    return true;
}
/** ������� */
void GameMain::Terminate() {
    base::Terminate();
}
/** ���͏��� */
void GameMain::Input() {
    base::Input();
}
/** �X�V���� */
void GameMain::Process() {
    base::Process();
}
/** �`�揈�� */
void GameMain::Render() {
    base::Render();
}
/** ���C�����[�v */
void GameMain::Run() {
    base::Run();
}