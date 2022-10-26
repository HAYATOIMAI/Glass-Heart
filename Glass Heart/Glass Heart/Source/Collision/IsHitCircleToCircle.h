/*****************************************************************//**
 * @file   IsHitCircleToCircle.h
 * @brief  円と円の衝突判定クラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    class IsHitCircleToCircle {
    public:
      /**
       * @ コンストラクタ
       *
       * @param[in] owner 親クラスへの参照
       */
      IsHitCircleToCircle(Object::ObjectBase& owner);
      /**
       * @brief デバッグ用当たり判定描画処理
       *
       * @param[in] circlePos 円の位置ベクトル
       * @param[in] range 範囲
       * @param[in] color 色情報
       */
      void RenderCircle(const VECTOR circlePos, float range, unsigned int color);
      /**
       * @brief 円の当たり判定
       *
       * @param[in] owner  チェックポイント
       * @param[in] target プレイヤー
       * @return 接触しているか
       */
      bool CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target);
    private:
      Object::ObjectBase& _owner;  //!< 親クラスへの参照
      float _radius1{ 0.0f };      //!< チェックポイントとの当たり判定用半径
      float _radius2{ 0.0f };      //!< チェックポイントとの当たり判定用半径
    };
  }
}