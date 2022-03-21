
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
    namespace UI {
        class UI;
    }
    namespace Effect {
        class EffectManager;
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
                Girl,
                Camera,
                Stage,
                CheckPoint,
                GoalPoint,
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
            inline bool IsDead() { return (_objectState == ObjectState::Dead); }
            /**
             * @brief ������ԂɂȂ��Ă��邩
             *
             * @return  �I�u�W�F�N�g�̏��
             */
            inline bool IsActive() { return (_objectState == ObjectState::Active); }

            inline GameMain& GetGame() { return _game; }
            /**
             * @brief ���[���h���W�ϊ�
             *
             */
            virtual void ComputeWorldTransform();
            inline const MATRIX& GetWorldTransform() const { return _worldTransform; }
            inline VECTOR GetForward() const { return VTransform({ 0, 0, 1 }, MGetRotY(_rotation.y)); }

            inline void SetPosition(const VECTOR& position) { _position = position; }
            inline VECTOR GetPosition() const { return _position; }
            inline void SetRotation(const VECTOR& rotation) { _rotation = rotation; }
            inline VECTOR GetRotation() const { return _rotation; }
            inline void SetScale(const VECTOR& scale) { _scale = scale; }
            inline VECTOR GetScale() const { return _scale; }

            inline void SetRadius(const float radius) { _radius = radius; }
            inline float GetRadius() const { return _radius; }

            inline void SetHitFlag(const bool hitFlag) { _hitFlag = hitFlag; }
            inline bool GetHitFlag() const { return _hitFlag; }
            inline bool GetDeadFlag() { return _deadFlag; }

            void SetStateManage(std::unique_ptr<State::StateManager> state);
            void SetModelManage(std::unique_ptr<Model::ModelAnimeManager> model);
            void SetCameraManage(std::shared_ptr<Camera::CameraManager> camera);
            void SetEffectManage(std::unique_ptr<GlassHeart::Effect::EffectManager> effect);

            inline State::StateManager& GetStateManage() { return *_stateManage; }
            inline Collision::CollisionManager& GetCollision() { return *_collsionManage; }
            inline Camera::CameraManager& GetCamera() { return *_cameraManage; }
            inline Model::ModelAnimeManager& GetModelAnime() { return *_modelAnimeManage; }
            ObjectServer& GetObjectServer();
        protected:
            GameMain& _game; //!< �Q�[�����C���N���X�̎Q��

            inline ObjectState GetObjectState() const { return _objectState; }
            inline void SetObjectState(ObjectState objstate) { _objectState = objstate; }
            ObjectState _objectState{ ObjectState::Active };

            std::unique_ptr<State::StateManager> _stateManage;  //!< �X�e�[�g�}�l�[�W���[�̃��j�[�N�|�C���^
            std::shared_ptr<Collision::CollisionManager> _collsionManage;  //!< �R���W�����̃V�F�A�[�h�|�C���^
            std::shared_ptr<Camera::CameraManager> _cameraManage;  //!< �J�����̃V�F�A�[�h�|�C���^
            std::unique_ptr<Model::ModelAnimeManager> _modelAnimeManage; //!< ���f���A�j���}�l�[�W���[�̃��j�[�N�|�C���^
            std::unique_ptr<Effect::EffectManager> _effectManage;  //!< �G�t�F�N�g�Ǘ��N���X�̃��j�[�N�|�C���^

            MATRIX _worldTransform{ MGetIdent() }; //!< ���[���h���W�ϊ�
            VECTOR _position{ 0, 0, 0 };  //!< �ʒu���
            VECTOR _rotation{ 0, 0, 0 };  //!< �p�x
            VECTOR _scale{ 1, 1, 1 };     //!< �g�嗦

            float _radius{ 0.0f };  //!< �R���W�����p���a
            bool _hitFlag{ false }; //!< �R���W�����p�t���O
            bool _deadFlag{ false };    //!<���S�������̃t���O
        };
    } // Object
} // GlassHeart


