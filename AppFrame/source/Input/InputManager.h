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
    /**
     * @class InputManager
     * @brief インプットマネージャー
     */
    class InputManager {
    public:
        /**
         * @brief 更新処理
         */
        void Process();

        inline InputJoypad& GetJoyPad() { return _inputjoy; }

    private:
        InputJoypad _inputjoy;  //!< インプットジョイパッドクラスの参照
    };

} // namespace AppFrame