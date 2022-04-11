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
#include "../Mode/ModeLoading.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../Effect/EffectServer.h"
#include "../UI/UI.h"

 /** ���� */
GlassHeart::Application::GameMain _gameMain;
/** �R���X�g���N�^ */
GlassHeart::Application::GameMain::GameMain() {}
/** �f�X�g���N�^ */
GlassHeart::Application::GameMain::~GameMain() {}
/**  ���������� */
bool GlassHeart::Application::GameMain::Initialize(HINSTANCE hInstance) {
    if (!base::Initialize(hInstance)) { return false; }

    /** ���\�[�X�T�[�o�[�̎擾 */
    auto& res = GetResourceServer();
    /** ���\�[�X�̃J�����g�t�H���_�ݒ� */
    res.ChangeCurrentFile("resource");

#ifdef _DEBUG
    /** �}�e���A���̎��Ȕ����F���Â��F�ɂ��� */
    MATERIALPARAM material;
    material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
    material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
    material.Power = 20.0f;
    SetMaterialParam(material);
#endif
    /** �g�p���鉹�̃e�[�u�� */
    const AppFrame::ResourceServer::SoundMap usesound{
        // BGM
        {"bgm",     {"Sound/BGM/BGM01_Ver2.mp3",false}},
        {"titleBgm",  {"Sound/BGM/titleBGM.mp3",false}},
        // SE
        {"walk",    {"Sound/SE/SE_Walk.wav",true}},
        {"run",     {"Sound/SE/SE_Run.wav",true}},
        {"jump",    {"Sound/SE/SE_Jump.wav",true}},
        {"landing", {"Sound/SE/SE_Landing.wav",true}},
        {"death",   {"Sound/SE/SE_Death.wav",true}},
        {"select",  {"Sound/SE/SE_Select.wav",true}}
    };
    /** ����ǂݍ��� */
    res.LoadSounds(usesound);

    // �T�E���h�}�l�[�W���[�̎擾
    auto& sm = GetSoundManager();
    sm.SetVolume("bgm", 128);
    sm.SetVolume("titleBgm", 128);
    sm.SetVolume("walk", 128);
    sm.SetVolume("run", 255);
    sm.SetVolume("jump", 255);
    sm.SetVolume("landing", 255);
    sm.SetVolume("death", 128);
    sm.SetVolume("select", 255);

    sm.SetMute(false);

    // �I�u�W�F�N�g�T�[�o�[�̐���
    _objServer = std::make_unique<Object::ObjectServer>();
    // �I�u�W�F�N�g�t�@�N�g���[�̐���
    _objFactory = std::make_unique<Object::ObjectFactory>(*this);
    // ���[�U�[�C���^�[�t�F�[�X����
    _ui = std::make_unique<GlassHeart::UI::UI>(*this);

    // ���[�h�T�[�o�[�𐶐����AAMG���[�h��o�^
    _modeServer = std::make_unique<AppFrame::ModeServer>("Amg", std::make_shared<Mode::ModeAmg>(*this));
    // �`�[�����S���[�h��o�^
    _modeServer->Register("TeamLogo", std::make_shared<Mode::ModeTeamLogo>(*this));
    // �^�C�g�����[�h��o�^
    _modeServer->Register("Title", std::make_shared<Mode::ModeTitle>(*this));
    //�@���[�f�B���O���[�h��o�^
    _modeServer->Register("Loading", std::make_shared<Mode::ModeLoading>(*this));
    // �C���Q�[�����[�h��o�^
    _modeServer->Register("InGame", std::make_shared<Mode::ModeGame>(*this));
    // �Q�[���N���A���[�h��o�^
    _modeServer->Register("GameClear", std::make_shared<GlassHeart::Mode::ModeClear>(*this));

    return true;
}
/** ������� */
void GlassHeart::Application::GameMain::Terminate() {
    base::Terminate();
}
/** ���͏��� */
void GlassHeart::Application::GameMain::Input() {
    base::Input();
}
/** �X�V���� */
void GlassHeart::Application::GameMain::Process() {
    base::Process();
}
/** �`�揈�� */
void GlassHeart::Application::GameMain::Render() {
    base::Render();
}
/** ���C�����[�v */
void GlassHeart::Application::GameMain::Run() {
    base::Run();
}