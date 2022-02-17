
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
             * @brief 更新処理
             * 
             */
            void Update() override;
            /**
             * @brief ジャンプ中処理
             * 
             * @return ジャンプ中の位置
             */
            VECTOR JumpUpdate();
        private:
            float _jY{ -8.0f }; //!< Y軸のジャンプ量
            VECTOR _jumpVelocity{ 0.0f, 0.0f, 0.0f }; //!< ジャンプ速度
            bool _isfall{ false }; //!< 落下中かを判断するフラグ

            float _vX{ 0.0f };  //!< 今回の移動量
            float _vY{ 0.0f };  //!< 今回の移動量
            float _vZ{ -140.0f };  //!< 今回の移動量

            VECTOR _position{ 0.0f, 0.0f, 0.0f };
        };
    }
}



