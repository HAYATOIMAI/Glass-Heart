
/*****************************************************************//**
 * @file   WinMain.cpp
 * @brief  �G���g���[�|�C���g
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/

#include "GameBase.h"
#include <Windows.h>
#include <memory>

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    // GameBase�N���X�̃C���X�^���X������������
    auto gamebase = AppFrame::GameBase::GameInstance();

    if (!gamebase) { return 0; }

    auto succeess = gamebase->Initialize(hInstance);

    if (succeess) {
        // �Q�[�������s���遦�������ɐ���
        gamebase->Run();
    }
    // ������������s
    gamebase->Terminate();

    return 0;
}
