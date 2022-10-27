/*****************************************************************//**
 * @file   StateBase.h
 * @brief  プレイヤーの状態基底クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateManager.h"
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
   * @brief     プレイヤーのステート関係
   */
  namespace State {
    /**
     * @class StateBase
     * @brief プレイヤーの状態基底クラス
     */
    class StateBase : public AppFrame::State::StateBaseRoot {
    public:
      /**
       * @brief           コンストラクタ
       *
       * @param[in] owner プレイヤークラスへの参照
       */
      StateBase(Player::Player& owner) : _owner{ owner } {};
      /**
       * @brief           描画処理
       */
      void Draw() override;
    protected:
      Player::Player& _owner;  //!< プレイヤークラスの参照
    };
  } // namespace State
} // namespace GlassHeart