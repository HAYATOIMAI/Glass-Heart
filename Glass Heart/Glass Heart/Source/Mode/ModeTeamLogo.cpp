
/*****************************************************************//**
 * @file   ModeTeamLogo.cpp
 * @brief  �`�[�����S��ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTeamLogo.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

/** �R���X�g���N�^ */
Mode::ModeTeamLogo::ModeTeamLogo(GameMain& game) : Mode::ModeMain{ game }{}
/** ���������� */
void Mode::ModeTeamLogo::Init() {
    // �g�p����摜�̃e�[�u��
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"TitleBg",          {"TeamLogo/kane.png",          1, 1, 1920, 1080}} };
    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();
    // �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);
    // �摜�̃n���h���̎擾
    _titleBgHandle = res.GetGraph("TitleBg");
}
/** ��������� */
void Mode::ModeTeamLogo::Enter() {
}
/** ���͏��� */
void Mode::ModeTeamLogo::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("Title");
    }
}
/** �X�V���� */
void Mode::ModeTeamLogo::Process() {
    //_alpha = (_alpha + 8) % 255;
}
/** �`�揈�� */
void Mode::ModeTeamLogo::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
}