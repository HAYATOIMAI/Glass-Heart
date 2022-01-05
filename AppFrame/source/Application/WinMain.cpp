
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

    // GameBase�N���X�̃C���X�^���X�𐶐����ă��j�[�N�|�C���^������������
    auto game = std::make_unique<AppFrame::GameBase>();
    auto succeess = game->Initialize();

    if (succeess) {
        // �Q�[�������s���遦�������ɐ���
        game->Run();
    }
    // ������������s
    game->Terminate();

    return 0;
}
