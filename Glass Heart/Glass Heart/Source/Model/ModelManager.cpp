
/*****************************************************************//**
 * @file   ModelManager.cpp
 * @brief
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModelManager.h"
#include "AppFrame.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Model;

ModelManager::ModelManager(Object::ObjectBase& owner) : _owner{ owner } {}
/// �f�X�g���N�^
GlassHeart::Model::ModelManager::~ModelManager(){}
/// ������
void  GlassHeart::Model::ModelManager::Init(){}
/// �X�V����
void  GlassHeart::Model::ModelManager::Update() {
    // ���[���h�s��X�V
    MV1SetMatrix(_handle, _owner.GetWorldTransform());

    // �s��g��Ȃ��ꍇ
    //MV1SetPosition(_handle, _owner.GetPosition());
    //MV1SetRotationXYZ(_handle, _owner.GetRotation());

}
/// �`�揈��
void GlassHeart::Model::ModelManager::Draw() {
    SetUseLighting(_isLighting);
    MV1DrawModel(_handle);
}
void GlassHeart::Model::ModelManager::MeshDraw() {

    SetUseLighting(_isLighting);
    MV1DrawMesh(_handle, 0);
}
int  GlassHeart::Model::ModelManager::handle(std::string_view key, int no) {
    auto&& [handle, actualNo] = _owner.GetGame().GetResourceServer().GetModles(key, no);
    _handle = handle;
    _key = key;
    return 0;
}
/// ���f���̐ݒ�
int  GlassHeart::Model::ModelManager::SetModel(std::string_view key, int no) {
    auto [handle, actualNo] = _owner.GetGame().GetResourceServer().GetModles(key, no);
    _handle = handle;
    return actualNo;
}
/// ���W�̐ݒ�
void  GlassHeart::Model::ModelManager::SetPosition(VECTOR position) {
    MV1SetPosition(_handle, position);
}
/// ��]�p�x�̐ݒ�
void  GlassHeart::Model::ModelManager::SetRotation(VECTOR rotation) {
    MV1SetRotationXYZ(_handle, rotation);
}
/// �g�嗦�̐ݒ�
void  GlassHeart::Model::ModelManager::SetScale(VECTOR scale) {
    MV1SetScale(_handle, scale);
}
/// ���[���h�s��̐ݒ�
void  GlassHeart::Model::ModelManager::SetMatrix(MATRIX& world) {
    MV1SetMatrix(_handle, world);
}

void  GlassHeart::Model::ModelManager::SetColor(int index, float r, float g, float b) {
    MV1SetMaterialEmiColor(_handle, index, GetColorF(r, g, b, 0.f));
}