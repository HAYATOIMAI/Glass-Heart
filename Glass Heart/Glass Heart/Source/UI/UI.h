/*****************************************************************//**
 * @file   UI.h
 * @brief  ユーザーインターフェースクラスの宣言
 *
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "../Application/GameMain.h"
#include <unordered_map>
#include <vector>
 /**
	* @namespace GlassHeart
	* @brief プロジェクト名
	*/
namespace GlassHeart {
	/**
	 * @namespace UI
	 * @brief UI関係
	 */
	namespace UI {
		/**
		 * @class UI
		 * @brief ユーザーインターフェース
		 */
		class UI {
		public:
			/**
			 * @brief コンストラクタ
			 *
			 */
			UI(Application::GameMain& game);
			/**
			 * @brief デストラクタ
			 *
			 */
			~UI();
			/**
			 * @brief 初期化処理
			 *
			 */
			virtual void Init();
			/**
			 * @brief 入口処理
			 *
			 */
			virtual void Enter();
			/**
			 * @brief 入力処理
			 */
			virtual void Input();
			/**
			 * @brief 更新処理
			 */
			virtual void Process(int counttime);
			/**
			 * @brief 描画処理
			 *
			 * @param x X座標描画位置
			 * @param y Y座標描画位置
			 * @param interval 間隔
			 */
			virtual void Render(int x, int y, double exrate);
			/**
			 * @brief 残り時間用描画処理
			 *
			 * @param x X座標描画位置
			 * @param y Y座標描画位置
			 * @param interval 間隔
			 * @param exrate   拡大率
			 */
			void NumberRender(int x, int y, int interval, double exrate);
			/**
			 * @brief 一の位の値を抽出する処理
			 *
			 * @param dismantvalue 一の位の値を抽出する処理
			 * @return 一の位の値
			 */
			int GetNumberPlace(int dismantvalue);
			/**
			 * @brief 桁数の取得
			 *
			 * @param value 桁数を取得する値
			 * @return  桁数
			 */
			int GetDigit(int value);

			inline Application::GameMain& GetGame() { return _game; }
		private:
			Application::GameMain& _game;  //!< プロジェクト
			int _interval{ 100 };             //!< 数字同士の間隔
			int _numberhandle[3]{ 0,0,0 };  //!< 数字の画像ハンドル
			int _second{ 0 };                   //!< 残り秒数
			int _timerhandle{ 0 };            //!< タイマーの画像ハンドル
			int digit{ -1 };                     //!< 位
		};
	} // namespace UI
} // namespace GlassHeart