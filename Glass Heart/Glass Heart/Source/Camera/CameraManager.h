
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
            /**
             * @brief コンストラクタ
             * 
             */
            CameraManager();
            /**
             * @brief 初期化処理
             * 
             */
            void Init();
            /**
             * @brief 入力処理
             * 
             * @param[in] input インプットマネージャークラスの参照
             */
            void Input(AppFrame::InputManager& input) {};
            /**
             * @brief 更新処理
             *
             */
            void Update();
            /**
             * @brief 描画処理
             *
             */
            void Render();
             /**
              * @brief カメラ座標(始点)の設定
              * 
              * @param[in] position カメラの位置
              */
            inline void SetPosition(VECTOR position) { _position = position; }
            /// 
            /// @param[in] target
            /**
             * @brief 目標座標(注視点)の設定
             * 
             * @param[in] target  目標の位置
             * @param[in] forward 向きベクトル
             */
            inline void SetTarget(VECTOR target, VECTOR forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }
            /**
             * @brief 注視点方向のベクトルを取得
             * 
             * @return 注視点方向の単位ベクトル
             */
            inline VECTOR GetForward() const { return VNorm(VSub(_target, _position)); }
        protected:
            VECTOR _position{ 0, 0, 0 };        //!< カメラの位置ベクトル
            VECTOR _target{ 0, 0, 0 };          //!< 目標の位置ベクトル
            VECTOR _forwardOfTarget{ 0, 0, 0 }; //!< 目標の位置ベクトル
            float targetDist{ 100.0f };         //!< 目標との距離
            float vertDist{ 100.0f };           //!< 
        };
    }
}