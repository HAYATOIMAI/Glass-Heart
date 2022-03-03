#pragma once
#include "ModeMain.h"

namespace GlassHeart {

    namespace Mode {

        class ModeLoading : public ModeMain {
        public:
            ModeLoading(GameMain& game);
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
             * @param input インプットマネージャークラスへの参照
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
            int _cnt{ 0 };
        };
    }
}



