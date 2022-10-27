/*********************************************************************
 * @file   ModeFadeIn.cpp
 * @brief  �t�F�[�h�C���N���X�̏���
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#include "ModeFadeIn.h"
#include "ModeServer.h"
#include "../Application/GameBase.h"
#include <DxLib.h>

namespace {
  constexpr auto AlphaMin = 0.f;                      //!< �A���t�@�l�Œ�l
  constexpr auto AlphaMax = 255.f;                    //!< �A���t�@�l�ő�l
  constexpr auto FadeTime = 75.555f;                  //!< �Ó]����
  constexpr auto AlphaDelta = (AlphaMax / FadeTime);  //!< �A���t�@�l�̍���
}

namespace AppFrame {
  namespace Mode {
    /** �R���X�g���N�^ */
    ModeFadeIn::ModeFadeIn(GameBase& game) : ModeFade{ game } {}
    /** �f�X�g���N�^ */
    ModeFadeIn::~ModeFadeIn() {}
    /** ��������� */
    void ModeFadeIn::Enter() {
      _alpha = AlphaMax;
      _deltaAlpha = -AlphaDelta;
    }
    /** �X�V���� */
    void ModeFadeIn::Process() {
      _alpha += _deltaAlpha;
      if (_alpha <= AlphaMin) {
        _alpha = AlphaMin;
        GetModeServer().PopBack(); // FadeIn���g���|�b�v�o�b�N
      }
    }
  } // namespace Mode
} // namespace AppFrame 