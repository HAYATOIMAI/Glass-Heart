/*********************************************************************
 * @file   ModeLoading.cpp
 * @brief  ���[�f�B���O��ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   March 2022
 *********************************************************************/
#include "ModeLoading.h"
#include <AppFrame.h>

namespace {
  constexpr int_fast16_t LoadingTime = 30;          //!< ���[�h����
  constexpr int_fast16_t LoadingCount= 60;          //!< ���[�h���I����Ă��Ȃ������ꍇ�̍ă��[�h����
  constexpr int_fast16_t RenderingPositionX = 1700; //!< Gif�摜�̕`��ʒu
  constexpr int_fast16_t RenderingPositionY = 900;  //!< Gif�摜�̕`��ʒu
  constexpr auto Stage = "Stage";                   //!< ���\�[�X�}�l�[�W���[����Ăяo��������
  constexpr auto NextMode = "InGame";               //!< �J�ڂ��郂�[�h�̕�����
}

 /** �R���X�g���N�^ */
GlassHeart::Mode::ModeLoading::ModeLoading(Application::GameMain& game) : ModeMain(game) {}
/** ���������� */
void GlassHeart::Mode::ModeLoading::Init() {
  _loadHandle = LoadGraph("resource/Loading/LoadGraphHeart.gif");
  _cnt = LoadingTime;
}
/** ��������� */
void GlassHeart::Mode::ModeLoading::Enter() {}
/**  ���͏��� */
void GlassHeart::Mode::ModeLoading::Input(AppFrame::Input::InputManager& input) {}
/** �X�V���� */
void GlassHeart::Mode::ModeLoading::Process() {
  // ���[�h�̂��߂̃J�E���^������
  if (_cnt > 0) {
    --_cnt;
  }
  auto [handle, no] = GetGame().GetResourceServer().GetModles(Stage);
  if (_cnt == 0) {
    // �񓯊��ǂݍ��݂��I�����Ă��邩
    // FALSE�Ȃ�I���A����ȊO�Ȃ�ǂݍ��݂��ĊJ
    if (CheckHandleASyncLoad(handle) == FALSE) {
      // �񓯊��ǂݍ��ݏI��
      SetUseASyncLoadFlag(FALSE);
      // �Q�[���{�҂ֈړ�
      GetModeServer().GoToMode(NextMode);
    }
    else {
      _cnt = LoadingCount;
    }
  }
}
/** �`�揈�� */
void GlassHeart::Mode::ModeLoading::Render() {
  PlayMovieToGraph(_loadHandle);
  DrawGraph(RenderingPositionX, RenderingPositionY, _loadHandle, FALSE);
}

void GlassHeart::Mode::ModeLoading::Exit() {
  DeleteGraph(_loadHandle);
}