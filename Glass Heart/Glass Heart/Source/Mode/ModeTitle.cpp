
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
         {"TitleExit",     {"Title/TitleExit.png",   1, 1, 1920, 1080}},
         {"TitleLogo",     {"Title/TitleLogo.png",   1, 1, 1920, 1080}},
         {"TitleBg",       {"Title/TitleBG.png",     1, 1, 1920, 1080}},
         {"TitlePlate",    {"Title/TitlePlate.png",  1, 1, 1920, 1080}},
         {"TitlePlate2",   {"Title/TitlePlate2.png", 1, 1, 1920, 1080}},
    };

    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();

    // �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);

    //!< �摜�̃n���h���̎擾
    _titleButton = res.GetGraph("TitleButton");
    _titleExit = res.GetGraph("TitleExit");
    _titleLogo = res.GetGraph("TitleLogo");
    _titleBg = res.GetGraph("TitleBg");
    _titlePlate = res.GetGraph("TitlePlate");
    _titlePlate2 = res.GetGraph("TitlePlate2");
}
// ���������
void Mode::ModeTitle::Enter() {
    _alpha = 0;
    _x = -1920;
    auto& sm = GetSoundManager();
    sm.PlayLoop("titleBgm");
}
// ���͏���
void Mode::ModeTitle::Input(AppFrame::InputManager& input) {

    auto [handle, no] = GetGame().GetResourceServer().GetModles("Stage");

    if (input.GetJoyPad().GetXinputButtonB()) {
        auto& sm = GetSoundManager();
        sm.Play("select");
        GetModeServer().GoToMode("Loading");
        _alpha = 255;
    }

    auto center = 0;
    auto leftEnd = -1920;

    if (input.GetJoyPad().GetXTriggerLeft() || input.GetJoyPad().GetXTriggerLeftShoulder()) {
        if (_x != center) {
            _x = center;
        }
        else if (_x == center) {
            _x = leftEnd;
        }
        //if (_x2 != center) {
        //    if (_x < center) {
        //        _x = center;
        //    }
        //    else {
        //        _x = leftEnd;
        //        _x2 = center;
        //    }
        //}
        //else if (_x2 < rightEnd) {
        //    _x2 = rightEnd;
        //}
    }
    if (input.GetJoyPad().GetXTriggerRight() || input.GetJoyPad().GetXTriggerRightShoulder()) {
        if (_x != center) {
            _x = center;
        }
        else if (_x == center) {
            _x = leftEnd;
        }
        //if (_x != center) {
        //    if (_x2 > center) {
        //        _x2 = center;
        //    }
        //    else {
        //        _x2 = rightEnd;
        //        _x = center;
        //    }
        //}
        //else if (_x < rightEnd) {
        //    _x = leftEnd;
        //}
    }
}
// �X�V����
void Mode::ModeTitle::Process() {
    _alpha = (_alpha + 2) % 255;
}
// �`�揈��
void Mode::ModeTitle::Render() {

    DrawGraph(0, 0, _titleBg, TRUE);
    DrawGraph(0, 0, _titleLogo, TRUE);
    DrawGraph(0, 0, _titleExit, TRUE);
    if (_x != 0) {
        DrawGraph(0, 0, _titlePlate, TRUE);
    }
    DrawGraph(_x, 0, _titlePlate2, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawGraph(0, 0, _titleButton, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Mode::ModeTitle::Exit() {
    auto& sm = GetSoundManager();
    sm.StopSound("titleBgm");
}
