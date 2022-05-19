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

 /** �`�揈�� */
void GlassHeart::State::StateBase::Draw() {
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), 4, FALSE);
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), 5, FALSE);
	_owner.GetModelAnime().Draw();
}