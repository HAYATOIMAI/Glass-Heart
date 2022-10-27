/*****************************************************************//**
 * @file   CreateBase.h
 * @brief  ObjectFactoryに登録するクリエーターの基底クラス
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <memory>
#include "ObjectBase.h"
#include "../Application/GameMain.h"

namespace GlassHeart {
  namespace Object {
    /**
     * @class CreateBase
     * @brief クリエーターはこのクラスを継承して作成する
     */
    class CreateBase {
    public:
      virtual ~CreateBase() = default;
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game) = 0;
    };
  }
}