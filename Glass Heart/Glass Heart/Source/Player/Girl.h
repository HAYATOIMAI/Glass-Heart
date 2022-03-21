/*********************************************************************
 * @file   Girl.h
 * @brief  �K�[���N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Object/ObjectBase.h"
#include "../State/StateManager.h"
#include <string>
#include <AppFrame.h>

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
            virtual~Girl() = default;
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
             * @brief
             */
            ObjectType GetObjectType() const  override { return ObjectType::Girl; };
            /**
            * @brief ���[���h���W�ϊ�
            *
            */
            void ComputeWorldTransform() override;

        public:
            /**
            * @class StateBase
            * @brief �K�[���̏�Ԋ��N���X
            */
            class StateBase : public State::StateBaseRoot {
            public:
                StateBase(Girl& owner) :_owner{ owner } {};
                void Draw() override;
            protected:
                Girl& _owner;
            };
            class StateWait :public StateBase {
            public:
                StateWait(Girl& owner) :StateBase{ owner } {};
                void Enter() override;
            private:
                int _cnt{ 0 };
            };
        };
    } // Player
} // GlassHeart