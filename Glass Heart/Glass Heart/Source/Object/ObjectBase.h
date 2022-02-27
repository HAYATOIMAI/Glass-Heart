
/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  �I�u�W�F�N�g�̊��N���X
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include <DxLib.h>
#include <memory>

/** ��d�C���N���[�h�h�~ */
namespace AppFrame {
    class ResourceServer;
    class InputManager;
}

namespace GlassHeart {

    class GameMain;
    namespace Collision {
        class CollisionManager;
    }
    namespace Model {
        class ModelAnimeManager;
    }
    namespace Camera {
        class CameraManager;
    }
    namespace State {
        class StateManager;
    }

    namespace Object {
        class ObjectServer;
        class ObjectFactory;
        /**
         * @class ObjectBase
         * @brief �I�u�W�F�N�g�̊��N���X
         */
        class ObjectBase {
        public:
            /**
            * @brief�@�I�u�W�F�N�g�̎��
            */
            enum class ObjectType {
                Object = 0,
                Player,
                Enemy,
                Camera,
                Stage,
                CheckPoint,
                GoalPoint
            };
            /**
             * @brief �I�u�W�F�N�g�̏��
             */
            enum class ObjectState {
                Active,
                Pause,
                Dead
            };
            /**
             * @brief �R���X�g���N�^
             *
             * @param game �Q�[�����C���N���X�ւ̎Q��
             */
            ObjectBase(GameMain& game);
            /**
             * @brief �f�X�g���N�^
             *
             */
            virtual ~ObjectBase();
            /**
             * @brief ����������
             */
            virtual	void Init() {};
            /**
             * @brief ���͏���
             * 
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            virtual	void Input(AppFrame::InputManager& input) {};
            /**
             * @brief �X�V����
             */
            virtual	void Process() {};
            /**
             * @brief �`�揈��
             */
            virtual	void Render() {};
            /**
             * @brief�@�I�u�W�F�N�g�̎�ނ��擾
             *
             * @return �I�u�W�F�N�g�̎��
             */
            virtual ObjectType GetObjectType() const = 0;
            /**
             * @brief ���S��ԂɂȂ��Ă��邩
             *
             * @return �I�u�W�F�N�g�̏��
             */
            bool IsDead() { return (_objectState == ObjectState::Dead); }
            /**
             * @brief ������ԂɂȂ��Ă��邩
             *
             * @return  �I�u�W�F�N�g�̏��
             */
            bool IsActive() { return (_objectState == ObjectState::Active); }

            GameMain& GetGame() { return _game; }
            /**
             * @brief ���[���h���W�ϊ�
             *
             */
            virtual void ComputeWorldTransform();
            const MATRIX& GetWorldTransform() const { return _worldTransform; }
            VECTOR GetForward() const { return VTransform({ 0, 0, 1 }, MGetRotY(_rotation.y)); }

            void SetPosition(const VECTOR& position) { _position = position; }
            VECTOR GetPosition() const { return _position; }
            void SetRotation(const VECTOR& rotation) { _rotation = rotation; }
            VECTOR GetRotation() const { return _rotation; }
            void SetScale(const VECTOR& scale) { _scale = scale; }
            VECTOR GetScale() const { return _scale; }

            void SetRadius(const float radius) { _radius = radius; }
            float GetRadius() const { return _radius; }

            void SetHitFlag(const bool hitFlag) { _hitFlag = hitFlag; }
            bool GetHitFlag() const { return _hitFlag; }

            void SetStateManage(std::unique_ptr<GlassHeart::State::StateManager> state);
            void SetModelManage(std::unique_ptr<GlassHeart::Model::ModelAnimeManager> model);
            void SetCameraManage(std::shared_ptr<GlassHeart::Camera::CameraManager> camera);

            GlassHeart::State::StateManager& GetStateManage() { return *_stateManage; }
            GlassHeart::Collision::CollisionManager& GetCollision() { return *_collsionManage; }
            GlassHeart::Camera::CameraManager& GetCamera() { return *_cameraManage; }
            GlassHeart::Model::ModelAnimeManager& GetModelAnime() { return *_modelAnimeManage; }
            ObjectServer& GetObjectServer();
        protected:
            GameMain& _game; //!< �Q�[�����C���N���X�̎Q��

            ObjectState GetObjectState() const { return _objectState; }
            void SetObjectState(ObjectState objstate) { _objectState = objstate; }
            ObjectState _objectState{ ObjectState::Active };

            std::unique_ptr<GlassHeart::State::StateManager> _stateManage;  //!< �X�e�[�g�}�l�[�W���[�̃��j�[�N�|�C���^
            std::shared_ptr<GlassHeart::Collision::CollisionManager> _collsionManage;  //!< �R���W�����̃V�F�A�[�h�|�C���^
            std::shared_ptr<GlassHeart::Camera::CameraManager> _cameraManage;  //!< �J�����̃V�F�A�[�h�|�C���^
            std::unique_ptr<GlassHeart::Model::ModelAnimeManager> _modelAnimeManage; //!< ���f���A�j���}�l�[�W���[�̃��j�[�N�|�C���^

            MATRIX _worldTransform{ MGetIdent() }; //!< ���[���h���W�ϊ�
            VECTOR _position{ 0, 0, 0 };  //!< �ʒu���
            VECTOR _rotation{ 0, 0, 0 };  //!< �p�x
            VECTOR _scale{ 1, 1, 1 };     //!< �g�嗦

            float _radius{ 0.0f };  //!< �R���W�����p���a
            bool _hitFlag{ false }; //!< �R���W�����p�t���O
        };
    }
}


