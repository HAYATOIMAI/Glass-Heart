
/*****************************************************************//**
 * @file   InputManager.h
 * @brief  �C���v�b�g�}�l�[�W���[�N���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "InputJoypad.h"
#include <DxLib.h>
#include <utility>

namespace AppFrame {

    class InputManager {
    public:
        /**
         * @brief �X�V����
         *
         */
        void Process();

        InputJoypad& GetJoyPad() { return _inputjoy; }

    private:
        InputJoypad _inputjoy;
    };

}