/*****************************************************************//**
 * @file   ModelManager.cpp
 * @brief  モデルマネージャークラスの処理
 *
 * @author Hayato Imai,Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#include "ModelManager.h"
#include "AppFrame.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

/** コンストラクタ */
GlassHeart::Model::ModelManager::ModelManager(Object::ObjectBase& owner) : _owner{ owner } {}
/** デストラクタ */
GlassHeart::Model::ModelManager::~ModelManager() {}
/** 初期化 */
void  GlassHeart::Model::ModelManager::Init() {}
/** 更新処理 */
void  GlassHeart::Model::ModelManager::Update() {
    // ワールド行列更新
    MV1SetMatrix(_handle, _owner.GetWorldTransform());
}
/** 描画処理 */
void GlassHeart::Model::ModelManager::Draw() {
    SetUseLighting(_isLighting);
    MV1DrawModel(_handle);
}
/** モデルの取得 */
int  GlassHeart::Model::ModelManager::handle(std::string_view key, int no) {
    auto&& [handle, actualNo] = _owner.GetGame().GetResourceServer().GetModles(key, no);
    _handle = handle;
    _key = key;
    return 0;
}
/** モデルの設定 */
int  GlassHeart::Model::ModelManager::SetModel(std::string_view key, int no) {
    auto [handle, actualNo] = _owner.GetGame().GetResourceServer().GetModles(key, no);
    _handle = handle;
    return actualNo;
}
/** 座標の設定 */
void  GlassHeart::Model::ModelManager::SetPosition(VECTOR position) {
    MV1SetPosition(_handle, position);
}
/** 回転角度の設定 */
void  GlassHeart::Model::ModelManager::SetRotation(VECTOR rotation) {
    MV1SetRotationXYZ(_handle, rotation);
}
/** 拡大率の設定 */
void  GlassHeart::Model::ModelManager::SetScale(VECTOR scale) {
    MV1SetScale(_handle, scale);
}
/** ワールド行列の設定 */
void  GlassHeart::Model::ModelManager::SetMatrix(MATRIX& world) {
    MV1SetMatrix(_handle, world);
}
/** 色を設定 */
void  GlassHeart::Model::ModelManager::SetColor(int index, float r, float g, float b) {
    MV1SetMaterialEmiColor(_handle, index, GetColorF(r, g, b, 0.f));
}