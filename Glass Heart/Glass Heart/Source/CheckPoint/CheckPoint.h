
/*********************************************************************
 * @file   CheckPoint.h
 * @brief  �`�F�b�N�|�C���g�N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"

namespace GlassHeart {

    namespace Model {
        class ModelManager;
    }

    class GameMain;

    namespace CheckPoint {

        class CheckPoint : public Object::ObjectBase {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param[in] game �Q�[�����C���N���X�ւ̎Q��
             */
            CheckPoint(GameMain& game);
            /**
             * @brief�@�f�X�g���N�^
             * 
             */
            virtual ~CheckPoint()override = default;
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

            ObjectType GetObjectType() const override { return ObjectType::CheckPoint; };

        private:
            int _checkPoint{ -1 };
            VECTOR _checkDrawPos{ 8190.0f, 5880.0f, 30.0f };
            VECTOR _checkPos{ 0.0f, 0.0f, 0.0f };
        };
    }
}