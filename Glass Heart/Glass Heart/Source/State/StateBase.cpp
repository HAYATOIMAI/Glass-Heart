/*****************************************************************//**
 * @file   StateBase.cpp
 * @brief  �v���C���[�̏�Ԃ̊��N���X
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateBase.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"

namespace {
	constexpr std::uint_fast8_t InvisibleFrame = 4;
	constexpr std::uint_fast8_t CollisionMesh = 5;
}

 /** �`�揈�� */
void GlassHeart::State::StateBase::Draw() {
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), InvisibleFrame, FALSE);
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), CollisionMesh, FALSE);
	_owner.GetModelAnime().Draw();
}