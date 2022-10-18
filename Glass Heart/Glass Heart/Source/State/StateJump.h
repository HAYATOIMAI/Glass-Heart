/*****************************************************************//**
 * @file   StateJump.h
 * @brief  プレイヤーのジャンプ状態クラスの宣言
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <AppFrame.h>

 /**
  * @namespace GlassHeart
  * @brief プロジェクト名
  */
namespace GlassHeart {
  namespace Player {
    class Player;
  }
  /**
   * @namespace State
   * @brief  プレイヤーのステート関係
   */
  namespace State {
    /**
     * @class StateJump
     * @brief ジャンプ状態
     */
    class StateJump : public StateBase {
    public:
      /**
      * @brief コンストラクタ
      *
      * @param owner プレイヤークラスへの参照
      */
      StateJump(Player::Player& owner);
      /**
       * @brief 入り口処理
       *
       */
      void Enter() override;
      /**
       * @brief 入力処理
       *
       * @param[in] input インプットマネージャークラスの参照
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief 更新処理
       *
       */
      void Update() override;
    };
  } // namespace State
} // namespace GlassHeart