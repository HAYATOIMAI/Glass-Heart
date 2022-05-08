/*********************************************************************
 * @file   Utility.h
 * @brief �֗��Ȋ֐��Q
 * 
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#pragma once
#include "Singleton.h"
#include <random>

 // ���������[�N���o�p
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define NEW new
#endif

namespace AppFrame {

    namespace Utility {
        /**
         * @class Utility
         * @brief �֗��Ȋ֐��Q
         */
        class Utility : public Singleton<Utility> {
        private:
            /**
             * @brief �R���X�g���N�^
             */
            Utility();
            /**
             * @brief �f�X�g���N�^
             */
            ~Utility() override {};
        public:
            friend class Singleton<Utility>;  // �C���X�^���X����������
            /**
             * @brief ��l�������z�̗����𐶐�
             *
             * @param[in] min �ŏ��l
             * @param[in] max �ő�l
             * @return �������ꂽ����
             */
            static  int  GetRandom(int min, int max);
            /**
             * @brief ���������[�N���o
             *
             */
            void CheckMemoryLeak();
        };
    } // namespace Utility
} // namespace AppFrame