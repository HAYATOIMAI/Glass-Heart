#include "ModeLoading.h"

using namespace GlassHeart;

Mode::ModeLoading::ModeLoading(GameMain& game) : ModeMain(game){}

void Mode::ModeLoading::Init() {
    _loadHandle = LoadGraph("resource/Loading/LoadGraphHeart.gif");
    _cnt = 180;
}

void Mode::ModeLoading::Enter() {
}

void Mode::ModeLoading::Input(AppFrame::InputManager& input) {   
}

void Mode::ModeLoading::Process() {
    // ���[�h�̈׃J�E���^������
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

    DrawGraph(1700, 900, _loadHandle, FALSE);
}