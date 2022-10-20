/*****************************************************************//**
 * @file   IsHitJumpStand.h
 * @brief  ジャンプした際の床との当たり判定の宣言
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <memory>
#include <cstdint>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    class IsHitJumpStand {
    public:
      /**
       * @ コンストラクタ
       *
       * @param[in] owner 親クラスへの参照
       */
      IsHitJumpStand(Object::ObjectBase& owner);
      /**
       * @brief 空中の足場との当たり判定
       *
       * @param[in] pos 位置ベクトル
       * @param[in] forward  移動量ベクトル
       * @return  位置ベクトル
       */
      VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward, const std::uint_fast8_t state);

      inline MV1_COLL_RESULT_POLY GetStand()    { return _stand; }
      inline MV1_COLL_RESULT_POLY GetWThrough() { return _wThrough; }
      inline MV1_COLL_RESULT_POLY GetBThrough() { return _bThrough; }
    private:
      Object::ObjectBase& _owner;      //!< 親クラスへの参照
      MV1_COLL_RESULT_POLY _stand;     //!< ジャンプ用床との当たり判定変数
      MV1_COLL_RESULT_POLY _wThrough;  //!< 白い床との当たり判定用変数
      MV1_COLL_RESULT_POLY _bThrough;  //!< 黒い床との当たり判定用変数
    };
  }
}