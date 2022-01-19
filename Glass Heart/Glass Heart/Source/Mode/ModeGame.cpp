
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

using namespace GlassHeart::Mode;

//!< �R���X�g���N�^
ModeGame::ModeGame(GameMain& game) : ModeMain{ game } {
}
//!< ����������
void ModeGame::Init() {
    //!< �g�p���郂�f��
    AppFrame::ResourceServer::ModelMap usemap{
    {"Player",    "SDChar/SDChar.mv1"},
    {"SkySphere", "skysphere.mv1"},
    {"Ground",    "ground.mv1"},
    {"Terrain",   "Ground/Ground.mv1"},
    {"Test",      "Test/ST_test.mv1"},
    };
    //!< ���f���̓ǂݍ���
    GetResourceServer().LoadModels(usemap);
}
//!< ���������
void ModeGame::Enter() {
    // �t�@�N�g���̐����ƃN���G�C�^�[�̓o�^
    auto& of = GetObjectFactory();

    of.Register("Player", std::make_unique<Object::PlayerCreate>());
    of.Register("Stage", std::make_unique<Object::StageCreate>());

    auto player = of.Create("Player");

    auto& os = GetObjectServer();

    os.Register("Player", player->GetPosition());
    os.Add(std::move(player));

    auto stage = of.Create("Stage");
    os.Add(std::move(stage));

    Process();
}
//!< ���͏���
void ModeGame::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputStart()) {
        GetModeServer().GoToMode("Title");
    }
    GetObjectServer().Input(input);
}
//!< �X�V����
void ModeGame::Process() {
    GetObjectFactory().UpdateSpawn();
    GetObjectServer().Process();
}
//!< �`�揈��
void ModeGame::Render() {
    GetObjectServer().Render();
}
//!< �I������
void ModeGame::Exit() {
    //!< �I�u�W�F�N�g������
    GetObjectServer().AllClear();
    //!< ���\�[�X�̏���
    GetResourceServer().AllClear();
    //!< �N���G�C�^�[���폜
    GetObjectFactory().Clear();
}