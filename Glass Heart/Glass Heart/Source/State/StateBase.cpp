
/*****************************************************************//**
 * @file   StateBase.cpp
 * @brief  プレイヤーの状態の基底クラス
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateBase.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"

using namespace GlassHeart;
/** 描画処理 */
void State::StateBase::Draw() {
    MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), 4, FALSE);
    MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), 5, FALSE);
    _owner.GetModelAnime().Draw();
}
