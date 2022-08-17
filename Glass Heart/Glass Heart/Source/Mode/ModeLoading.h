/*****************************************************************//**
 * @file   ModeLoading.h
 * @brief  ローディング画面クラスの宣言
 *
 * @author Hayato Imai
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ModeMain.h"
 /**
	* @namespace GlassHeart
	* @brief プロジェクト名
	*/
namespace GlassHeart {
	namespace Application {
		class GameMain;
	}
	/**
	 * @namespace Mode
	 * @brief モード関係
	 */
	namespace Mode {
		/**
		 * @class ModeLoading
		 * @brief ローディング画面クラスの宣言
		 */
		class ModeLoading : public ModeMain {
		public:
			/**
			 * @brief コンストラクタ
			 *
			 * @param[in] game
			 */
			ModeLoading(Application::GameMain& game);
			/**
			 * @brief デストラクタ
			 *
			 */
			~ModeLoading() = default;
			/**
			 * @brief 初期化処理
			 *
			 */
			void Init() override;
			/**
			 * @brief 入り口処理
			 *
			 */
			virtual void Enter() override;
			/**
			 * @brief 入力処理
			 *
			 * @param[in] input インプットマネージャークラスへの参照
			 */
			void Input(AppFrame::Input::InputManager& input) override;
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
		private:
			std::uint16_t _cnt{ 0 };              //!< ローディング時間
			std::int_fast32_t _loadHandle{ -1 };  //!< ローディングGIF画像用ハンドル
		};
	} // namespace Mode
} // namespace GlassHeart