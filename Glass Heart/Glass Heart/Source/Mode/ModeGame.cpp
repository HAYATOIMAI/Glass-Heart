
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
void Mode::ModeGame::Init() {
    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();
    // �摜�̃n���h���̎擾
    _teamLogo = res.GetGraph("TeamLogo");
    _titleLogo = res.GetGraph("TitleLogo");
}
/** ��������� */
void Mode::ModeGame::Enter() {
    // �t�@�N�g���[�̐����ƃN���G�C�^�[�̓o�^
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
    _countSeconds = 350;

    auto& ui = GetUI();
    ui.Enter();
    
    _deathDrawHundle = _game.GetResourceServer().GetGraph("Death");

    Process();
}
/** ���͏��� */
void Mode::ModeGame::Input(AppFrame::InputManager& input) {
    // �I�u�W�F�N�g�̓��͏���
    GetObjectServer().Input(input);
}
/** �X�V���� */
void Mode::ModeGame::Process() {
    // �I�u�W�F�N�g�̍X�V����
    GetObjectServer().Process();
   // �^�C�}�[����
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
    GetUI().Process(_countSeconds);
}
/** �`�揈�� */
void Mode::ModeGame::Render() {
    // �I�u�W�F�N�g��`��
    GetObjectServer().Render();
    // UI��`��
    GetUI().Render(100, 100, 0.05);
    // �b���`��
    GetUI().NumberRender(400, 100, 80, 1.0);
    for (auto& itr : GetObjectServer().GetObjectLists()) {
        if (itr->GetObjectType() == Object::ObjectBase::ObjectType::Player) {
            if (itr->GetDeadFlag()) {
                DrawRotaGraph(960, 540, 1.0, 0.0, _deathDrawHundle, TRUE);
            }
        }
    }
    // �`�[�����S�ƃ^�C�g���摜�`��
    DrawBillboard3D(VGet(22500.0f, 12600.0f, 200.0f), 0.5f, 0.5f, 800.0f, 0.0f, _teamLogo, TRUE);
    DrawBillboard3D(VGet(25450.0f, 12400.0f, 200.0f), 0.5f, 0.5f, 1200.0f, 0.0f, _titleLogo, TRUE);
#ifdef _DEBUG
    auto x = 1000; auto y = 0; auto size = 32;
    auto white = GetColor(255, 255, 255);

    //DrawFormatString(x, y, white, "���݂̎���: %d ", _count); y += size;
    DrawFormatString(x, y, white, "���݂̎���: %d�b ", _countSeconds); y += size;
#endif // DEBUG
}
/** �I������ */
void Mode::ModeGame::Exit() {
    // BGM��SE���~
    auto& sm = GetSoundManager();
    sm.StopSound("bgm");
    sm.StopSound("run");
}