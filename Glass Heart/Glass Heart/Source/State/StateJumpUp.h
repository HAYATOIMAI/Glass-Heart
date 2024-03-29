/*********************************************************************
 * @file   StateJumpUp.h
 * @brief   ジャンプ上昇状態の宣言
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <DxLib.h>
 /**
  * @namespace GlassHeart
  * @brief     プロジェクト名
  */
namespace GlassHeart {
  namespace Player {
    class Player;
  }
  /**
   * @namespace State
   * @brief     プレイヤーのステート関係
   */
  namespace State {
    /**
     * @class StateJumpUp
     * @brief ジャンプ上昇処理
     */
    class StateJumpUp : public StateBase {
    public:
      /**
       * @brief           コンストラクタ
       *
       * @param[in] owner プレイヤークラスへの参照
       */
      StateJumpUp(Player::Player& owner);
      /**
       * @brief           入り口処理
       */
      void Enter() override;
      /**
       * @brief           入力処理
       *
       * @param[in] input インプットマネージャークラスの参照
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief           更新処理
       */
      void Update() override;
    };
  } // namespace State
} // namespace GlassHeart