/*********************************************************************
 * @file   ModeFadeIn.cpp
 * @brief  �t�F�[�h�C���N���X�̏���
 *
 * @author Hayato Imai
 * @date    May 2022
 *********************************************************************/
#include "ModeFadeIn.h"
#include "ModeServer.h"
#include <DxLib.h>

namespace {
  constexpr float ALPHA_MIN = 0.f;        //!< �A���t�@�l�Œ�l
  constexpr float ALPHA_MAX = 255.f;     //!< �A���t�@�l�ő�l
  constexpr float FADE_TIME = 75.555f;  //!< �Ó]����
  constexpr float ALPHA_DELTA = (ALPHA_MAX / FADE_TIME);  //!< �A���t�@�l�̍���
}

namespace AppFrame {
  namespace Mode {
    /** �R���X�g���N�^ */
    ModeFadeIn::ModeFadeIn(GameBase& game) : ModeFade{ game } {}
    /** �f�X�g���N�^ */
    ModeFadeIn::~ModeFadeIn() {}
    /** ��������� */
    void ModeFadeIn::Enter() {
      _alpha = ALPHA_MAX;
      _deltaAlpha = -ALPHA_DELTA;
    }
    /** �X�V���� */
    void ModeFadeIn::Process() {
      _alpha += _deltaAlpha;
      if (_alpha <= ALPHA_MIN) {
        _alpha = ALPHA_MIN;
        GetModeServer().PopBack(); // FadeIn���g���|�b�v�o�b�N
      }
    }
  } // namespace Mode
} // namespace AppFrame 