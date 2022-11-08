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
 * @brief     プロジェクト名
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
   * @brief     プレイヤー関係
   */
  namespace Player {
    /**
     * @class Player
     * @brief プレイヤークラス
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
       * @brief                  コンストラクタ
       *
       * @param[in] game         ゲームメインクラスへの参照
       */
      Player(Application::GameMain& game);
      /**
       * @brief                  デストラクタ
       */
      virtual~Player() override = default;
      /**
       * @brief                  入力処理
       *                         
       * @param[in] input        インプットマネージャークラスの参照
       */
      virtual void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief                  更新処理
       */
      virtual void Process() override;
      /**
       * @brief                  描画処理
       */
      void Render() override;
      /**
       * @brief                  オブジェクトタイプ
       */
      ObjectType GetObjectType() const override { return ObjectType::Player; };
      /**
       * @brief                  ワールド座標変換
       */
      void ComputeWorldTransform() override;
      /**
       * @brief                  移動処理
       *                         
       * @param[in] forward      向きベクトル
       */
      virtual void Move(const VECTOR& forward);
      /**
       * @brief                  色判定処理
       */
      void ColorChange();
      /**
       * @brief                  プレイヤーの色を白に変更
       */
      void SetWhite();
      /**
       * @brief                  プレイヤーの色を黒に変更
       */
      void SetBlack();
      /**
       * @brief                  プレイヤーの位置を初期化
       */
      void ResetPos();
      /**
       * @brief                  プレイヤーの移動速度の移動速度を取得
       *                         
       * @return                 プレイヤーの移動速度
       */
      inline float GetForwardSpeed() const { return _forwardSpeed; }
      /**
       * @brief                  プレイヤーの移動速度をセットする
       * 
       * @param[in] forwardSpeed プレイヤーの移動速度にセットする値
       */
      inline void SetForwardSpeed(const float forwardSpeed) { _forwardSpeed = forwardSpeed; }
      /**
       * @brief                  デバッグ用ステート名変数を取得
       *                         
       * @return                 ステート名の参照
       */
      inline std::string& GetCrName() { return _stateName; }
      /**
       * @brief                  プレイヤーの色状態を取得
       *                         
       * @return                 プレイヤーの色の参照
       */
      inline ColourState& GetColourState() { return _colorState; }
      /**
       * @brief                  ジャンプ速度を取得する
       *                         
       * @return                 ジャンプ速度
       */
      inline VECTOR GetJumpVelocity() const { return _jumpVelocity; }
      /**
       * @brief                  ジャンプ速度をセットする
       *                        
       * @param[in] jump         セットするジャンプ速度
       */
      inline void SetJumpVelocity(const VECTOR jump) { _jumpVelocity = jump; }
      /**
       * @brief                  チェックポイントを通過したかのフラグを取得
       *                         
       * @return                 通過したかのフラグ
       */
      inline bool GetCheckPointFlag() const { return _checkPointFlag; }
      /**
       * @brief                  チェックポイントを通過したかのフラグを取得
       *                        
       * @param[in] flag         通過したかのフラグ
       */
      inline void SetCheckPointFlag(const bool flag) { _checkPointFlag = flag; }
    protected:
      /**
       * @brief 
       * 
       */
      void CollisionDetectionByColor();
      /**
       * @brief 
       * 
       */
      void IsHitCheckPoint();
      bool _checkPointFlag{ false };                  //!< チェックポイントフラグ
      ColourState _colorState{ ColourState::White };  //!< 色状態を管理する変数
      float _forwardSpeed{ 0.0f };                    //!< 移動速度
      int_fast16_t _deathCoolCount{ 0 };              //!< 死亡した時の復活までのクールタイム
      int_fast16_t _recastCount{ 0 };                 //!< 色変更クールタイム用カウンタ
      std::string _stateName{ "White" };              //!< デバッグ用状態名変数
      VECTOR _jumpVelocity{ 0.0f, 0.0f, 0.0f };       //!< ジャンプ速度
    };
  } // namespace Player
} // namespace GlassHeart