
/*****************************************************************//**
 * @file   GameBase.h
 * @brief  �A�v���P�[�V�����̊��N���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <DxLib.h>
#include <EffekseerForDXLib.h>

namespace AppFrame {
    /** ��d�C���N���[�h�h�~ */
    class ResourceServer;
    class InputManager;
    class SoundManager;
    class ModeServer;
    /**
     * @class GameBase
     * @brief �A�v���P�[�V�����̊��N���X�̐錾
     */
    class GameBase {
    public:
        /**
         * @enumclass  Enum
         * @brief �Q�[���̏��
         */
        enum class GameState {
            Active,  //!< �A�N�e�B�u
            Pause,   //!< ���f
            End      //!< �I��
        };
        /**
         * @brief �R���X�g���N�^
         *
         */
        GameBase();
        /**
         * @brief �f�X�g���N�^
         *
         */
        virtual ~GameBase();
        /**
         * @brief  ����������
         *
         * @return �����������̉�
         */
        virtual bool Initialize(HINSTANCE hInstance);
        /**
         * @brief  �������
         *
         */
        virtual void Terminate();
        /**
         * @brief �X�V����
         *
         */
        virtual void Process();
        /**
         * @brief �`�揈��
         *
         */
        virtual void Render();
        /**
         * @brief ���͏���
         *
         */
        virtual void Input();
        /**
         * @brief ���C�����[�v
         *
         */
        virtual void Run();

        inline ModeServer& GetModeServer() const { return *_modeServer; }

        inline ResourceServer& GetResourceServer()	const { return *_resServer; }

        inline SoundManager& GetSoundManager()	const { return *_soundManage; }

        inline static GameBase* GameInstance() { return _gameInstance; }

    protected:
        static GameBase* _gameInstance;              //!< �Q�[���x�[�X�N���X�̃C���X�^���X
        GameState _gameState{ GameState::Active };   //!< �Q�[���̏��
        std::unique_ptr<ModeServer> _modeServer;     //!< ���[�h�T�[�o�[�̃��j�[�N�|�C���^
        std::unique_ptr<ResourceServer> _resServer;  //!< ���\�[�X�T�[�o�[�̃��j�[�N�|�C���^
        std::unique_ptr<InputManager> _inputManage;  //!< �C���v�b�g�}�l�[�W���[�̃��j�[�N�|�C���^
        std::unique_ptr<SoundManager> _soundManage;  //!< �T�E���h�}�l�[�W���[�̃��j�[�N�|�C���^
    };
} //AppFrame