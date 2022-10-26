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
     * @brief �X�e�[�W�p�̃N���G�C�^�[
     */
    class StageCreate : public CreateBase {
    public:
      /**
       * @brief �X�e�[�W�𐶐�
       * 
       * @param[in] game �Q�[�����C���N���X�̎Q��
       * @return         �X�e�[�W�̃C���X�^���X
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}