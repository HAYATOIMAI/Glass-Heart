
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

/** �R���X�g���N�^ */
Mode::ModeAmg::ModeAmg(GameMain& game) : ModeMain{ game } {}
/** ���������� */
void Mode::ModeAmg::Init() {
    
    // �g�p����摜�̃e�[�u��
    const AppFrame::ResourceServer::GraphMap useGraph{
    {"AMGBg",          {"Amg/AMG.jpg",          1, 1, 1920, 1080}}
    };
    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();

    // �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);

    // �摜�̃n���h���̎擾
    _titleBgHandle = res.GetGraph("AMGBg");

    AppFrame::ResourceServer::GraphMap usegramap{
        {"0", {"Numberplate/0.png",1,1,75,120} },
        {"1", {"Numberplate/1.png",1,1,75,120} },
        {"2", {"Numberplate/2.png",1,1,75,120} },
        {"3", {"Numberplate/3.png",1,1,75,120} },
        {"4", {"Numberplate/4.png",1,1,75,120} },
        {"5", {"Numberplate/5.png",1,1,75,120} },
        {"6", {"Numberplate/6.png",1,1,75,120} },
        {"7", {"Numberplate/7.png",1,1,75,120} },
        {"8", {"Numberplate/8.png",1,1,75,120} },
        {"9", {"Numberplate/9.png",1,1,75,120} },
        {"timer",{"Numberplate/Timer.png",1,1,2377,2361}},
        {"Death",{"BackGround/break.png",1,1,1920,1080}}
    };
    GetResourceServer().LoadGraphics(usegramap);

    //!< �g�p���郂�f��
    AppFrame::ResourceServer::ModelMap usemap{
    {"Stage", "Stage/Stage04.mv1"},
    {"BackGround", "BackGround/bg.mv1"},
    };
    // ���f���̓ǂݍ���
    GetResourceServer().LoadModels(usemap);
    // �񓯊��ǂݍ��݊J�n
    SetUseASyncLoadFlag(TRUE);
    _fadeCount = 30;
}
/** ��������� */
void Mode::ModeAmg::Enter() {}
/** ���͏��� */
void Mode::ModeAmg::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB() || _fadeCount == 0) {
        GetModeServer().GoToMode("TeamLogo");
    }
}
/** �X�V���� */ 
void Mode::ModeAmg::Process() {
    if (_fadeCount > 0) {
        --_fadeCount;
    }
}
/** �`�揈�� */
void Mode::ModeAmg::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
}