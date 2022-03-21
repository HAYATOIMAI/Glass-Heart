
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

using namespace GlassHeart;

/** コンストラクタ */
State::StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {}
/** 入り口処理 */
void State::StateJump::Enter() {
    _isJump = true;

    _owner.GetModelAnime().ChangeAnime("Jump_start", true);
}
/** 入力処理 */
void State::StateJump::Input(AppFrame::InputManager& input) {}
/** 更新処理 */
void State::StateJump::Update() {
    // 対応するボタンが押されたらジャンプ処理実行
    if (_isJump == true){
        _owner.GetStateManage().PushBack("JumpUp");
        _isJump = false;
    }   
}