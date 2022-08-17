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
#include <AppFrame.h>

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
		class Player : public  Object::ObjectBase {
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
			 * @param game ゲームメインクラスへの参照
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
			 * @brief オブラートタイプ
			 */
			ObjectType GetObjectType() const  override { return ObjectType::Player; };
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

			inline float GetForwardSpeed() { return _forwardSpeed; }
			inline void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }

			inline std::string& GetCrName() { return _stateName; }

			inline ColourState& GetColourState() { return _crState; }

			inline VECTOR GetJumpVelocity() { return _jumpVelocity; }
			inline void SetJumpVelocity(VECTOR jump) { _jumpVelocity = jump; }

			inline bool GetCheckPointFlag() { return _checkPointFlag; }
			inline void SetCheckPointFlag(bool flag) { _checkPointFlag = flag; }
		protected:
			bool _checkPointFlag{ false };                    //!< チェックポイントフラグ
			ColourState _crState{ ColourState::White };  //!< 色状態を管理する変数
			float _forwardSpeed{ 0.0f };                       //!< 移動速度
			std::int_fast16_t _deathCoolCount{ 0 };                           //!< 死亡した時の復活までのクールタイム
			std::int_fast8_t _recastCount{ 0 };                                //!< 色変更クールタイム用カウンタ
			std::string _stateName{ "White" };                //!< デバッグ用状態名変数
			VECTOR _jumpVelocity{ 0.f, 0.f, 0.f };            //!< ジャンプ速度
		};
	} // namespace Player
} // namespace GlassHeart