/*********************************************************************
 * @file   Player.h
 * @brief  プレイヤークラスの宣言
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include <string>

namespace AppFrame {
  namespace Input {
    class InputManager;
  }
  namespace Sound {
    class SoundManager;
  }
}
/**
 * @namespace GlassHeart
 * @brief プロジェクト名
 */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Camera {
    class CameraManager;
  }
  namespace Model {
    class ModelAnimeManager;
  }
  /**
   * @namespace Player 
   * @brief プレイヤー関係
   */
  namespace Player {
    /**
     * @class Player
     * @brief プレイヤークラスの宣言
     */
    class Player : public Object::ObjectBase {
    public:
      /**
       * @brief 色状態
       */
      enum class ColourState {
        White,
        Black,
      };
      /**
       * @brief コンストラクタ
       *
       * @param[in] game ゲームメインクラスへの参照
       */
      Player(Application::GameMain& game);
      /**
       * @brief デストラクタ
       *
       */
      virtual~Player() override = default;
      /**
       * @brief 入力処理
       *
       * @param[in] input  インプットマネージャークラスの参照
       */
      virtual void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief 更新処理
       *
       */
      virtual void Process() override;
      /**
       * @brief 描画処理
       *
       */
      void Render() override;
      /**
       * @brief オブジェクトタイプ
       */
      ObjectType GetObjectType() const override { return ObjectType::Player; };
      /**
       * @brief ワールド座標変換
       *
       */
      void ComputeWorldTransform() override;
      /**
       * @brief 移動処理
       *
       * @param[in] forward 向きベクトル
       */
      virtual void Move(const VECTOR& forward);
      /**
       * @brief 色判定処理
       *
       */
      void ColorChange();
      /**
       * @brief プレイヤーの色を白に変更
       *
       */
      void SetWhite();
      /**
       * @brief プレイヤーの色を黒に変更
       *
       */
      void SetBlack();
      /**
       * @brief 
       *
       */
      void ResetPos();
      /**
       * @ プレイヤーの移動速度の移動速度のゲッター
       * 
       * @return プレイヤーの移動速度
       */
      inline float GetForwardSpeed() { return _forwardSpeed; }
      /**
       * @ プレイヤーの移動速度のセッター
       * 
       * @param[in] forwardSpeed プレイヤーの移動速度にセットする値
       */
      inline void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }
      /**
       * @ デバッグ用ステート名変数のゲッター
       * 
       * @return ステート名
       */
      inline std::string& GetCrName() { return _stateName; }
      /**
       * @ 色状態を取得するゲッター
       * 
       * @return プレイヤーの色
       */
      inline ColourState& GetColourState() { return _crState; }
      /**
       * @ ジャンプ速度を取得するゲッター
       * 
       * @return ジャンプ速度
       */
      inline VECTOR GetJumpVelocity() { return _jumpVelocity; }
      /**
       * @ ジャンプ速度をセットする
       * 
       * @param[in] jump セットするジャンプ速度
       */
      inline void SetJumpVelocity(VECTOR jump) { _jumpVelocity = jump; }
      /**
       * @ チェックポイントを通過したかのフラグのゲッター
       * 
       * @return 通過したかのフラグ
       */
      inline bool GetCheckPointFlag() { return _checkPointFlag; }
      /**
       * @ チェックポイントを通過したかのフラグのセッター
       * 
       * @param[in] flag
       */
      inline void SetCheckPointFlag(bool flag) { _checkPointFlag = flag; }
    protected:
      bool _checkPointFlag{ false };               //!< チェックポイントフラグ
      ColourState _crState{ ColourState::White };  //!< 色状態を管理する変数
      float _forwardSpeed{ 0.0f };                 //!< 移動速度
      std::int_fast16_t _deathCoolCount{ 0 };      //!< 死亡した時の復活までのクールタイム
      std::int_fast8_t _recastCount{ 0 };          //!< 色変更クールタイム用カウンタ
      std::string _stateName{ "White" };           //!< デバッグ用状態名変数
      VECTOR _jumpVelocity{ 0.0f, 0.0f, 0.0f };    //!< ジャンプ速度
    };
  } // namespace Player
} // namespace GlassHeart