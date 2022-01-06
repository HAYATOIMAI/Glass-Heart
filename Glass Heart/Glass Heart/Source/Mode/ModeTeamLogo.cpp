
/*****************************************************************//**
 * @file   ModeTeamLogo.cpp
 * @brief  �`�[�����S��ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTeamLogo.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Mode;

//!< �R���X�g���N�^
ModeTeamLogo::ModeTeamLogo(GameMain& game) : ModeMain{ game }
{
}
void ModeTeamLogo::Init() {
	//!< �g�p����摜�̃e�[�u��
	const AppFrame::ResourceServer::GraphMap useGraph{
	{"TitleBg",          {"TitleBg.png",          1, 1, 1920, 1080}} };

	//!< ���\�[�X�T�[�o�[���擾
	auto& res = GetResourceServer();

	//!< �摜�̓ǂݍ���
	res.LoadGraphics(useGraph);

	//!< �摜�̃n���h���̎擾
	_titleBgHandle = res.GetGraph("TitleBg");

	//!< �T�E���h�}�l�[�W���[���擾
	auto& sm = GetSoundManager();
	sm.PlayLoop("bgm1");
	sm.SetVolume("bgm1", 50);
}
//!< ���������
void ModeTeamLogo::Enter() {
}
//!< ���͏���
void ModeTeamLogo::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputButtonB()) {
		GetModeServer().GoToMode("Title");
	}
}
//!< �X�V����
void ModeTeamLogo::Process() {
	//_alpha = (_alpha + 8) % 255;
}
//!< �`�揈��
void ModeTeamLogo::Render() {
	DrawGraph(0, 0, _titleBgHandle, FALSE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
}