
/*********************************************************************
* @file   GoalPoint.h
* @brief  �S�[���|�C���g�N���X�̐錾
*
* @author Yoshihiro Takahashi
* @date   February 2022
*********************************************************************/
#pragma once

#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"

namespace GlassHeart {

    namespace CheckPoint {
        /**
        * @class GoalPoint
        * @brief �S�[���|�C���g
        */
        class GoalPoint : public Object::ObjectBase {
        public:
            /**
            * @brief �R���X�g���N�^
            *
            * @param game �Q�[�����C���N���X�ւ̎Q��
            */
            GoalPoint(GameMain& game);
            /**
            * @brief �f�X�g���N�^
            *
            */
            virtual ~GoalPoint() override = default;
            /**
            * @brief �X�V����
            *
            */
            void Process() override;
            /**
            * @brief �`�揈��
            *
            */
            void Render() override;
            /**
            * @brief �Q�[���N���A�֑J�ڏ���
            *
            */
            void GoToGameClear();
            /**
            * @brief �^�C�v�̎擾
            * @return �^�C�vID
            */
            ObjectType GetObjectType() const override { return ObjectType::GoalPoint; };

        private:

            int _goalPoint{ -1 };
            VECTOR _goalDrawPos{ 25800.0f, 12580.0f, 80.0f };
            VECTOR _goalPos{ -1500.0f, 70.0f, -140.0f };
        };
    }
}
