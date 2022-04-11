
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
    // 使用する画像のテーブル
    const AppFrame::ResourceServer::GraphMap useMap{
    {"NowLoading",   {"Loading/Loading.png", 1, 1, 2150, 186}},
    };
    // リソースサーバーを取得
    auto& res = GetResourceServer();
    // 画像の読み込み
    res.LoadGraphics(useMap);

    _nowLoading = res.GetGraph("NowLoading");

    _loadHandle = LoadGraph("resource/Loading/LoadGraphHeart.gif");
    _cnt = 30;
}

void Mode::ModeLoading::Enter() {}

void Mode::ModeLoading::Input(AppFrame::InputManager& input) {}

void Mode::ModeLoading::Process() {
    // ロードのためのカウンタを減少
    if (_cnt > 0) {
        --_cnt;
    }
    
    auto [handle, no] = GetGame().GetResourceServer().GetModles("Stage");
    if (_cnt == 0) {
        // 非同期読み込みが終了しているか
        // FALSEなら終了、それ以外なら読み込みを再開
        if (CheckHandleASyncLoad(handle) == FALSE) {
            // 非同期読み込み終了
            SetUseASyncLoadFlag(FALSE);
            // ゲーム本編へ移動
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