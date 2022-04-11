/*****************************************************************//**
 * @file   ModeFade.h
 * @brief  ���[�h�̃t�F�[�h�N���X�錾
 *         ��ʂ̍őO�ʂɃt���X�N���[���T�C�Y�̉摜���d�˂ăA���t�@�l�ɂ��t�F�[�h���s��
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeBase.h"

namespace AppFrame {
    /**
     * @class ModeFade
     * @brief ���[�h�̃t�F�[�h�N���X�錾
     */
    class ModeFade : public ModeBase {
    public:
        /**
         * @brief �R���X�g���N�^
         *
         * @param[in] game�@�Q�[���x�[�X�N���X
         */
        ModeFade(GameBase& game);
        /**
         * @brief �f�X�g���N�^
         *
         */
        virtual ~ModeFade();
        /**
         * @brief ����������
         *
         */
        virtual void Init() override;
        /**
        * @brief ���������
        */
        virtual void Enter() override;
        /**
         * @brief �X�V����
         */
        virtual void Process() override;
        /**
         * @brief �`�揈��
         */
        virtual void Render() override;
    protected:
        int _width{ 1920 };       //!< �c��
        int _height{ 1080 };      //!< ����
        unsigned int _color{ 0 }; //!< �F���
        float _alpha{ 0 };        //!< �A���t�@�l
        float _deltaAlpha{ 0 };   //!< �A���t�@�l�Ƃ̍���
    };
    /**
     * @class ModeFadeIn
     * @brief �t�F�[�h�C���N���X�̐錾
     */
    class ModeFadeIn : public ModeFade {
    public:
        /**
         * @brief �R���X�g���N�^
         *
         * @param[in] game�@�Q�[���x�[�X�N���X
         */
        ModeFadeIn(GameBase& game);
        /**
         * @brief �f�X�g���N�^
         *
         */
        virtual ~ModeFadeIn();
        /**
        * @brief ���������
        */
        void Enter() override;
        /**
         * @brief �X�V����
         */
        void Process() override;
    };
    /**
     * @class ModeFadeOut
     * @brief �t�F�[�h�A�E�g�N���X�̐錾
     */
    class ModeFadeOut : public ModeFade {
    public:
        /**
        * @brief �R���X�g���N�^
        *
        * @param[in] game�@�Q�[���x�[�X�N���X
        */
        ModeFadeOut(GameBase& game);
        /**
         * @brief �f�X�g���N�^
         *
         */
        virtual ~ModeFadeOut();
        /**
       * @brief ���������
       */
        void Enter() override;
        /**
        * @brief �X�V����
        */
        void Process() override;
    };

} // namespace AppFrame