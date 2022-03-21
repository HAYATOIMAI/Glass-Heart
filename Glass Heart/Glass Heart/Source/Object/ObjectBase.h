
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
                Girl,
                Camera,
                Stage,
                CheckPoint,
                GoalPoint,
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
            inline bool IsDead() { return (_objectState == ObjectState::Dead); }
            /**
             * @brief 生存状態になっているか
             *
             * @return  オブジェクトの状態
             */
            inline bool IsActive() { return (_objectState == ObjectState::Active); }

            inline GameMain& GetGame() { return _game; }
            /**
             * @brief ワールド座標変換
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
            GameMain& _game; //!< ゲームメインクラスの参照

            inline ObjectState GetObjectState() const { return _objectState; }
            inline void SetObjectState(ObjectState objstate) { _objectState = objstate; }
            ObjectState _objectState{ ObjectState::Active };

            std::unique_ptr<State::StateManager> _stateManage;  //!< ステートマネージャーのユニークポインタ
            std::shared_ptr<Collision::CollisionManager> _collsionManage;  //!< コリジョンのシェアードポインタ
            std::shared_ptr<Camera::CameraManager> _cameraManage;  //!< カメラのシェアードポインタ
            std::unique_ptr<Model::ModelAnimeManager> _modelAnimeManage; //!< モデルアニメマネージャーのユニークポインタ
            std::unique_ptr<Effect::EffectManager> _effectManage;  //!< エフェクト管理クラスのユニークポインタ

            MATRIX _worldTransform{ MGetIdent() }; //!< ワールド座標変換
            VECTOR _position{ 0, 0, 0 };  //!< 位置情報
            VECTOR _rotation{ 0, 0, 0 };  //!< 角度
            VECTOR _scale{ 1, 1, 1 };     //!< 拡大率

            float _radius{ 0.0f };  //!< コリジョン用半径
            bool _hitFlag{ false }; //!< コリジョン用フラグ
            bool _deadFlag{ false };    //!<死亡したかのフラグ
        };
    } // Object
} // GlassHeart


