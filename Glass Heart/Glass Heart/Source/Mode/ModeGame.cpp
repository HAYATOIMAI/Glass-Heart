
/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  �Q�[�����N���X�̏���
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

//!< �R���X�g���N�^
Mode::ModeGame::ModeGame(GameMain& game) : ModeMain{ game } {}
//!< ����������
void Mode::ModeGame::Init() {
    //!< �g�p���郂�f��
    AppFrame::ResourceServer::ModelMap usemap{
    {"Player",    "Boy/PC2_motion.mv1"},
    //{"SkySphere", "skysphere.mv1"},
    /*{"Ground",    "ground.mv1"},
    {"Terrain",   "Ground/Ground.mv1"},
    {"Test",      "Test/ST_test.mv1"},*/
    {"Stage", "Test/Zenhan.mv1"},
    };
    //!< ���f���̓ǂݍ���
    GetResourceServer().LoadModels(usemap);
}
//!< ���������
void Mode::ModeGame::Enter() {
    // �t�@�N�g���̐����ƃN���G�C�^�[�̓o�^
    auto& of = GetObjectFactory();

    of.Register("Player", std::make_unique<Object::PlayerCreate>());
    of.Register("FollowCamera", std::make_unique<Object::FollowCameraCreate>());
    of.Register("Stage", std::make_unique<Object::StageCreate>());
    of.Register("CheckPoint", std::make_unique<Object::CheckPointCreate>());

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

    Process();
}
//!< ���͏���
void Mode::ModeGame::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputStart()) {
        GetModeServer().GoToMode("Title");
    }
    GetObjectServer().Input(input);
}
//!< �X�V����
void Mode::ModeGame::Process() {
    GetObjectFactory().UpdateSpawn();
    GetObjectServer().Process();
}
//!< �`�揈��
void Mode::ModeGame::Render() {
    GetObjectServer().Render();
}
//!< �I������
void Mode::ModeGame::Exit() {
    //!< �I�u�W�F�N�g������
    GetObjectServer().AllClear();
    //!< ���\�[�X�̏���
    GetResourceServer().AllClear();
    //!< �N���G�C�^�[���폜
    GetObjectFactory().Clear();
}