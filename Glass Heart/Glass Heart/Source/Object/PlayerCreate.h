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
     * @brief �v���C���[�p�̃N���G�C�^�[
     */
    class PlayerCreate : public CreateBase {
    public:
      /**
       * @brief          �v���C���[�̐���
       * 
       * @param[in] game �Q�[�����C���N���X�̎Q��
       * @return         �v���C���[�̃C���X�^���X
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}