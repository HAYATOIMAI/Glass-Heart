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
#include <cstdint>

namespace {
	constexpr std::uint_fast8_t InvisibleFrame = 4;  //!< �\�����Ȃ����b�V���ԍ�
	constexpr std::uint_fast8_t CollisionMesh = 5;   //!< �\�����Ȃ������蔻�胁�b�V���ԍ�
}

 /** �`�揈�� */
void GlassHeart::State::StateBase::Draw() {
	// �s�v�ȃ��b�V�����\����
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), InvisibleFrame, FALSE);
	MV1SetFrameVisible(_owner.GetModelAnime().GetHandle(), CollisionMesh, FALSE);
	// ���f���̃A�j���[�V�������Đ�
	_owner.GetModelAnime().Draw();
}