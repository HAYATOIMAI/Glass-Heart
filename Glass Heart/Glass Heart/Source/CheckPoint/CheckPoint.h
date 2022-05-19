/*********************************************************************
 * @file   CheckPoint.h
 * @brief  チェックポイントクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"

namespace GlassHeart {
	namespace Model {
		class ModelManager;
	}
	namespace Application {
		class GameMain;
	}
	/**
   * @namespace CheckPoint
   * @brief チェックポイント関係
   */
	namespace CheckPoint {
		class CheckPoint : public Object::ObjectBase {
		public:
			/**
			 * @brief コンストラクタ
			 *
			 * @param[in] game ゲームメインクラスへの参照
			 */
			CheckPoint(Application::GameMain& game);
			/**
			 * @brief　デストラクタ
			 *
			 */
			virtual ~CheckPoint()override = default;
			/**
			 * @brief 更新処理
			 *
			 */
			void Process() override;
			/**
			 * @brief 描画処理
			 *
			 */
			void Render() override;

			ObjectType GetObjectType() const override { return ObjectType::CheckPoint; };

		private:
			int _checkPoint{ -1 };                                     //!< チェックポイント用グラフィックハンドル
			VECTOR _checkDrawPos{ 8190.0f, 5880.0f, 30.0f };  //!< チェックポイント描画用
		};
	} // namespace CheckPoint
} // namespace GlassHeart 