/*****************************************************************//**
 * @file   ModeTeamLogo.cpp
 * @brief  �`�[�����S��ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTeamLogo.h"
#include "../Application/GameMain.h"

/** �R���X�g���N�^ */
GlassHeart::Mode::ModeTeamLogo::ModeTeamLogo(Application::GameMain& game) : Mode::ModeMain{ game }{}
/** ���������� */
void GlassHeart::Mode::ModeTeamLogo::Init() {
    // �g�p����摜�̃e�[�u��
    const AppFrame::Resource::ResourceServer::GraphMap useGraph{
    {"TeamLogo",          {"TeamLogo/TeamLogo.png",          1, 1, 1920, 1080}} 
    };

    auto& res = GetResourceServer();
    // �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);
    // ���\�[�X�}�l�[�W���[����o�^�����摜���擾
    _teamLogo = res.GetGraph("TeamLogo");
    _fadeCount = 30;
}
/** ��������� */
void GlassHeart::Mode::ModeTeamLogo::Enter() {}
/** ���͏��� */
void GlassHeart::Mode::ModeTeamLogo::Input(AppFrame::Input::InputManager& input) {
    // B�{�^���������ꂽ���͈�莞�Ԍo�߂�����^�C�g���֑J��
    if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
        GetModeServer().GoToMode("Title");
    }
}
/** �X�V���� */
void GlassHeart::Mode::ModeTeamLogo::Process() {
    if (_fadeCount > 0) {
        --_fadeCount;
    }
}
/** �`�揈�� */
void GlassHeart::Mode::ModeTeamLogo::Render() {
    DrawGraph(0, 0, _teamLogo, FALSE);
}