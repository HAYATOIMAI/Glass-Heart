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
     * @class FollowCameraCreate
     * @brief �t�H���[�J�����p�̃N���G�C�^�[
     */
    class FollowCameraCreate : public CreateBase {
    public:
      /**
       * @brief          �t�H���[�J�����𐶐�
       * 
       * @param[in] game �Q�[�����C���N���X�̎Q��
       * @return         �t�H���[�J�����̃C���X�^���X
       */
      std::unique_ptr<ObjectBase> Create(Application::GameMain& game) override;
    };
  }
}