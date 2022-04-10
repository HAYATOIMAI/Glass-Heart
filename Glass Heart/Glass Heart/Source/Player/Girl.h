/*********************************************************************
 * @file   Girl.h
 * @brief  �K�[���N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#pragma once

#include <string>
#include <AppFrame.h>
#include "../Object/ObjectBase.h"
#include "../State/StateManager.h"


namespace AppFrame {
    class InputManager;
    class SoundManager;
}

namespace GlassHeart {

    class GameMain;

    namespace Model {
        class ModelAnimeManager;
    }

    namespace Player {
        /**
         * @class Girl
         * @brief �K�[��
         */
        class Girl : public  Object::ObjectBase {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param game �Q�[�����C���N���X�ւ̎Q��
             */
            Girl(GameMain& game);
            /**
             * @brief �f�X�g���N�^
             *
             */
            virtual~Girl() override = default;
            /**
             * @brief ���͏���
             *
             * @param[in] input  �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            void Input(AppFrame::InputManager& input) override;
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
            * @brief ���[���h���W�ϊ�
            *
            */
            void ComputeWorldTransform() override;
            /**
             * @brief �^�C�v�̎擾
             * @return �^�C�vID
             */
            ObjectType GetObjectType() const  override { return ObjectType::Girl; };

        public:
            /**
            * @class StateBase
            * @brief �K�[���̏�Ԋ��N���X
            */
            class StateBase : public AppFrame::StateBaseRoot {
            public:
                StateBase(Girl& owner) :_owner{ owner } {};
                void Draw() override;
            protected:
                Girl& _owner;
            };
            /**
            * @class StateWait
            * @brief �K�[���̑ҋ@���
            */
            class StateWait :public StateBase {
            public:
                StateWait(Girl& owner) :StateBase{ owner } {};
                void Enter() override;
            };
        };
    }
}
