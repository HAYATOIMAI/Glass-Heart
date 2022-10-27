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
     * @brief �`�F�b�N�|�C���g�p�̃N���G�C�^�[
     */
    class CheckPointCreate : public CreateBase {
    public:
      /**
       * @brief          �`�F�b�N�|�C���g�𐶐�
       * 
       * @param[in] game �Q�[�����C���N���X�̎Q��
       * @return         �`�F�b�N�|�C���g�̃C���X�^���X
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}