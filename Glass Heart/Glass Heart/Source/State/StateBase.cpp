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
#include <cstdint>

namespace {
	constexpr std::uint_fast8_t InvisibleFrame = 4;  //!< 表示しないメッシュ番号
	constexpr std::uint_fast8_t CollisionMesh = 5;   //!< 表示しない当たり判定メッシュ番号
}

 /** 描画処理 */
void GlassHeart::State::StateBase::Draw() {
	// 不要なメッシュを非表示に
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), InvisibleFrame, FALSE);
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), CollisionMesh, FALSE);
	// モデルのアニメーションを再生
	_owner.GetModelAnime().Draw();
}