
/*****************************************************************//**
 * @file   ModeMain.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>

namespace GlassHeart {

    class GameMain;
    namespace Object {
        class ObjectServer;
        class ObjectFactory;
    }

    namespace Mode {
        /**
         * @class ModeMain
         * @brief 
         */
        class ModeMain : public AppFrame::ModeBase{
        public:
            /**
             * @brief コンストラクタ
             *
             * @param game　ゲームメインクラス
             */
            ModeMain(GameMain& game);
            /**
             * @brief デストラクタ
             * 
             */
            ~ModeMain() = default;
            /**
             * @brief 初期化処理
             *
             */
            virtual void Init() override {};
            /**
             * @brief 入り口処理
             *
             */
            virtual void Enter() override {};
            /**
             * @brief 入力処理
             * 
             * @param[in] input インプットマネージャークラスへの参照
             */
            virtual void Input(AppFrame::InputManager& input) override {};
            /**
             * @brief 更新処理
             * 
             */
            virtual void Process()override {};
            /**
             * @brief　描画処理
             * 
             */
            virtual void Render() override {};
            /**
             * @brief 終了処理
             */
            virtual void Exit() override {};

            GameMain& GetGameMain() const { return _gameMain; }

            Object::ObjectFactory& GetObjectFactory();

            Object::ObjectServer& GetObjectServer();
        protected:
            GameMain& _gameMain;
        };
    }
}