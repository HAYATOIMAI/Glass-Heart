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
     * @class GirlCreate
     * @brief ガール用のクリエイター
     */
    class GirlCreate : public CreateBase {
    public:
      /**
       * @brief          ガールを生成
       * 
       * @param[in] game ゲームメインクラスの参照
       * @return         ガールのインスタンス
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}