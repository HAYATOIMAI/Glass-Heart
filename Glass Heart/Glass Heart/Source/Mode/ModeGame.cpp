
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
#include "../UI/UI.h"
#include <AppFrame.h>

using namespace GlassHeart;

/** �R���X�g���N�^ */
Mode::ModeGame::ModeGame(GameMain& game) : ModeMain{ game } {}
/** ���������� */
void Mode::ModeGame::Init() {}
/** ��������� */
void Mode::ModeGame::Enter() {
    // �t�@�N�g���̐����ƃN���G�C�^�[�̓o�^
    auto& of = GetObjectFactory();
    auto& os = GetObjectServer();

    of.Register("Player", std::make_unique<Object::PlayerCreate>());
    of.Register("Girl", std::make_unique<Object::GirlCreate>());
    of.Register("FollowCamera", std::make_unique<Object::FollowCameraCreate>());
    of.Register("Stage", std::make_unique<Object::StageCreate>());
    of.Register("CheckPoint", std::make_unique<Object::CheckPointCreate>());
    of.Register("GoalPoint", std::make_unique<Object::GoalPointCreate>());

    auto player = of.Create("Player");

    os.Register("Player", player->GetPosition());
    os.Add(std::move(player));

    auto girl = of.Create("Girl");
    os.Register("Girl", girl->GetPosition());
    os.Add(std::move(girl));

    auto followCamera = of.Create("FollowCamera");
    os.Register("FollowCamera", followCamera->GetPosition());
    os.Add(std::move(followCamera));

    auto stage = of.Create("Stage");
    os.Add(std::move(stage));

    auto checkPoint = of.Create("CheckPoint");
    os.Add(std::move(checkPoint));

    auto goalPoint = of.Create("GoalPoint");
    os.Add(std::move(goalPoint));

    auto& sm = GetSoundManager();

    sm.PlayLoop("bgm");

    _count = 60;
    _countSeconds = 150;

    auto& ui = GetUI();
    ui.Enter();

    Process();
}
/** ���͏��� */
void Mode::ModeGame::Input(AppFrame::InputManager& input) {
    GetObjectServer().Input(input);
}
/** �X�V���� */
void Mode::ModeGame::Process() {
    //GetObjectFactory().UpdateSpawn();
    GetObjectServer().Process();

    if (_count <= 60) {
        --_count;
    }
    if (_count == 0) {
        _count = 60;
        --_countSeconds;
    }
    if (_countSeconds < 0) {
        _countSeconds = 0;
    }
    if (_countSeconds == 0) {
        GetModeServer().GoToMode("GameClear");
    }
}
/** �`�揈�� */
void Mode::ModeGame::Render() {
    GetObjectServer().Render();
    GetUI().Render(300, 100, 80);

#ifdef _DEBUG
    auto x = 1000; auto y = 0; auto size = 32;
    auto white = GetColor(255, 255, 255);

    //DrawFormatString(x, y, white, "���݂̎���: %d ", _count); y += size;
    DrawFormatString(x, y, white, "���݂̎���: %d�b ", _countSeconds); y += size;
#endif // DEBUG
}
/** �I������ */
void Mode::ModeGame::Exit() {

    auto& sm = GetSoundManager();
    sm.StopSound("bgm");
    sm.StopSound("run");

    //// �I�u�W�F�N�g������
    //GetObjectServer().AllClear();
    //// ���\�[�X�̏���
    //GetResourceServer().AllClear();
    //// �N���G�C�^�[���폜
    //GetObjectFactory().Clear();
}