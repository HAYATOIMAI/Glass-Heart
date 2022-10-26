/*********************************************************************
 * @file   ModeLoading.cpp
 * @brief  ���[�f�B���O��ʃN���X�̏���
 *
 * @author Hayato Imai
 * @date   March 2022
 *********************************************************************/
#include "ModeLoading.h"
#include <AppFrame.h>

 /** �R���X�g���N�^ */
GlassHeart::Mode::ModeLoading::ModeLoading(Application::GameMain& game) : ModeMain(game) {}
/** ���������� */
void GlassHeart::Mode::ModeLoading::Init() {
  _loadHandle = LoadGraph("resource/Loading/LoadGraphHeart.gif");
  _cnt = 30;
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
  auto [handle, no] = GetGame().GetResourceServer().GetModles("Stage");
  if (_cnt == 0) {
    // �񓯊��ǂݍ��݂��I�����Ă��邩
    // FALSE�Ȃ�I���A����ȊO�Ȃ�ǂݍ��݂��ĊJ
    if (CheckHandleASyncLoad(handle) == FALSE) {
      // �񓯊��ǂݍ��ݏI��
      SetUseASyncLoadFlag(FALSE);
      // �Q�[���{�҂ֈړ�
      GetModeServer().GoToMode("InGame");
    }
    else {
      _cnt = 60;
    }
  }
}
/** �`�揈�� */
void GlassHeart::Mode::ModeLoading::Render() {
  PlayMovieToGraph(_loadHandle);
  DrawGraph(1700, 900, _loadHandle, FALSE);
}

void GlassHeart::Mode::ModeLoading::Exit() {
  DeleteGraph(_loadHandle);
}