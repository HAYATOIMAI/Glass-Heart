#pragma once
#include "CreateBase.h"
#include <memory>

namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Object {
    class ObjectBase;
    /**
     * @class FollowCameraCreate
     * @brief フォローカメラ用のクリエイター
     */
    class FollowCameraCreate : public CreateBase {
    public:
      /**
       * @brief          フォローカメラを生成
       * 
       * @param[in] game ゲームメインクラスの参照
       * @return         フォローカメラのインスタンス
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}