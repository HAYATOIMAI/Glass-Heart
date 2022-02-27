
/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  オブジェクトの基底クラス
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include <DxLib.h>
#include <memory>

/** 二重インクルード防止 */
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
         * @brief オブジェクトの基底クラス
         */
        class ObjectBase {
        public:
            /**
            * @brief　オブジェクトの種類
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
             * @brief オブジェクトの状態
             */
            enum class ObjectState {
                Active,
                Pause,
                Dead
            };
            /**
             * @brief コンストラクタ
             *
             * @param game ゲームメインクラスへの参照
             */
            ObjectBase(GameMain& game);
            /**
             * @brief デストラクタ
             *
             */
            virtual ~ObjectBase();
            /**
             * @brief 初期化処理
             */
            virtual	void Init() {};
            /**
             * @brief 入力処理
             * 
             * @param[in] input インプットマネージャークラスの参照
             */
            virtual	void Input(AppFrame::InputManager& input) {};
            /**
             * @brief 更新処理
             */
            virtual	void Process() {};
            /**
             * @brief 描画処理
             */
            virtual	void Render() {};
            /**
             * @brief　オブジェクトの種類を取得
             *
             * @return オブジェクトの種類
             */
            virtual ObjectType GetObjectType() const = 0;
            /**
             * @brief 死亡状態になっているか
             *
             * @return オブジェクトの状態
             */
            bool IsDead() { return (_objectState == ObjectState::Dead); }
            /**
             * @brief 生存状態になっているか
             *
             * @return  オブジェクトの状態
             */
            bool IsActive() { return (_objectState == ObjectState::Active); }

            GameMain& GetGame() { return _game; }
            /**
             * @brief ワールド座標変換
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
            GameMain& _game; //!< ゲームメインクラスの参照

            ObjectState GetObjectState() const { return _objectState; }
            void SetObjectState(ObjectState objstate) { _objectState = objstate; }
            ObjectState _objectState{ ObjectState::Active };

            std::unique_ptr<GlassHeart::State::StateManager> _stateManage;  //!< ステートマネージャーのユニークポインタ
            std::shared_ptr<GlassHeart::Collision::CollisionManager> _collsionManage;  //!< コリジョンのシェアードポインタ
            std::shared_ptr<GlassHeart::Camera::CameraManager> _cameraManage;  //!< カメラのシェアードポインタ
            std::unique_ptr<GlassHeart::Model::ModelAnimeManager> _modelAnimeManage; //!< モデルアニメマネージャーのユニークポインタ

            MATRIX _worldTransform{ MGetIdent() }; //!< ワールド座標変換
            VECTOR _position{ 0, 0, 0 };  //!< 位置情報
            VECTOR _rotation{ 0, 0, 0 };  //!< 角度
            VECTOR _scale{ 1, 1, 1 };     //!< 拡大率

            float _radius{ 0.0f };  //!< コリジョン用半径
            bool _hitFlag{ false }; //!< コリジョン用フラグ
        };
    }
}


