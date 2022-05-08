/*********************************************************************
 * @file   FollowCamera.h
 * @brief  フォローカメラクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"

namespace GlassHeart {

    namespace Camera {
        class CameraManager;
    }
    namespace Camera {
        /**
        * @class FollowCamera
        * @brief フォローカメラ
        */
        class FollowCamera : public Object::ObjectBase {
        public:
            /**
            * @brief コンストラクタ
            *
            * @param game ゲームメインクラスへの参照
            */
            FollowCamera(Application::GameMain& game);
            /**
            * @brief デストラクタ
            *
            */
            virtual ~FollowCamera() override = default;
            /**
            * @brief 更新処理
            *
            */
            void Process() override;
            /**
            * @brief 描画処理
            *
            */
            void Render() override;
            /**
            * @brief タイプの取得
            * @return タイプID
            */
            ObjectType GetObjectType() const override { return ObjectType::Camera; };
            /**
            * @brief カメラのスピード設定
            * @param[in] forwardSpeed
            * @return フォワードスピード
            */
            void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }

        protected:
            float _forwardSpeed{ 0 };
            float _angularSpeed{ 0 };
            int _waitTime{ 0 };
        };
    }
}
