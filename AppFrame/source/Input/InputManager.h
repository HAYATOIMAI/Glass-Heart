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
    /**
     * @class InputManager
     * @brief �C���v�b�g�}�l�[�W���[
     */
    class InputManager {
    public:
        /**
         * @brief �X�V����
         */
        void Process();

        inline InputJoypad& GetJoyPad() { return _inputjoy; }

    private:
        InputJoypad _inputjoy;  //!< �C���v�b�g�W���C�p�b�h�N���X�̎Q��
    };

} // namespace AppFrame