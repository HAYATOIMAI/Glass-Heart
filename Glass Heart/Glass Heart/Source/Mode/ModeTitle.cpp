
/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  �^�C�g����ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTitle.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

// �R���X�g���N�^
Mode::ModeTitle::ModeTitle(GameMain& game) : ModeMain{ game } {}
// ����������
void Mode::ModeTitle::Init() {
    // �g�p����摜�̃e�[�u��
    const AppFrame::ResourceServer::GraphMap useGraph{
        {"TitleButton",   {"Title/TitleButton.png", 1, 1, 1920, 1080}},
        {"TitleLogo",     {"Title/TitleLogo.png",   1, 1, 1920, 1080}},
        {"Title",         {"Title/Title.png",       1, 1, 1920, 1080}},
    };

    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();

    // �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);

    // �摜�̃n���h���̎擾
    _title = res.GetGraph("Title");
    _titleBgHandle = res.GetGraph("TitleBG");
    _titleButtonHandle = res.GetGraph("TitleButton");
    _titleLogo = res.GetGraph("TitleLogo");
}
// ���������
void Mode::ModeTitle::Enter() {}
// ���͏���
void Mode::ModeTitle::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("InGame");
    }
}
// �X�V����
void Mode::ModeTitle::Process() {}
// �`�揈��
void Mode::ModeTitle::Render() {
    DrawGraph(0, 0, _title, FALSE);
}