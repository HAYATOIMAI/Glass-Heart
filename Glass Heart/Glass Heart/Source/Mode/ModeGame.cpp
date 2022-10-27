/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  �Q�[�����N���X�̏���
 *
 * @author Hayato Imai, Yoshihiro Takahashi, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/GameMain.h"
#include "../Camera/CameraManager.h"
#include "../UI/UI.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../Object/PlayerCreate.h"
#include "../Object/GirlCreate.h"
#include "../Object/StageCreate.h"
#include "../Object/FollowCameraCreate.h"
#include "../Object/CheckPointCreate.h"
#include "../Object/GoalPointCreate.h"

namespace {
  constexpr VECTOR TeamLogoPosition      = { 22500.0f, 12600.0f, 200.0f };
  constexpr VECTOR TitleLogoPosition     = { 25450.0f, 12400.0f, 200.0f };
  constexpr	std::int_fast16_t Timer      = 60;
  constexpr std::int_fast16_t TimeLimit  = 350;
  constexpr std::int_fast32_t UiPosition = 100;
  constexpr auto RenderingExrate         = 0.05;
  constexpr auto MiddlePos               = 0.5f;
  constexpr auto NotRotate               = 0.0f;
  constexpr auto TeamLogoSize            = 800.0f;
  constexpr auto TitleSize               = 1200.0f;
  constexpr auto TeamLogo                = "TeamLogo";
  constexpr auto TitleLogo               = "TitleLogo";
  constexpr auto Bgm                     = "bgm";
  constexpr auto Run                     = "run";
  constexpr auto Death                   = "Death";
  constexpr auto PlayerCreator           = "Player";
  constexpr auto GirlCreator             = "Girl";
  constexpr auto FollowCameraCreator     = "FollowCamera";
  constexpr auto StageCreator            = "Stage";
  constexpr auto CheckPointCreator       = "CheckPoint";
  constexpr auto GoalPointCreator        = "GoalPoint";
  constexpr auto GameClear               = "GameClear";
}

/** �R���X�g���N�^ */
GlassHeart::Mode::ModeGame::ModeGame(Application::GameMain& game) : ModeMain{ game } {}
/** ���������� */
void GlassHeart::Mode::ModeGame::Init() {
  // ���\�[�X�T�[�o�[���擾
  auto& res = GetResourceServer();
  //���\�[�X�}�l�[�W���[����o�^�����摜���擾
  _teamLogo  = res.GetGraph(TeamLogo);
  _titleLogo = res.GetGraph(TitleLogo);
}
/** ��������� */
void GlassHeart::Mode::ModeGame::Enter() {
  // �I�u�W�F�N�g�𐶐����A�Ǘ�����}�l�[�W���[�ɓo�^����
  ObjectRegister();
  // BGM�����[�v�Đ�
  auto& sm = GetSoundManager();
  sm.PlayLoop(Bgm);
  // �^�C�}�[�̕b�����Z�b�g
  _count = Timer;
  _countSeconds = TimeLimit;
  // UI�̓�����������s
  auto& ui = GetUI();
  ui.Enter();
  // ���\�[�X�}�l�[�W���[����o�^�����摜���擾
  _deathDrawHundle = _game.GetResourceServer().GetGraph(Death);
  // �X�V�����Ăяo��
  Process();
}
/** ���͏��� */
void GlassHeart::Mode::ModeGame::Input(AppFrame::Input::InputManager& input) {
  // �I�u�W�F�N�g�̓��͏���
  GetObjectServer().Input(input);
}
/** �X�V���� */
void GlassHeart::Mode::ModeGame::Process() {
  // �I�u�W�F�N�g�̍X�V����
  GetObjectServer().Process();
  // �^�C�}�[�o�ߏ���
  TimerProcess();
}
/** �`�揈�� */
void GlassHeart::Mode::ModeGame::Render() {
  // �I�u�W�F�N�g��`��
  GetObjectServer().Render();
  // UI��`��
  UiRenderring();
  // �`�[�����S�ƃ^�C�g���摜�`��
  DrawBillboard3D(TeamLogoPosition, MiddlePos, MiddlePos, TeamLogoSize, NotRotate, _teamLogo, TRUE);
  DrawBillboard3D(TitleLogoPosition, MiddlePos, MiddlePos, TitleSize, NotRotate, _titleLogo, TRUE);
  // �f�o�b�O�p�^�C�}�[�b���\��
#ifdef _DEBUG
  auto x = 1000; auto y = 0; auto size = 32;
  auto white = GetColor(255, 255, 255);

  //DrawFormatString(x, y, white, "���݂̎���: %d ", _count); y += size;
  DrawFormatString(x, y, white, "���݂̎���: %d�b ", _countSeconds); y += size;
#endif // DEBUG
}
/** �I������ */
void GlassHeart::Mode::ModeGame::Exit() {
  // BGM��SE���~
  auto& sm = GetSoundManager();
  sm.StopSound(Bgm);
  sm.StopSound(Run);
}
/** �I�u�W�F�N�g�𐶐��A�}�l�[�W���[�ɓo�^���� */
void GlassHeart::Mode::ModeGame::ObjectRegister() {
  // �t�@�N�g���[�̐���
  auto& of = GetObjectFactory();
  auto& os = GetObjectServer();
  // �N���G�C�^�[�̓o�^
  of.Register(PlayerCreator,       std::make_unique<Object::PlayerCreate>());
  of.Register(GirlCreator,         std::make_unique<Object::GirlCreate>());
  of.Register(FollowCameraCreator, std::make_unique<Object::FollowCameraCreate>());
  of.Register(StageCreator,        std::make_unique<Object::StageCreate>());
  of.Register(CheckPointCreator,   std::make_unique<Object::CheckPointCreate>());
  of.Register(GoalPointCreator,    std::make_unique<Object::GoalPointCreate>());

  auto player = of.Create(PlayerCreator);
  // �I�u�W�F�N�g�T�[�o�[�ɓo�^
  os.Register(PlayerCreator, player->GetPosition());
  os.Add(std::move(player));

  auto girl = of.Create(GirlCreator);
  os.Register(GirlCreator, girl->GetPosition());
  os.Add(std::move(girl));

  auto followCamera = of.Create(FollowCameraCreator);
  os.Register(FollowCameraCreator, followCamera->GetPosition());
  os.Add(std::move(followCamera));

  auto stage = of.Create(StageCreator);
  os.Add(std::move(stage));

  auto checkPoint = of.Create(CheckPointCreator);
  os.Add(std::move(checkPoint));

  auto goalPoint = of.Create(GoalPointCreator);
  os.Add(std::move(goalPoint));
}

void GlassHeart::Mode::ModeGame::TimerProcess() {
  // �v���C���[�̎��S��Ԃł͂Ȃ����̂݃^�C�}�[����
  for (auto& itr : GetObjectServer().GetObjectLists()) {
    if (itr->GetObjectType() == Object::ObjectBase::ObjectType::Player) {
      if (itr->GetDeadFlag() == false) {
        // �^�C�}�[����
        if (_count <= Timer) {
          --_count;
        }
        if (_count == 0) {
          _count = Timer;
          --_countSeconds;
        }
        if (_countSeconds < 0) {
          _countSeconds = 0;
        }
        // �^�C�}�[���[���ɂȂ�����N���A���[�h��
        if (_countSeconds == 0) {
          GetModeServer().GoToMode(GameClear);
        }
        GetUI().Process(_countSeconds);
      }
    }
  }
}

void GlassHeart::Mode::ModeGame::UiRenderring() {
  // UI��`��
  GetUI().Render(UiPosition, UiPosition, RenderingExrate);
  // �b���`��
  GetUI().NumberRender(400, 100, 80, 1.0);
  for (auto& itr : GetObjectServer().GetObjectLists()) {
    if (itr->GetObjectType() == Object::ObjectBase::ObjectType::Player) {
      if (itr->GetDeadFlag()) {
        DrawRotaGraph(960, 540, 1.0, 0.0, _deathDrawHundle, TRUE);
      }
    }
  }
}
