
/*****************************************************************//**
 * @file   WinMain.cpp
 * @brief  エントリーポイント
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/

#include "GameBase.h"
#include <Windows.h>
#include <memory>

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    // GameBaseクラスのインスタンスを生成してユニークポインタを初期化する
    auto game = std::make_unique<AppFrame::GameBase>();
    auto succeess = game->Initialize();

    if (succeess) {
        // ゲームを実行する※初期化に成功
        game->Run();
    }
    // 解放処理を実行
    game->Terminate();

    return 0;
}
