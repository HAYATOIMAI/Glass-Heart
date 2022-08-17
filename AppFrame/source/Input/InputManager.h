/*****************************************************************//**
 * @file   InputManager.h
 * @brief  インプットマネージャークラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "InputJoypad.h"
#include <DxLib.h>
#include <utility>
 /**
	 * @namespace AppFrame
	 * @brief  アプリケーションフレーム
	 */
namespace AppFrame {
	/**
	 * @namespace Input
	 * @brief 入力処理関係
	 */
	namespace Input {
		/**
		 * @class InputManager
		 * @brief インプットマネージャークラスの宣言
		 */
		class InputManager {
		public:
			/**
			 * @brief 更新処理
			 */
			void Process();

			inline InputJoypad& GetJoyPad() { return _inputjoy; }

		private:
			InputJoypad _inputjoy;  //!< インプットジョイパッドクラスの参照
		};
	}
} // namespace AppFrame