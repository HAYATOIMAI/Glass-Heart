/*********************************************************************
 * @file   Singleton.h
 * @brief  �V���O���g���p�^�[��
 *
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#pragma once
 /**
  * @namespace AppFrame
  * @brief  �A�v���P�[�V�����t���[��
  */
namespace AppFrame {
  template<class T>
  /**
   * @class Singleton
   * @brief �V���O���g���p�^�[��
   */
  class Singleton {
  protected:
    /**
     * @brief �O���̃C���X�^���X�����͋֎~
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
     * @brief ������Z�q�֎~
     */
    void operator=(const Singleton& obj) {};
    /**
     * @brief �R�s�[�R���X�g���N�^�֎~
     */
    Singleton(const Singleton& obj) {};
  };
} // namespace AppFrame