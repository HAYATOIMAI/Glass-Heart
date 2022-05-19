/*********************************************************************
 * @file   Utility.cpp
 * @brief �֗��Ȋ֐��Q
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
		/** �R���X�g���N�^ */
		Utility::Utility() {
		}
		/**  ��l�������z�̗����𐶐�*/
		int Utility::GetRandom(int min, int max) {
			std::uniform_int_distribution<> distribution(min, max);
			return distribution(engine);
		}
		/** ���������[�N�`�F�b�N */
		void Utility::CheckMemoryLeak() {
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}
	}
}