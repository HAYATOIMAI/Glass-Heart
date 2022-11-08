/*********************************************************************
 * @file   StateIdle.h
 * @brief  アイドル状態クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateBase.h"
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
     * @class StateIdle
     * @brief アイドル状態クラスの宣言
     */
    class StateIdle : public StateBase {
    public:
      /**
       * @brief           コンストラクタ
       *
       * @param[in] owner プレイヤークラスへの参照
       */
      StateIdle(Player::Player& owner) : StateBase{ owner } {};
      /**
       * @brief           入り口処理
       */
      void Enter() override;
      /**
       * @brief　         入力処理
       *
       * @param[in] input インプットマネージャークラスの参照
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief　         更新処理
       */
      void Update() override;
    private:
      bool _resetFlag{ false };           //!< 色をリセットするかのフラグ
      int_fast16_t _recastCnt{ 0 };  //!< リキャスト用カウンター
    };
  } // namespace State
} // namespace GlassHeart
