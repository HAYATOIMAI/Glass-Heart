/*****************************************************************//**
 * @file   ModeAmg.cpp
 * @brief  AMG��ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeAmg.h"
#include "../Application/GameMain.h"

 /** �R���X�g���N�^ */
GlassHeart::Mode::ModeAmg::ModeAmg(Application::GameMain& game) : ModeMain{ game } {}
/** ���������� */
void GlassHeart::Mode::ModeAmg::Init() {
	// �g�p����摜�̃e�[�u��
	const AppFrame::Resource::ResourceServer::GraphMap useGraph{
	{"AMGBg",  {"Amg/AMG.jpg",  1, 1, 1920, 1080} },
	{"0",      {"Numberplate/0.png", 1, 1, 75, 120} },
	{"1",      {"Numberplate/1.png", 1, 1, 75, 120} },
	{"2",      {"Numberplate/2.png", 1, 1, 75, 120} },
	{"3",      {"Numberplate/3.png", 1, 1, 75, 120} },
	{"4",      {"Numberplate/4.png", 1, 1, 75, 120} },
	{"5",      {"Numberplate/5.png", 1, 1, 75, 120} },
	{"6",      {"Numberplate/6.png", 1, 1, 75, 120} },
	{"7",      {"Numberplate/7.png", 1, 1, 75, 120} },
	{"8",      {"Numberplate/8.png", 1, 1, 75, 120} },
	{"9",      {"Numberplate/9.png", 1, 1, 75, 120} },
	{"timer",  {"Numberplate/Timer.png", 1, 1, 2377, 2361}},
	{"Death",  {"BackGround/break.png", 1, 1, 1920, 1080}}
	};

	auto& res = GetResourceServer();
	// �摜�̓ǂݍ���
	res.LoadGraphics(useGraph);
	// ���\�[�X�}�l�[�W���[����o�^�����摜���擾
	_titleBgHandle = res.GetGraph("AMGBg");

	// �g�p���郂�f���̃e�[�u��
	AppFrame::Resource::ResourceServer::ModelMap useMap{
	{"Stage", "Stage/Stage04.mv1"},
	{"BackGround", "BackGround/bg.mv1"},
	{"Player", "Boy/PC2_motion.mv1"},
	{"Girl", "Girl/Girl.mv1"},
	};
	// ���f���̓ǂݍ���
	GetResourceServer().LoadModels(useMap);
	// �񓯊��ǂݍ��݊J�n
	SetUseASyncLoadFlag(TRUE);
	_fadeCount = 30;
}
/** ��������� */
void GlassHeart::Mode::ModeAmg::Enter() {}
/** ���͏��� */
void GlassHeart::Mode::ModeAmg::Input(AppFrame::Input::InputManager& input) {
	if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
		GetModeServer().GoToMode("TeamLogo");
	}
}
/** �X�V���� */
void GlassHeart::Mode::ModeAmg::Process() {
	if (_fadeCount > 0) {
		--_fadeCount;
	}
}
/** �`�揈�� */
void GlassHeart::Mode::ModeAmg::Render() {
	DrawGraph(0, 0, _titleBgHandle, FALSE);
}