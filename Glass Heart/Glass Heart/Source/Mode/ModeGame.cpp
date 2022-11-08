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
  constexpr VECTOR TeamLogoPosition = { 22500.0f, 12600.0f, 200.0f };   //!< �`�[�����S�摜�̕`��ʒu
  constexpr VECTOR TitleLogoPosition = { 25450.0f, 12400.0f, 200.0f };  //!< �^�C�g�����S�摜�̕`��ʒu
  constexpr	int_fast16_t Timer = 60;                                    //!< �o�߂��鎞��
  constexpr int_fast16_t TimeLimit = 350;                               //!< ��������
  constexpr int_fast32_t UiPosition  = 100;                             //!< UI�`��ʒu
  constexpr int_fast32_t TimerNumberX = 400;                            //!< �^�C�}�[������X���`��ʒu
  constexpr int_fast32_t TimerNumberY = 100;                            //!< �^�C�}�[������Y���`��ʒu
  constexpr int_fast32_t NumberInterval = 80;                           //!< �^�C�}�[�����̕`��Ԋu
  constexpr int_fast32_t DeathEffectPositionX = 960;                    //!< ���S���ɕ\������摜X���ʒu
  constexpr int_fast32_t DeathEffectPositionY = 540;                    //!< ���S���ɕ\������摜Y���ʒu
  constexpr auto EffectExrate = 1.0;                                    //!< ���S���ɕ\������摜�̊g�嗦
  constexpr auto TimerExrate = 1.0;                                     //!< �^�C�}�[�����̊g�嗦
  constexpr auto RenderingExrate = 0.05;                                //!< �`��Ԋu
  constexpr auto MiddlePos = 0.5f;                                      //!< �`�悷��摜�̒��S���W
  constexpr auto NotRotate = 0.0f;                                      //!< �`�悷��摜�̉�]������p�x
  constexpr auto TeamLogoSize = 800.0f;                                 //!< �摜�T�C�Y
  constexpr auto TitleSize = 1200.0f;                                   //!< �摜�T�C�Y
  constexpr auto TeamLogo = "TeamLogo";                                 //!< ���\�[�X�}�l�[�W���[����Ăяo���t�@�C����
  constexpr auto TitleLogo = "TitleLogo";                               //!< ���\�[�X�}�l�[�W���[����Ăяo���t�@�C����
  constexpr auto Run = "run";                                           //!< ��~����T�E���h
  constexpr auto Bgm = "bgm";                                           //!< ��~����T�E���h
  constexpr auto Death = "Death";                                       //!< ���\�[�X�}�l�[�W���[����Ăяo���t�@�C����
  constexpr auto PlayerCreator = "Player";                              //!< ��������I�u�W�F�N�g�̖��O
  constexpr auto GirlCreator = "Girl";                                  //!< ��������I�u�W�F�N�g�̖��O
  constexpr auto FollowCameraCreator = "FollowCamera";                  //!< ��������I�u�W�F�N�g�̖��O
  constexpr auto StageCreator = "Stage";                                //!< ��������I�u�W�F�N�g�̖��O
  constexpr auto CheckPointCreator = "CheckPoint";                      //!< ��������I�u�W�F�N�g�̖��O
  constexpr auto GoalPointCreator = "GoalPoint";                        //!< ��������I�u�W�F�N�g�̖��O
  constexpr auto GameClear = "GameClear";                               //!< �J�ڂ��郂�[�h�̕�����
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
/** �^�C�}�[�o�ߏ��� */
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
/** UI���w��ʒu�ɕ`�� */
void GlassHeart::Mode::ModeGame::UiRenderring() {
  // UI��`��
  GetUI().Render(UiPosition, UiPosition, RenderingExrate);
  // �b���`��
  GetUI().NumberRender(TimerNumberX, TimerNumberY, NumberInterval, TimerExrate);
  for (auto& itr : GetObjectServer().GetObjectLists()) {
    if (itr->GetObjectType() == Object::ObjectBase::ObjectType::Player) {
      if (itr->GetDeadFlag()) {
        DrawRotaGraph(DeathEffectPositionX, DeathEffectPositionY, EffectExrate, 0.0, _deathDrawHundle, TRUE);
      }
    }
  }
}