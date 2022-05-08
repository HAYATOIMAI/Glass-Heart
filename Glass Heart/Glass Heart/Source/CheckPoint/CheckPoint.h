/*********************************************************************
 * @file   CheckPoint.h
 * @brief  �`�F�b�N�|�C���g�N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"
#include <unordered_map>

namespace GlassHeart {
    namespace Model {
        class ModelManager;
    }
    namespace Application {
        class GameMain;
    }
    namespace CheckPoint {

        class CheckPoint : public Object::ObjectBase {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param[in] game �Q�[�����C���N���X�ւ̎Q��
             */
            CheckPoint(Application::GameMain& game);
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

            void Register(std::string_view key, VECTOR vec);

            ObjectType GetObjectType() const override { return ObjectType::CheckPoint; };

        private:
            int _checkPoint{ -1 };                                     //!< �`�F�b�N�|�C���g�p�O���t�B�b�N�n���h��
            VECTOR _checkDrawPos{ 8190.0f, 5880.0f, 30.0f };  //!< �`�F�b�N�|�C���g�`��p
            VECTOR _checkPos{ 1730.6f, 3394.0f, -55.0f };       //!< 
            bool _isNear{ false };

            std::unordered_map<std::string, VECTOR> _checkPoints;
        };
    } // namespace CheckPoint
} // namespace GlassHeart 