/*****************************************************************//**
 * @file   IsHitFloor.h
 * @brief  床との当たり判定クラスの宣言
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <cstdint>
#include <DxLib.h>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    /**
     * @class 
     */
    class IsHitFloor {
    public:
      /**
       * @ コンストラクタ
       *
       * @param[in] owner 親クラスへの参照
       */
      IsHitFloor(Object::ObjectBase& owner);
      /**
       * @brief             床メッシュとの当たり判定
       *
       * @param[in] pos     位置ベクトル
       * @param[in] forward 移動量ベクトル
       * @return            位置ベクトル
       */
      VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward, const std::int_fast8_t state);

      inline MV1_COLL_RESULT_POLY GetHitFloor() const { return _floor; }
      inline MV1_COLL_RESULT_POLY GetWThrough() const { return _wThrough; }
      inline MV1_COLL_RESULT_POLY GetBThrough() const { return _bThrough; }
    private:
      Object::ObjectBase& _owner;      //!< 親クラスへの参照
      MV1_COLL_RESULT_POLY _floor;     //!< 床との当たり判定用変数
      MV1_COLL_RESULT_POLY _wThrough;  //!< 白い床との当たり判定用変数
      MV1_COLL_RESULT_POLY _bThrough;  //!< 黒い床との当たり判定用変数
    };
  }
}