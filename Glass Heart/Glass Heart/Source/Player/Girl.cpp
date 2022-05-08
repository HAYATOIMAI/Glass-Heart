/*********************************************************************
 * @file   Girl.cpp
 * @brief  �K�[���̏���
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#include "Girl.h"
#include <numbers>
#include "../Object/ObjectServer.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"

namespace {
    constexpr auto GirlPositionX = 25830.0f;  //!< �K�[���̈ʒuX
    constexpr auto GirlPositionY = 12410.0f;   //!< �K�[���̈ʒuY
    constexpr auto GirlPositionZ = 30.0f;     //!< �K�[���̈ʒuZ
}

using namespace GlassHeart::Player;

/** �R���X�g���N�^ */
Girl::Girl(Application::GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _rotation = VGet(0.0f, 180.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
    _position = VGet(GirlPositionX, GirlPositionY, GirlPositionZ);
}
/** ���͏��� */
void Girl::Input(AppFrame::Input::InputManager& input) {}

/** �X�V���� */
void Girl::Process() {
    _stateManage->Update();
    ComputeWorldTransform();
    _modelAnimeManage->Update();
    GetObjectServer().Register("Girl", _position);
}
/** �`�揈�� */
void Girl::Render() {
    _stateManage->Draw();
}
/** ���[���h���W�ϊ� */
void Girl::ComputeWorldTransform() {
    auto world = MGetScale(_scale);
    world = MMult(world, MGetRotZ(_rotation.z));
    world = MMult(world, MGetRotX(_rotation.x));
    world = MMult(world, MGetRotY(_rotation.y + std::numbers::pi_v<float>));
    _worldTransform = MMult(world, MGetTranslate(_position));
}
/** �`�揈�� */
void Girl::StateBase::Draw() {
    _owner.GetModelAnime().Draw();
}
/** �ҋ@��� */
void Girl::StateWait::Enter() {
    _owner.GetModelAnime().ChangeAnime("PC3_wait", true);
}