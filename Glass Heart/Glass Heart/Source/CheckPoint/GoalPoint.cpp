/*****************************************************************//**
 * @file   GoalPoint.cpp
 * @brief  �S�[���|�C���g�̏���
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#include "GoalPoint.h"
#include "../Application/GameMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"

namespace {
  constexpr auto GoalPositionX = 25830.0f;  //!< �S�[���̈ʒuX
  constexpr auto GoalPositionY = 12420.0f;  //!< �S�[���̈ʒuY
  constexpr auto GoalPositionZ = 30.0f;     //!< �S�[���̈ʒuZ
}
/** �R���X�g���N�^ */
GlassHeart::CheckPoint::GoalPoint::GoalPoint(Application::GameMain& game) : ObjectBase{ game } {
  _goalPoint = LoadGraph("resource/2dMaterial/light3.png");
  _position = VGet(GoalPositionX, GoalPositionY, GoalPositionZ);
  _radius = 100.0f;
  _hitFlag = false;
}
/** �X�V���� */
void GlassHeart::CheckPoint::GoalPoint::Process() {
  GetObjectServer().Register("GoalPoint", _position);

  // �S�[���|�C���g�ƃv���C���[�̓����蔻��
  for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ite++) {
    if ((*ite)->GetObjectType() == ObjectBase::ObjectType::Player) {
      if (_collsionManage->GetIsHitCircle().CheckCircleToCircle(*this, **ite) == true) {
        _hitFlag = true;
        GoToGameClear();
      }
      else {
        _hitFlag = false;
      }
    }
  }
}
/** �`�揈�� */
void GlassHeart::CheckPoint::GoalPoint::Render() {
  auto cr = GetColor(0, 0, 255);

  DrawBillboard3D(_goalDrawPos, 0.5f, 0.5f, 120.0f, 0.0f, _goalPoint, TRUE);
#ifdef _DEBUG

  auto red = GetColor(255, 0, 0);
  auto green = GetColor(0, 255, 0);

  if (_hitFlag == true) {
    _collsionManage->GetIsHitCircle().RenderCircle(_position, _radius, red);
  }
  else {
    _collsionManage->GetIsHitCircle().RenderCircle(_position, _radius, green);
  }
#endif // _DEBUG
}
/** �Q�[���N���A�֑J�ڏ��� */
void GlassHeart::CheckPoint::GoalPoint::GoToGameClear() {
  if (_hitFlag == true) {
    _game.GetModeServer().GoToMode("GameClear");
  }
}