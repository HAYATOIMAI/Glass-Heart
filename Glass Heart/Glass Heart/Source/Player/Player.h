
/*****************************************************************//**
 * @file   Player.h
 * @brief  プレイヤークラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"


namespace GlassHeart {

	namespace Camera {
		class CameraManager;
	}
	namespace Model {
		class ModelAnimeManager;
	}
	
	namespace Player {
		/**
		 * @class Player
		 * @brief プレイヤー
		 */
		class Player : public  GlassHeart::Object::ObjectBase {
		public:
			/**
			 * @brief コンストラクタ
			 * 
			 * @param game ゲームメインクラスへの参照
			 */
			Player(GameMain& game);
			/**
			 * @brief デストラクタ
			 * 
			 */
			virtual~Player() = default;
			/**
			 * @brief 入力処理
			 * 
			 * @param input
			 */
			virtual void Input(AppFrame::InputManager& input) override;
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
			 * @brief 
			 */
			ObjectType GetObjectType() const  override { return ObjectType::Player; };
			/**
			 * @brief ワールド座標変換
			 * 
			 */
			void ComputeWorldTransform() override;

			float GetForwardSpeed() { return _forwardSpeed; }
			void SetForwardSpeed(float forwardspeed) { _forwardSpeed = forwardspeed; }

		protected:
			float _forwardSpeed{ 0.0f };  //!< 
			float _angularSpeed{ 0.0f };  //!< 
			VECTOR _backDelta{ 0, 0, 0 };  //!<
			/**
			 * @brief 移動処理
			 * 
			 * @param[in] forward
			 */
			virtual void Move(const VECTOR& forward);
			/**
			 * @brief 敵との接触判定
			 * @details 使用予定無し
			 */
			void HitCheckEnemy();
		};
	}
}