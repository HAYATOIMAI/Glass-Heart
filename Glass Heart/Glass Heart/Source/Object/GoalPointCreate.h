#pragma once
#include "CreateBase.h"
#include <memory>

namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Object{
    class ObjectBase;
    /**
     * @class GoalPointCreate 
     * @brief ゴール地点のクリエーター
     */
    class GoalPointCreate : public CreateBase {
    public:
      /**
       * @brief          ゴール地点を作成
       * 
       * @param[in] game ゲームメインクラスの参照
       * @return         ゴール地点のインスタンス
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}