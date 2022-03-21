
/*********************************************************************
 * @file   StateJumpUp.h
 * @brief  上昇状態の宣言
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <DxLib.h>

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {
        /**
         * @class StateJumpUp
         * @brief ジャンプ上昇処理
         */
        class StateJumpUp : public StateBase {
        public:
            /**
             * @brief コンストラクタ
             * 
             * @param owner プレイヤークラスへの参照
             */
            StateJumpUp(Player::Player& owner);
            /**
             * @brief 入り口処理
             * 
             */
            void Enter() override;
            /**
             * @brief
             * 
             * @param input
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief 更新処理
             * 
             */
            void Update() override;
        private:
            float _jY{ -2.0f }; //!< 重力加速度
            bool _isfall{ false }; //!< 落下中かを判断するフラグ
            float _vX{ 0.0f };  //!< 今回の移動量
        };
    } // State 
} // GlassHeart



