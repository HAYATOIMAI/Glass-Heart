
/*****************************************************************//**
 * @file   StateBase.cpp
 * @brief  ó‘Ô‚ÌŠî’êƒNƒ‰ƒX
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateBase.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"

using namespace GlassHeart::State;

void StateBase::Draw() {
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), 16, FALSE);
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), 17, FALSE);
	_owner.GetModelAnime().Draw();
}
