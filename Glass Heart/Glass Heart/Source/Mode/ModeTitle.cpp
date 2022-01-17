
/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  �^�C�g����ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeTitle.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Mode;

//!< �R���X�g���N�^
ModeTitle::ModeTitle(GameMain& game) : ModeMain{ game } {
}
//!< ����������
void ModeTitle::Init() {
    //! �g�p����摜�̃e�[�u��
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"GameTitle",        {"GameTitle.png",        1, 1, 1553, 224}},
    {"LeftClickToStart", {"LeftClickToStart.png", 1, 1, 1135, 107}},
    };

    //!< ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();

    //!< �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);

    //!< �摜�̃n���h���̎擾
    _titleBgHandle = res.GetGraph("GameTitle");

    //!< �T�E���h�}�l�[�W���[���擾
    auto& sm = GetSoundManager();
    sm.PlayLoop("bgm1");
    sm.SetVolume("bgm1", 50);

}
//!< ���������
void ModeTitle::Enter() {
}
//!< ���͏���
void ModeTitle::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("InGame");
    }
}
//!< �X�V����
void ModeTitle::Process() {
}
//!< �`�揈��
void ModeTitle::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
    //SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawGraph(0, 0, _gameTitleHandle, TRUE);
}