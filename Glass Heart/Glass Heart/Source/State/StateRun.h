
/*********************************************************************
 * @file   StateRun.h
 * @brief  プレイヤーの走り状態クラスの宣言
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace GlassHeart {

    namespace Player {
        class Player;   
    }

    namespace State {
       /**
        * @class StateRun
        * @brief プレイヤーの走り状態クラス
        */
        class StateRun : public StateBase{
        public:
            /**
            * @brief コンストラクタ
            *
            * @param[in] owner プレイヤークラスへの参照
            */
            StateRun(Player::Player& owner) : StateBase{ owner } {};
            /**
             * @brief 入り口処理
             *
             */
            void Enter() override;
            /**
             * @brief　入力処理
             *
             * @param[in] input インプットマネージャークラスの参照
             */
            void Input(AppFrame::InputManager& input) override;
            /**
            * @brief　更新処理
            *
            */
            void Update() override;
        };
    }
}



