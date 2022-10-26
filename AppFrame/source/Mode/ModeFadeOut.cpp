/*********************************************************************
 * @file   ModeFadeOut.cpp
 * @brief  �t�F�[�h�A�E�g�N���X�̏���
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#include "ModeFadeOut.h"
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
    ModeFadeOut::ModeFadeOut(GameBase& game) : ModeFade{ game } {}
    /** �f�X�g���N�^ */
    ModeFadeOut::~ModeFadeOut() {}
    /** ��������� */
    void ModeFadeOut::Enter() {
      _alpha = AlphaMin;
      _deltaAlpha = AlphaDelta;
    }
    /** �X�V���� */
    void ModeFadeOut::Process() {
      _alpha += _deltaAlpha;
      if (_alpha >= AlphaMax) {
        _alpha = AlphaMax;
        GetModeServer().PopBack(); // FadeOut���g���|�b�v�o�b�N
        GetModeServer().PopBack(); // FadeOut���̃V�[�����ꏏ�Ƀ|�b�v�o�b�N
      }
    }
  } // namespace Mode
} // namespace AppFrame 