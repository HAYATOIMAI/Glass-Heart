/*********************************************************************
 * @file   FollowCamera.h
 * @brief  フォローカメラクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Object/ObjectBase.h"

namespace GlassHeart {

    namespace Camera {
        class CameraManager;
    }

    namespace Camera {

        class FollowCamera : public Object::ObjectBase {
        public:

            FollowCamera(GameMain& game);

            ~FollowCamera();

            void Init() override;

            void Process() override;

            void Render() override;

            ObjectType GetObjectType() const override { return ObjectType::Camera; };

            void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }

        protected:
            float _forwardSpeed{ 0 };
            float _angularSpeed{ 0 };
            int _waitTime{ 0 };
        };
    }
}
