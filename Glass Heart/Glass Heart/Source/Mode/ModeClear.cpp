
/*****************************************************************//**
 * @file   ModeClear.cpp
 * @brief  �Q�[���N���A�N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "ModeClear.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../UI/UI.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Mode;

int ModeMain::_count;
int ModeMain::_countSeconds;

/** �R���X�g���N�^ */
ModeClear::ModeClear(GameMain& game) : ModeMain{ game } {
}
/** ���������� */
void ModeClear::Init() {
    // �g�p����摜�̃e�[�u��
    const AppFrame::ResourceServer::GraphMap useGraph{
   {"TitleBG",       {"Title/TitleBG.png",     1, 1, 1920, 1080}},
   {"Result",        {"Result/result4.png",    1, 1, 1920, 1080}},
   {"GameClear",     {"Result/GameClear.png",  1, 1, 1920, 1080}},
   {"GameOver",      {"Result/GameOver.png",   1, 1, 1920, 1080}},
    };

    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();
    // �摜�̓ǂݍ���
    res.LoadGraphics(useGraph);
    // �摜�̃n���h���̎擾
    _gameClear = res.GetGraph("GameClear");
    _gameOver = res.GetGraph("GameOver");

    // �T�E���h�}�l�[�W���[���擾
    /*auto& sm = GetSoundManager();
    sm.PlayLoop("bgm1");
    sm.SetVolume("bgm1", 50);*/
}
/** ��������� */
void ModeClear::Enter() {}
/** ���͏��� */
void ModeClear::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputButtonB()) {
        GetModeServer().GoToMode("Title");
    }
}
/** �X�V���� */ 
void ModeClear::Process() {
}
/** �`�揈�� */
void ModeClear::Render() {

    if (_countSeconds == 0) {
        DrawGraph(0, 0, _gameOver, FALSE);
    }
    else {
        DrawGraph(0, 0, _gameClear, FALSE);
    }
    GetUI().NumberRender(1650, 700, 200, 2.0);

    auto x = 0; auto y = 0; auto size = 32;
    auto black = GetColor(0, 0, 0);

    DrawFormatString(x, y, black, "���݂̎���: %d ", _count); y+= size;
    DrawFormatString(x, y, black, "���݂̎���: %d�b ", _countSeconds); y += size;

}
/** �I������ */
void ModeClear::Exit() {
    //!< �I�u�W�F�N�g������
    GetObjectServer().AllClear();
    //!< ���\�[�X�̏���
    //GetResourceServer().AllClear();
    //!< �N���G�C�^�[���폜
    //GetObjectFactory().Clear();
}