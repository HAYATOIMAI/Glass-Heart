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
     * @class CheckPointCreate
     * @brief チェックポイント用のクリエイター
     */
    class CheckPointCreate : public CreateBase {
    public:
      /**
       * @brief          チェックポイントを生成
       * 
       * @param[in] game ゲームメインクラスの参照
       * @return         チェックポイントのインスタンス
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}