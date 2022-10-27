/*********************************************************************
 * @file   Singleton.h
 * @brief  シングルトンパターン
 *
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#pragma once
 /**
  * @namespace AppFrame
  * @brief  アプリケーションフレーム
  */
namespace AppFrame {
  template<class T>
  /**
   * @class Singleton
   * @brief シングルトンパターン
   */
  class Singleton {
  protected:
    /**
     * @brief 外部のインスタンス生成は禁止
     */
    Singleton() {};
    virtual ~Singleton() {};
  public:
    static inline T& GetInstance() {
      static T instance;
      return instance;
    }
  private:
    /**
     * @brief 代入演算子禁止
     */
    void operator=(const Singleton& obj) {};
    /**
     * @brief コピーコンストラクタ禁止
     */
    Singleton(const Singleton& obj) {};
  };
} // namespace AppFrame