
/*****************************************************************//**
 * @file   CameraManager.h
 * @brief  カメラマネージャー
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <utility>
#include <memory>
#include <DxLib.h>

namespace AppFrame {
    class InputManager;
}

namespace GlassHeart {

    namespace Camera {

        class CameraManager {
        public:
            CameraManager();
            /// 初期化
            void Init();
            /// 入力処理
            void Input(AppFrame::InputManager& input);
            /// 更新処理
            void Update();
            /// 描画処理
            void Render();
            /// カメラ座標(始点)の設定
             /// @param[in] position
            void SetPosition(VECTOR position) { _position = position; }
            /// 目標座標(注視点)の設定
            /// @param[in] target
            void SetTarget(VECTOR target, VECTOR forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }
            /// 注視点方向のベクトルを取得
            /// @return 注視点方向の単位ベクトル
            VECTOR GetForward() const { return VNorm(VSub(_target, _position)); }
        protected:
            VECTOR _position{ 0, 0, 0 };
            VECTOR _target{ 0, 0, 0 };
            VECTOR _forwardOfTarget{ 0, 0, 0 };
            float targetDist{ 100.0f };
            float vertDist{ 100.0f };
        };
    }
}