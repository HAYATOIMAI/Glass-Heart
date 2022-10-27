#pragma once
#include "CreateBase.h"
#include <memory>
namespace GlassHeart{
  namespace Application {
    class GameMain;
  }
  namespace Object {
    class ObjectBase;
    /**
     * @class StageCreate
     * @brief ステージ用のクリエイター
     */
    class StageCreate : public CreateBase {
    public:
      /**
       * @brief ステージを生成
       * 
       * @param[in] game ゲームメインクラスの参照
       * @return         ステージのインスタンス
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}