
/*****************************************************************//**
 * @file   ModeBase.h
 * @brief  ���[�h�̊��N���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>

namespace AppFrame {
    /** ��d�C���N���[�h�h�~ */
    class GameBase;
    class InputManager;
    class ResourceServer;
    class SoundManager;
    class ModeServer;
    /**
     * @class ModeBase
     * @brief ���[�h�̊��N���X
     */
    class ModeBase {
    public:
        /**
         * @brief �R���X�g���N�^
         *
         * @param[in] game�@�Q�[���x�[�X�N���X
         */
        ModeBase(GameBase& game);
        /**
         * @brief �f�X�g���N�^
         *
         */
        virtual ~ModeBase();
        /**
         * @brief ����������
         *
         */
        virtual void Init() = 0;
        /**
         * @brief ���������
         */
        virtual void Enter() {};
        /**
         * @brief ���͏���
         *
         * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
         */
        virtual void Input(InputManager& input) {};
        /**
         * @brief �X�V����
         */
        virtual void Process() {};
        /**
         * @brief �`�揈��
         */
        virtual void Render() {};
        /**
         * @brief �o������
         */
        virtual void Exit() {};

        inline GameBase& GetGame() const { return _game; };

        ResourceServer& GetResourceServer();

        SoundManager& GetSoundManager();

        ModeServer& GetModeServer();

    protected:
        GameBase& _game; //!< �Q�[���x�[�X�N���X�ւ̎Q��
    };
}