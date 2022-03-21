/*********************************************************************
 * @file   Girl.h
 * @brief  ガールクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Object/ObjectBase.h"
#include "../State/StateManager.h"
#include <string>
#include <AppFrame.h>

namespace AppFrame {
    class InputManager;
    class SoundManager;
}

namespace GlassHeart {

    class GameMain;

    namespace Model {
        class ModelAnimeManager;
    }

    namespace Player {
        /**
         * @class Girl
         * @brief ガール
         */
        class Girl : public  Object::ObjectBase {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param game ゲームメインクラスへの参照
             */
            Girl(GameMain& game);
            /**
             * @brief デストラクタ
             *
             */
            virtual~Girl() = default;
            /**
             * @brief 入力処理
             *
             * @param[in] input  インプットマネージャークラスの参照
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief 更新処理
             *
             */
            void Process() override;
            /**
             * @brief 描画処理
             *
             */
            void Render() override;
            /**
             * @brief
             */
            ObjectType GetObjectType() const  override { return ObjectType::Girl; };
            /**
            * @brief ワールド座標変換
            *
            */
            void ComputeWorldTransform() override;

        public:
            /**
            * @class StateBase
            * @brief ガールの状態基底クラス
            */
            class StateBase : public State::StateBaseRoot {
            public:
                StateBase(Girl& owner) :_owner{ owner } {};
                void Draw() override;
            protected:
                Girl& _owner;
            };
            class StateWait :public StateBase {
            public:
                StateWait(Girl& owner) :StateBase{ owner } {};
                void Enter() override;
            private:
                int _cnt{ 0 };
            };
        };
    } // Player
} // GlassHeart