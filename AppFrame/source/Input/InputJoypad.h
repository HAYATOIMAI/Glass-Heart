
/*****************************************************************//**
 * @file   InputJoypad.h
 * @brief  �W���C�p�b�h�N���X�̐錾
 * 
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <utility>

namespace AppFrame {

    class InputJoypad {
    public:
        /**
         * @brief �X�V����
         */
        void Process();
        // �����L�[��
        bool GetXinputUp() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_UP]; }
        // �����L�[��
        bool GetXinputDown() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_DOWN]; }
        // �����L�[��
        bool GetXinputLeft() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_LEFT]; }
        // �����L�[�E
        bool GetXinputRight() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_RIGHT]; }
        // START�{�^��
        bool GetXinputStart() { return _xInput.Buttons[XINPUT_BUTTON_START]; }
        // BACK�{�^��
        bool GetXinputBack() { return _xInput.Buttons[XINPUT_BUTTON_BACK]; }
        // ���X�e�B�b�N��������
        bool GetXinputLeftThumb() { return _xInput.Buttons[XINPUT_BUTTON_LEFT_THUMB]; }
        // �E�X�e�B�b�N��������
        bool GetXinputRightThumb() { return _xInput.Buttons[XINPUT_BUTTON_RIGHT_THUMB]; }
        // LB�{�^��
        bool GetXinputLeftShoulder() { return _xInput.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]; }
        // RB�{�^��
        bool GetXinputRightShoulder() { return _xInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]; }
        // A�{�^��
        bool GetXinputButtonA() { return _xInput.Buttons[XINPUT_BUTTON_A]; }
        // B�{�^��
        bool GetXinputButtonB() { return _xInput.Buttons[XINPUT_BUTTON_B]; }
        // X�{�^��
        bool GetXinputButtonX() { return _xInput.Buttons[XINPUT_BUTTON_X]; }
        // Y�{�^��
        bool GetXinputButtonY() { return _xInput.Buttons[XINPUT_BUTTON_Y]; }
        // ���g���K�[
        bool GetXinputLeftTrigger() { return _xInput.LeftTrigger; }
        // �E�g���K�[
        bool GetXinputRightTrigger() { return _xInput.RightTrigger; }
        // ���X�e�B�b�N�̉����l
        bool GetXinputThumbLX() { return _xInput.ThumbLX; }
        // ���X�e�B�b�N�̏c���l
        bool GetXinputThumbLY() { return _xInput.ThumbLY; }
        // �E�X�e�B�b�N�̉����l
        bool GetXinputThumbRX() { return _xInput.ThumbRX; }
        // �E�X�e�B�b�N�̏c���l
        bool GetXinputThumbRY() { return _xInput.ThumbRY; }
        /**  ���X�e�B�b�N�̉����l */
        short GetAnalogStickLX() { return _xInput.ThumbLX; }
        /** ���X�e�B�b�N�̏c���l */
        short GetAnalogStickLY() { return _xInput.ThumbLY; }

        /** �g���K���͂��擾 */
        XINPUT_STATE& GetTrg() { return _xTrigger; }
        // �����L�[��
        bool GetXTriggerUp() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_UP]; }
        // �����L�[��
        bool GetXTriggerDown() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_DOWN]; }
        // �����L�[��
        bool GetXTriggerLeft() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_LEFT]; }
        // �����L�[�E
        bool GetXTriggerRight() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_RIGHT]; }
        // START�{�^��
        bool GetXTriggerStart() { return _xTrigger.Buttons[XINPUT_BUTTON_START]; }
        // BACK�{�^��
        bool GetXTriggerBack() { return _xTrigger.Buttons[XINPUT_BUTTON_BACK]; }
        // ���X�e�B�b�N��������
        bool GetXTriggerLeftThumb() { return _xTrigger.Buttons[XINPUT_BUTTON_LEFT_THUMB]; }
        // �E�X�e�B�b�N��������
        bool GetXTriggerRightThumb() { return _xTrigger.Buttons[XINPUT_BUTTON_RIGHT_THUMB]; }
        // LB�{�^��
        bool GetXTriggerLeftShoulder() { return _xTrigger.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]; }
        // RB�{�^��
        bool GetXTriggerRightShoulder() { return _xTrigger.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]; }
        // A�{�^��
        bool GetXTriggerButtonA() { return _xTrigger.Buttons[XINPUT_BUTTON_A]; }
        // B�{�^��
        bool GetXTriggerButtonB() { return _xTrigger.Buttons[XINPUT_BUTTON_B]; }
        // X�{�^��
        bool GetXTriggerButtonX() { return _xTrigger.Buttons[XINPUT_BUTTON_X]; }
        // Y�{�^��
        bool GetXTriggerButtonY() { return _xTrigger.Buttons[XINPUT_BUTTON_Y]; }

    private:
        int _inputInfo{ 0 };  //!< ���͏��
        int _trgInfo{ 0 };  //!< �g���K�[���͏��
        XINPUT_STATE _xInput{ 0 };  //!< XInput�p���͏��
        XINPUT_STATE _xTrigger{ 0 };  //!< XInput�p�g���K�[���͏��
        DINPUT_JOYSTATE _dInput{ 0 };  //!< DirectInput�p���͏��
        DINPUT_JOYSTATE _dTrigger{ 0 };  //!< DirectInput�p�g���K�[���͏��
    };

}
