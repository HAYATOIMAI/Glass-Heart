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
     * @brief �S�[���n�_�̃N���G�[�^�[
     */
    class GoalPointCreate : public CreateBase {
    public:
      /**
       * @brief          �S�[���n�_���쐬
       * 
       * @param[in] game �Q�[�����C���N���X�̎Q��
       * @return         �S�[���n�_�̃C���X�^���X
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}