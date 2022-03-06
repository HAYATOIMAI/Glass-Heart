#pragma once
#include "ModeMain.h"

namespace GlassHeart {

    namespace Mode {

        class ModeLoading : public ModeMain {
        public:
            /**
             * @brief コンストラクタ
             * 
             * @param[in] game
             */
            ModeLoading(GameMain& game);
            /**
             * @brief デストラクタ
             * 
             */
            ~ModeLoading() = default;
            /**
             * @brief 初期化処理
             *
             */
            void Init() override;
            /**
             * @brief 入り口処理
             *
             */
            virtual void Enter() override;
            /**
             * @brief 入力処理
             *
             * @param[in] input インプットマネージャークラスへの参照
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
        private:
            int _loadHandle{ -1 };
            int _nowLoading{ -1 };
            int _cnt{ 0 };
        };
    }
}