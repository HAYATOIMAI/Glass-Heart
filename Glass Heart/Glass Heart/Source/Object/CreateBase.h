/*****************************************************************//**
 * @file   CreateBase.h
 * @brief  ObjectFactory�ɓo�^����N���G�[�^�[�̊��N���X
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
     * @brief �N���G�[�^�[�͂��̃N���X���p�����č쐬����
     */
    class CreateBase {
    public:
      virtual ~CreateBase() = default;
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game) = 0;
    };
  }
}