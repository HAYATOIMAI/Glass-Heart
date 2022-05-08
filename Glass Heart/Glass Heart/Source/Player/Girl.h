/*********************************************************************
 * @file   Girl.h
 * @brief  ガールクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#pragma once

#include <string>
#include <AppFrame.h>
#include "../Object/ObjectBase.h"
#include "../State/StateManager.h"


namespace AppFrame {
    namespace Input {
        class InputManager;
    }
    namespace Sound {
        class SoundManager;
    }
}

namespace GlassHeart {

    namespace Application {
        class GameMain;
    }
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
            Girl(Application::GameMain& game);
            /**
             * @brief デストラクタ
             *
             */
            virtual~Girl() override = default;
            /**
             * @brief 入力処理
             *
             * @param[in] input  インプットマネージャークラスの参照
             */
            void Input(AppFrame::Input::InputManager& input) override;
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
            * @brief ワールド座標変換
            *
            */
            void ComputeWorldTransform() override;
            /**
             * @brief タイプの取得
             * @return タイプID
             */
            ObjectType GetObjectType() const  override { return ObjectType::Girl; };

        public:
            /**
            * @class StateBase
            * @brief ガールの状態基底クラス
            */
            class StateBase : public AppFrame::State::StateBaseRoot {
            public:
                StateBase(Girl& owner) :_owner{ owner } {};
                void Draw() override;
            protected:
                Girl& _owner;
            };
            /**
            * @class StateWait
            * @brief ガールの待機状態
            */
            class StateWait :public StateBase {
            public:
                StateWait(Girl& owner) :StateBase{ owner } {};
                void Enter() override;
            };
        };
    }
}
