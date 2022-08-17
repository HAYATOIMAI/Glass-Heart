/*********************************************************************
 * @file   Utility.cpp
 * @brief 便利な関数群
 *
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#include "Utility.h"

namespace {
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
}

namespace AppFrame {
	namespace Utility {
		/** コンストラクタ */
		Utility::Utility() {
		}
		/**  一様整数分布の乱数を生成*/
		int Utility::GetRandom(int min, int max) {
			std::uniform_int_distribution<> distribution(min, max);
			return distribution(engine);
		}
		/** メモリリークチェック */
		void Utility::CheckMemoryLeak() {
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}
	}
}