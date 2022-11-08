/*****************************************************************//**
 * @file   Player.cpp
 * @brief  プレイヤーの処理
 *
 * @author Hayato Imai, Haruki Ikeda, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "Player.h"
#include "../Object/ObjectServer.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"

namespace {
  constexpr int_fast16_t Recast = 20;                       //!< 色変更リキャストタイム
  constexpr int_fast16_t DeathCoolTime = 120;               //!< 死亡した時の復活までのクールタイム
  constexpr VECTOR PlayerPosition  = { -150.0f, 40.0f, -55.0f };  //!< プレイヤーの位置座標
  constexpr VECTOR LineLength = { 0.0f, -10.0f, 0.0f };     //!< 当たり判定に使用する線分の長さ
  constexpr auto Hit = 1;                                   //!< ヒットしたかのフラグ
  constexpr auto Radius = 20.f;                             //!< チェックポイントとの当たり判定用半径
  constexpr auto RespawnArea = -300.0f;                     //!< リスポーンエリア
  constexpr auto ObjectToRegister = "Player";               //!< オブジェクトを管理するマネージャーに登録する文字列
  constexpr auto DeathSoundeffect = "death";                //!< 再生するSE
  constexpr auto CheckPoint = "CheckPoint";                 //!< 
  constexpr auto Fall = "Fall";                             //!<
  constexpr auto White = "White";                           //!<
  constexpr auto Black = "Black";                           //!<
}

/** コンストラクタ */
GlassHeart::Player::Player::Player(Application::GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
  auto right = RightRotation();
  _rotation = VGet(0.0f, right, 0.0f);
  _position = PlayerPosition;
  _radius = Radius;  // チェックポイントとの当たり判定用半径をセット
}
/** 入力処理 */
void GlassHeart::Player::Player::Input(AppFrame::Input::InputManager& input) {
  if (_deadFlag == false) {
    // カメラの更新
    _cameraManage->Input(input);
    // ステートの更新
    _stateManage->Input(input);
  }
  //LBボタンを押すと色変更
  if (input.GetJoyPad().GetXinputLeftShoulder() && _recastCount == 0) {
    //連打防止のため20フレーム間入力を制限
    ColorChange();
    _recastCount = Recast;
  }
#ifdef _DEBUG
  // デバッグ用LBボタンを押すとプレイヤーの位置を初期化
  if (input.GetJoyPad().GetXinputRightShoulder()) {
    auto right = RightRotation();
    _rotation = VGet(0.0f, right, 0.0f);
    _position = Position;
  }
#endif // _DEBUG
}
/** 更新処理 */
void GlassHeart::Player::Player::Process() {
  // 入力制限の為カウンタを減少
  if (_recastCount > 0) {
    --_recastCount;
  }
  if (_deathCoolCount > 0) {
    --_deathCoolCount;
  }
  // 色ごとの衝突判定
  CollisionDetectionByColor();

  if (_deadFlag == false) {
    // 状態の更新
    _stateManage->Update();
    // ワールド行列の更新
    ComputeWorldTransform();
    // モデルアニメーションの更新
    _modelAnimeManage->Update();
  }
  // オブジェクトサーバーに位置を送信
  GetObjectServer().Register(ObjectToRegister, _position);
  // チェックポイントとの衝突判定
  IsHitCheckPoint();
#ifdef _DEBUG
  if (_position.y < RespawnArea) {
    if (_checkPointFlag == true) {
      // オブジェクトサーバーからチェックポイントの座標を取得
      auto checkPos = GetObjectServer().GetPosition(CheckPoint);
      // プレイヤーの座標をチェックポイントの座標にする
      _position = checkPos;
    }
    else {
      _position = PlayerPosition;
    }
  }
#endif // DEBUG
}
/** 描画処理 */
void GlassHeart::Player::Player::Render() {
  // ステートの更新
  _stateManage->Draw();
#ifdef _DEBUG
  // デバッグ用 プレイヤーの座標を表示
  auto x = 0; auto y = 0; auto size = 32;
  auto i = 0; auto o = 32 * 6; auto timeY = 32 * 10;
  auto white = GetColor(255, 255, 255);

  SetFontSize(size);
  DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーX座標 =  %.3f ", _position.x); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーY座標 =  %.3f ", _position.y); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーZ座標 =  %.3f ", _position.z); y += size;
  // 色状態を表示
  DrawFormatString(i, o, GetColor(255, 255, 255), _stateName.c_str(), _colorState); y += size;
