
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
    {"TeamLogo",          {"TeamLogo/TeamLogo.png",          1, 1, 1920, 1080}} };
    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();
    // �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);
    // �摜�̃n���h���̎擾
    _teamLogo = res.GetGraph("TeamLogo");
    _fadeCount = 30;

    // �g�p���郂�f��
    AppFrame::ResourceServer::ModelMap useModel{
    {"Player", "Boy/PC2_motion.mv1"},
    {"Girl", "Girl/Girl.mv1"},
    };
    // ���f���̓ǂݍ���
    GetResourceServer().LoadModels(useModel);
}
/** ��������� */
void Mode::ModeTeamLogo::Enter() {
}
/** ���͏��� */
void Mode::ModeTeamLogo::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
        GetModeServer().GoToMode("Title");
    }
}
/** �X�V���� */
void Mode::ModeTeamLogo::Process() {
    if (_fadeCount > 0) {
        --_fadeCount;
    }
}
/** �`�揈�� */
void Mode::ModeTeamLogo::Render() {
    DrawGraph(0, 0, _teamLogo, FALSE);
}