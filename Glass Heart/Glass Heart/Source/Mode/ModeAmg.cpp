
/*****************************************************************//**
 * @file   ModeAmg.cpp
 * @brief  AMG��ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeAmg.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

//!< �R���X�g���N�^
Mode::ModeAmg::ModeAmg(GameMain& game) : ModeMain{ game } {
}
//!< ����������
void Mode::ModeAmg::Init() {
    //! �g�p����摜�̃e�[�u��
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"AMGBg",          {"AMG.jpg",          1, 1, 1920, 1080}}
    };

    //!< ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();

    //!< �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);

    //!< �摜�̃n���h���̎擾
    _titleBgHandle = res.GetGraph("AMGBg");

    //!< �T�E���h�}�l�[�W���[���擾
    auto& sm = GetSoundManager();
    sm.PlayLoop("bgm1");
    sm.SetVolume("bgm1", 50);

}
//!< ���������
void Mode::ModeAmg::Enter() {}
//!< ���͏���
void Mode::ModeAmg::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("TeamLogo");
    }
}
//!< �X�V����
void Mode::ModeAmg::Process() {
    //_alpha = (_alpha + 8) % 255;
}
//!< �`�揈��
void Mode::ModeAmg::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
    /*SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/
}