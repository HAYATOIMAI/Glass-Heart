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

namespace GlassHeart {

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
			UI(GameMain& game);
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
			 * @brief
			 */
			virtual void Input();
			/**
			 * @brief 更新処理
			 */
			virtual void Process(int counttime);
			/**
			 * @brief 描画処理
			 * 
			 * @param x
			 * @param y
			 * @param interval 間隔
			 */
			virtual void Render(int x, int y, int interval);
			/**
			 * @brief 一の位の値を抽出する処理
			 * 
			 * @param dismantvalue 一の位の値を抽出する処理
			 * @return 一の位の値
			 */
			int GetNumberPlace(int dismantvalue);

			int GetDigit(int value);

			GameMain& GetGame() { return _game; }
		private:
			GameMain& _game;
			int _numberhandle[3];
			int digit{ -1 };
			int _onehandle{ -1 };     //一の位の数字画像
			int _tenhandle{ -1 };  //十の位の数字画像
			int _hundhandle{ -1 }; //百の位の数字画像
			int _interval{ 100 };  //数字同士の間隔
			int _second{ 0 };
		};
	}
}