#endif // _DEBUG
}
/** ワールド座標変換 */
void GlassHeart::Player::Player::ComputeWorldTransform() {
  auto world = MGetScale(_scale);
  world = MMult(world, MGetRotZ(_rotation.z));
  world = MMult(world, MGetRotX(_rotation.x));
  world = MMult(world, MGetRotY(_rotation.y + DX_PI_F)); // モデルの向きはここで調整
  _worldTransform = MMult(world, MGetTranslate(_position));
}
/** 移動処理 */
void GlassHeart::Player::Player::Move(const VECTOR& forward) {
  auto pos = _position;
  // プレイヤーの色を取得
  auto state = static_cast<int_fast16_t> (_colorState);
  // 空中の足場の底面と側面判定処理
  pos = _collsionManage->GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
  // 床との当たり判定
  pos = _collsionManage->GetIsHitFloor().CheckHitFloor(pos, LineLength, state);
  // 死亡判定を取るメッシュと当たり判定
  pos = _collsionManage->GetIsHitBDeathMesh().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
  // 死亡判定を取るメッシュと当たり判定
  pos = _collsionManage->GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
  // 足場と底面と側面に当たっていなかったら落下状態へ移行
  if (_collsionManage->GetIsHitFloor().GetHitFloor().HitFlag == 0 && 
    _collsionManage->GetIsHitSideBottom().GetSideAndBottom().HitNum == 0) {
    GetStateManage().GoToState(Fall);
  }
  // 座標更新
  _position = pos;
}
/** 色変更処理 */
void GlassHeart::Player::Player::ColorChange() {
  if (_colorState == ColourState::Black) {
    SetWhite();
  }
  else if (_colorState == ColourState::White) {
    SetBlack();
  }
}
/** 白に設定 */
void GlassHeart::Player::Player::SetWhite() {
  auto animHandle = _modelAnimeManage->GetHandle();
  _stateName = White;
  MV1SetFrameVisible(animHandle, 0, FALSE);
  MV1SetFrameVisible(animHandle, 1, TRUE);
  MV1SetFrameVisible(animHandle, 2, FALSE);
  MV1SetFrameVisible(animHandle, 3, TRUE);
  _colorState = ColourState::White;
}
/** 黒に設定 */
void GlassHeart::Player::Player::SetBlack() {
  auto animHandle = _modelAnimeManage->GetHandle();
  _stateName = Black;
  MV1SetFrameVisible(animHandle, 1, FALSE);
  MV1SetFrameVisible(animHandle, 0, TRUE);
  MV1SetFrameVisible(animHandle, 3, FALSE);
  MV1SetFrameVisible(animHandle, 2, TRUE);
  _colorState = ColourState::Black;
}
/** リスポーンシステム */
void GlassHeart::Player::Player::ResetPos() {
  // 白いデスメッシュと当たっていたら
  if (_collsionManage->GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    if (_deadFlag == false) {
      // 死亡時の効果音を再生
      GetGame().GetSoundManager().Play(DeathSoundeffect);
      _deadFlag = true;
      _deathCoolCount = DeathCoolTime;
    }
    // チェックポイントと当たっていたらプレイヤーの座標をチェックポイントの位置にする
    if (_checkPointFlag == true) {
      if (_deadFlag == true && _deathCoolCount == 0) {
        // オブジェクトサーバーからチェックポイントの座標を取得
        auto checkPos = GetObjectServer().GetPosition(CheckPoint);
        // プレイヤーの座標をチェックポイントの座標にする
        _position = checkPos;
        _deadFlag = false;
      }
    }
    else {
      // チェックポイントと当たっていなかったら初期位置に戻す
      if (_deadFlag == true && _deathCoolCount == 0) {
        _position = PlayerPosition;
        _deadFlag = false;
      }
    }
  }
  // 黒いデスメッシュと当たっていたら
  if (_collsionManage->GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    if (_deadFlag == false) {
      // 死亡時の効果音を再生
      GetGame().GetSoundManager().Play(DeathSoundeffect);
      _deadFlag = true;
      _deathCoolCount = DeathCoolTime;
    }
    // チェックポイントと当たっていたらプレイヤーの座標をチェックポイントの位置にする
    if (_checkPointFlag == true) {
      if (_deadFlag == true && _deathCoolCount == 0) {
        // オブジェクトサーバーからチェックポイントの座標を取得
        auto checkPos = GetObjectServer().GetPosition(CheckPoint);
        // プレイヤーの座標をチェックポイントの座標にする
        _position = checkPos;
        _deadFlag = false;
      }
    }
    else {
      // チェックポイントと当たっていなかったら初期位置に戻す
      if (_deadFlag == true && _deathCoolCount == 0) {
        _position = PlayerPosition;
        _deadFlag = false;
      }
    }
  }
}

void GlassHeart::Player::Player::CollisionDetectionByColor() {
  // 白いデスメッシュと当たっていたら
  if (GetCollision().GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    // 同じ色ならば位置はそのままにする
    if (GetColourState() == Player::Player::ColourState::White) {
      SetPosition(_position);
    }
    // 違う色ならば位置をリセットする
    if (GetColourState() == Player::Player::ColourState::Black) {
      ResetPos();
    }
  }
  // 黒いデスメッシュと当たっていたら
  if (GetCollision().GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    // 違う色ならば位置をリセットする
    if (GetColourState() == Player::Player::ColourState::White) {
      ResetPos();
    }
    // 同じ色ならば位置はそのままにする
    if (GetColourState() == Player::Player::ColourState::Black) {
      SetPosition(_position);
    }
  }
}

void GlassHeart::Player::Player::IsHitCheckPoint() {
  // チェックポイントとの当たり判定
  for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ++ite) {
    // オブジェクトタイプがチェックポイントだったら
    if ((*ite)->GetObjectType() == ObjectBase::ObjectType::CheckPoint) {
      // 円形と円形の当たり判定(当たったらtrueを返す)
      if (_collsionManage->GetIsHitCircle().CheckCircleToCircle(*this, **ite) == true) {
        // 当たった
        _hitFlag = true;
        _checkPointFlag = true;
      }
      else {
        // 当たらなかった
        _hitFlag = false;
      }
    }
  }
}
