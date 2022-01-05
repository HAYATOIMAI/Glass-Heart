
/*****************************************************************//**
 * @file   InputManager.h
 * @brief  インプットマネージャークラスの宣言
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
         * @brief 更新処理
         *
         */
        void Process();

        InputJoypad& GetJoyPad() { return _inputjoy; }

    private:
        InputJoypad _inputjoy;
    };

}