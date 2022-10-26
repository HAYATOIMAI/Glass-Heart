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
     * @class PlayerCreate
     * @brief プレイヤー用のクリエイター
     */
    class PlayerCreate : public CreateBase {
    public:
      /**
       * @brief          プレイヤーの生成
       * 
       * @param[in] game ゲームメインクラスの参照
       * @return         プレイヤーのインスタンス
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}