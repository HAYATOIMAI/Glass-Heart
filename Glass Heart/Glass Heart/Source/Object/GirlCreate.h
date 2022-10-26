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
     * @brief �K�[���p�̃N���G�C�^�[
     */
    class GirlCreate : public CreateBase {
    public:
      /**
       * @brief          �K�[���𐶐�
       * 
       * @param[in] game �Q�[�����C���N���X�̎Q��
       * @return         �K�[���̃C���X�^���X
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}