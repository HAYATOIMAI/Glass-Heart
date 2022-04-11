
/*********************************************************************
 * @file   ModeLoading.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   March 2022
 *********************************************************************/
#include "ModeLoading.h"
#include <AppFrame.h>

using namespace GlassHeart;

Mode::ModeLoading::ModeLoading(Application::GameMain& game) : ModeMain(game){}

void Mode::ModeLoading::Init() {
    // �g�p����摜�̃e�[�u��
    const AppFrame::ResourceServer::GraphMap useMap{
    {"NowLoading",   {"Loading/Loading.png", 1, 1, 2150, 186}},
    };
    // ���\�[�X�T�[�o�[���擾
    auto& res = GetResourceServer();
    // �摜�̓ǂݍ���
    res.LoadGraphics(useMap);

    _nowLoading = res.GetGraph("NowLoading");

    _loadHandle = LoadGraph("resource/Loading/LoadGraphHeart.gif");
    _cnt = 30;
}

void Mode::ModeLoading::Enter() {}

void Mode::ModeLoading::Input(AppFrame::InputManager& input) {}

void Mode::ModeLoading::Process() {
    // ���[�h�̂��߂̃J�E���^������
    if (_cnt > 0) {
        --_cnt;
    }
    
    auto [handle, no] = GetGame().GetResourceServer().GetModles("Stage");
    if (_cnt == 0) {
        // �񓯊��ǂݍ��݂��I�����Ă��邩
        // FALSE�Ȃ�I���A����ȊO�Ȃ�ǂݍ��݂��ĊJ
        if (CheckHandleASyncLoad(handle) == FALSE) {
            // �񓯊��ǂݍ��ݏI��
            SetUseASyncLoadFlag(FALSE);
            // �Q�[���{�҂ֈړ�
            GetModeServer().GoToMode("InGame");
        }
        else {
            _cnt = 60;
        }
    }
}

void Mode::ModeLoading::Render() {
    PlayMovieToGraph(_loadHandle);
    DrawGraph(0, 850, _nowLoading, FALSE);
    DrawGraph(1700, 900, _loadHandle, FALSE);
}