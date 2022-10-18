/*****************************************************************//**
 * @file   CameraManager.h
 * @brief  カメラマネージャークラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <utility>
#include <memory>
#include <DxLib.h>

namespace AppFrame {
  namespace Input {
    class InputManager;
  }
}
/**
 * @namespace GlassHeart
 * @brief プロジェクト名
 */
namespace GlassHeart {
  /**
   * @namespace Camera
   * @brief カメラ関係
   */
  namespace Camera {
    /**
     * @class CameraManager
     * @brief カメラマネージャークラスの宣言
     */
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
      void Input(AppFrame::Input::InputManager& input) {};
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
      VECTOR _position{ 0.f, 0.f, 0.f };         //!< カメラの位置ベクトル
      VECTOR _target{ 0.f, 0.f, 0.f };           //!< 目標の位置ベクトル
      VECTOR _forwardOfTarget{ 0.f, 0.f, 0.f };  //!< 目標の向きベクトル
      float _targetDist{ 100.0f };               //!< 目標との距離
    };
  } // namespace Camera
} // namespace GlassHeart