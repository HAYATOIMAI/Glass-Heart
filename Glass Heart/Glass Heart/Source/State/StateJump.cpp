
/*********************************************************************
 * @file   StateJump.cpp
 * @brief  �W�����v��ԃN���X�̏���
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJump.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"
#include <numbers>
#include <AppFrame.h>

using namespace GlassHeart::State;

/** �R���X�g���N�^ */
StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {
    _lastPosition = _owner.GetPosition();
}
/** ��������� */
void StateJump::Enter() {
    _isJump = true;

    _owner.GetModelAnime().ChangeAnime("Jump_start", true);
}
/** ���͏��� */
void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        //_owner.GetStateManage().PushBack("Run");
    }
    //if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
    //    // �E�����Ɍ�����ύX
    //    _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
    //}
    //if (input.GetJoyPad().GetAnalogStickLX() <= -5000) {
    //    // �������Ɍ�����ύX
    //    _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
    //}
}
/** �X�V���� */
void StateJump::Update() {
    // �Ή�����{�^���������ꂽ��W�����v�������s
    if (_isJump == true){
        _owner.GetStateManage().PushBack("JumpUp");
        _isJump = false;
    }   
}