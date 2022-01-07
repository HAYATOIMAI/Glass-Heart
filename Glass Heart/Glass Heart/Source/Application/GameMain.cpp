
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
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"

using namespace GlassHeart;

/** ���� */
GameMain _gameMain;

GameMain::GameMain() {
}

GameMain::~GameMain() {
}

//!< ����������
bool GameMain::Initialize(HINSTANCE hInstance) {
    if (!base::Initialize(hInstance)) { return false; }

    //!< ���\�[�X�T�[�o�[�̎擾
    auto& res = GetResourceServer();

    //!< ���\�[�X�̃J�����g�t�H���_�ݒ�
    res.ChangeCurrentFile("resource");

    // �}�e���A���̎��Ȕ����F���Â��F�ɂ���
#ifdef _DEBUG
    MATERIALPARAM material;
    material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
    material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
    material.Power = 20.0f;
    SetMaterialParam(material);
#endif

    //!< �g�p���鉹�̃e�[�u��
    const AppFrame::ResourceServer::SoundMap usesound{
    {"damage", {"damage.wav", true}},
    {"bgm1", {"sublight.wav", false}},
    {"bgm2", {"stage1.mid", false}},
    };

    //!< ����ǂݍ���
    res.LoadSounds(usesound);

    //!< �T�E���h�R���|�[�l���g�̎擾
    auto& sm = GetSoundManager();
    sm.SetVolume("damage", 128);

#ifdef _DEBUG
    sm.SetMute(true);
#else
    sm.SetMute(false);
#endif // DEBUG

    //!< �I�u�W�F�N�g�T�[�o�[�̐���
    _objServer = std::make_unique<GlassHeart::Object::ObjectServer>();
    //!< �I�u�W�F�N�g�t�@�N�g���[�̐���
    _objFactory = std::make_unique<GlassHeart::Object::ObjectFactory>(*this);

    //!< ���[�h�T�[�o�[�𐶐����AAMG���[�h��o�^
    _modeServer = std::make_unique<AppFrame::ModeServer>("Amg", std::make_shared<GlassHeart::Mode::ModeAmg>(*this));
    // �`�[�����S���[�h��o�^
    _modeServer->Register("TeamLogo", std::make_shared<GlassHeart::Mode::ModeTeamLogo>(*this));
    // �^�C�g�����[�h��o�^
    _modeServer->Register("Title", std::make_shared<GlassHeart::Mode::ModeTitle>(*this));
    // �C���Q�[�����[�h��o�^
    _modeServer->Register("InGame", std::make_shared<GlassHeart::Mode::ModeGame>(*this));

    return true;
}
//!< �������
void GameMain::Terminate() {
    base::Terminate();
}
//!< ���͏���
void GameMain::Input() {
    base::Input();
    
}
//!< �X�V����
void GameMain::Process() {
    base::Process();
    
}
//!< �`�揈��
void GameMain::Render() {
    base::Render();
    _modeServer->Render();
}
//!< ���C�����[�v
void GameMain::Run() {
    base::Run();
}