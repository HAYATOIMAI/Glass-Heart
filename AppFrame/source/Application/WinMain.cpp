
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

    // GameBaseクラスのインスタンスを初期化する
    auto gamebase = AppFrame::GameBase::GameInstance();

    if (!gamebase) { return 0; }

    auto succeess = gamebase->Initialize(hInstance);

    if (succeess) {
        // ゲームを実行する※初期化に成功
        gamebase->Run();
    }
    // 解放処理を実行
    gamebase->Terminate();

    return 0;
}
