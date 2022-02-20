
/*********************************************************************
 * @file   StateJump.cpp
 * @brief  ジャンプ状態クラスの処理
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

/** コンストラクタ */
StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {
    _lastPosition = _owner.GetPosition();
}
/** 入り口処理 */
void StateJump::Enter() {
    _isJump = true;

    _owner.GetModelAnime().ChangeAnime("Jump_start", true);
}
/** 入力処理 */
void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        //_owner.GetStateManage().PushBack("Run");
    }
    //if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
    //    // 右方向に向きを変更
    //    _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
    //}
    //if (input.GetJoyPad().GetAnalogStickLX() <= -5000) {
    //    // 左方向に向きを変更
    //    _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
    //}
}
/** 更新処理 */
void StateJump::Update() {
    // 対応するボタンが押されたらジャンプ処理実行
    if (_isJump == true){
        _owner.GetStateManage().PushBack("JumpUp");
        _isJump = false;
    }   
}