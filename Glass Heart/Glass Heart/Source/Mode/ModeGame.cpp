
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

int Mode::ModeMain::_count;
int Mode::ModeMain::_countSeconds;
int Mode::ModeMain::_countMinutes;

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
    of.Register("GoalPoint", std::make_unique<Object::GoalPointCreate>());

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

    _count = 0;
    _countSeconds = 0;
    _countMinutes = 0;

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

    if (_count < 60) {
        ++_count;
    }
    if (_count == 60) {
        _count = 0;
        ++_countSeconds;
    }
    if (_countSeconds == 60) {
        _countSeconds = 0;
        ++_countMinutes;
    }
}
//!< �`�揈��
void Mode::ModeGame::Render() {
    GetObjectServer().Render();

#ifdef _DEBUG
    auto x = 1000; auto y = 0; auto size = 32;
    auto white = GetColor(255, 255, 255);

    // ���݂̎���(��)
    DrawFormatString(x, y, white, "���݂̎���: %d ", _count); y += size;
    DrawFormatString(x, y, white, "���݂̎���: %d�b ", _countSeconds); y += size;
    DrawFormatString(x, y, white, "���݂̎���: %d�� ", _countMinutes); y += size;
#endif // DEBUG
}
//!< �I������
void Mode::ModeGame::Exit() {
    ////!< �I�u�W�F�N�g������
    //GetObjectServer().AllClear();
    ////!< ���\�[�X�̏���
    //GetResourceServer().AllClear();
    ////!< �N���G�C�^�[���폜
    //GetObjectFactory().Clear();
}