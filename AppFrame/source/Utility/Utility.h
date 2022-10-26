/*********************************************************************
 * @file   Utility.h
 * @brief 便利な関数群
 *
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#pragma once
#include "Singleton.h"
#include <random>
#include <cstdint>
#ifdef _DEBUG
 // メモリリーク検出用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define NEW new
#endif
/**
 * @namespace AppFrame
 * @brief     アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @namespace  Utility
   * @brief      便利な関数関係
   */
  namespace Utility {
    /**
     * @class Utility
     * @brief 便利な関数群
     */
    class Utility : public Singleton<Utility> {
    private:
      /**
       * @brief         コンストラクタ
       */
      Utility();
      /**
       * @brief         デストラクタ
       */
      ~Utility() override {};
    public:
      friend class Singleton<Utility>;  // インスタンス生成を許可
      /**
       * @brief         一様整数分布の乱数を生成
       *
       * @param[in] min 最小値
       * @param[in] max 最大値
       * @return        生成された乱数
       */
      static std::int_fast32_t GetRandom(const std::int_fast32_t min, const std::int_fast32_t max);
      /**
       * @brief         メモリリーク検出
       */
      static void CheckMemoryLeak();
    };
  } // namespace Utility
} // namespace AppFrame