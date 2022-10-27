/*********************************************************************
 * @file   StateBaseRoot.h
 * @brief  状態の基底クラスの宣言
 *
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#pragma once
#include "../Input/InputManager.h"
 /**
  * @namespace AppFrame
  * @brief  アプリケーションフレーム
  */
namespace AppFrame {
  /**
   * @namespace State
   * @brief プレイヤーステート関係
   */
  namespace State {
    /**
     * @class StateBaseRoot
     * @brief 状態の基底クラス
     */
    class StateBaseRoot {
    public:
      /**
       * @brief コンストラクタ
       */
      StateBaseRoot() {};
      /**
       * @brief 入り口処理
       */
      virtual void Enter() {};
      /**
       * @brief 入力処理
       *
       * @param[in] input  インプットマネージャークラスの参照
       */
      virtual void Input(Input::InputManager& input) {};
      /**
       * @brief　更新処理
       *
       */
      virtual void Update() {};
      /**
       * @brief 描画処理
       *
       */
      virtual void Draw() {};
    };
  } // namespace State
} // namespace AppFrame