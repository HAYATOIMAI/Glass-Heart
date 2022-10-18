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
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../UI/UI.h"
#include <AppFrame.h>

namespace {
	constexpr	std::int_fast8_t Timer = 60;
	constexpr std::int_fast16_t TimeLimit = 350;
}

/** �R���X�g���N�^ */
GlassHeart::Mode::ModeGame::ModeGame(Application::GameMain& game) : ModeMain{ game } {}
/** ���������� */
void GlassHeart::Mode::ModeGame::Init() {
	// ���\�[�X�T�[�o�[���擾
	auto& res = GetResourceServer();
	// �摜�̃n���h���̎擾
	_teamLogo = res.GetGraph("TeamLogo");
	_titleLogo = res.GetGraph("TitleLogo");
}
/** ��������� */
void GlassHeart::Mode::ModeGame::Enter() {
	// �t�@�N�g���[�̐���
	auto& of = GetObjectFactory();
	auto& os = GetObjectServer();
	// �N���G�C�^�[�̓o�^
	of.Register("Player", std::make_unique<GlassHeart::Object::PlayerCreate>());
	of.Register("Girl", std::make_unique<GlassHeart::Object::GirlCreate>());
	of.Register("FollowCamera", std::make_unique<GlassHeart::Object::FollowCameraCreate>());
	of.Register("Stage", std::make_unique<GlassHeart::Object::StageCreate>());
	of.Register("CheckPoint", std::make_unique<GlassHeart::Object::CheckPointCreate>());
	of.Register("GoalPoint", std::make_unique<GlassHeart::Object::GoalPointCreate>());

	auto player = of.Create("Player");
	// �I�u�W�F�N�g�T�[�o�[�ɓo�^
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
	// BGM�����[�v�Đ�
	auto& sm = GetSoundManager();
	sm.PlayLoop("bgm");
	// �^�C�}�[�̕b�����Z�b�g
	_count = Timer;
	_countSeconds = TimeLimit;
	// UI�̓�����������s
	auto& ui = GetUI();
	ui.Enter();
	// ���\�[�X�}�l�[�W���[����o�^�����摜���擾
	_deathDrawHundle = _game.GetResourceServer().GetGraph("Death");

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
					GetModeServer().GoToMode("GameClear");
				}
				GetUI().Process(_countSeconds);
			}
		}
	}
}
/** �`�揈�� */
void GlassHeart::Mode::ModeGame::Render() {
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
	sm.StopSound("bgm");
	sm.StopSound("run");
}