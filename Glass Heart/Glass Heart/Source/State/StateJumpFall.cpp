
/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  �v���C���[�̗������
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateJumpFall.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include <numbers>

namespace {
    constexpr auto StraifVector = 3.0f; // �X�g���C�t�pX���ړ���
    constexpr auto Gravity = -0.2f;  //!< �d�͉����x
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;

State::StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void State::StateJumpFall::Enter() {
    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
    auto& game = _owner.GetGame();
    game.GetSoundManager().StopSound("run");
}

void State::StateJumpFall::Input(AppFrame::InputManager& input) {
    _owner.SetForwardSpeed(0.f);
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000 && input.GetJoyPad().GetAnalogStickLX() > 1) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
        _owner.SetForwardSpeed(StraifVector);
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= -5000 && input.GetJoyPad().GetAnalogStickLX() < 1) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
        _owner.SetForwardSpeed(StraifVector);
    }
}
/** �X�V���� */
void State::StateJumpFall::Update() {
    // ���͐����̈׃J�E���^������
    if (_cnt > 0) {
        --_cnt;
    }

    auto pos = _owner.GetPosition();

    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;
    _owner.SetJumpVelocity(jumpVelocity);

    forward.y = jumpVelocity.y;

    int state = static_cast<int> (_owner.GetColourState());
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);

    pos = _owner.GetCollision().CheckJumpStand(pos, { 0.f, forward.y, 0.f }, state);

    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        _owner.GetStateManage().GoToState("Idle");
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {

        if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
            _owner.GetStateManage().GoToState("Idle");
        }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
           _owner.GetStateManage().GoToState("Idle");
        }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
  
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
        }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        pos = _owner.GetCollision().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
  
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            // SetPosition(VGet(_position.x, _position.y, _position.z));

        }
    }

    _owner.SetPosition(pos);
}
void State::StateJumpFall::Landing() {
}