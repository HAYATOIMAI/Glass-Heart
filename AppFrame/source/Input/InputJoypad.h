
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
        bool GetXinputUp() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_UP]; }
        // �����L�[��
        bool GetXinputDown() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_DOWN]; }
        // �����L�[��
        bool GetXinputLeft() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_LEFT]; }
        // �����L�[�E
        bool GetXinputRight() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_RIGHT]; }
        // START�{�^��
        bool GetXinputStart() { return _xinput.Buttons[XINPUT_BUTTON_START]; }
        // BACK�{�^��
        bool GetXinputBack() { return _xinput.Buttons[XINPUT_BUTTON_BACK]; }
        // ���X�e�B�b�N��������
        bool GetXinputLeftThumb() { return _xinput.Buttons[XINPUT_BUTTON_LEFT_THUMB]; }
        // �E�X�e�B�b�N��������
        bool GetXinputRightThumb() { return _xinput.Buttons[XINPUT_BUTTON_RIGHT_THUMB]; }
        // LB�{�^��
        bool GetXinputLeftShoulder() { return _xinput.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]; }
        // RB�{�^��
        bool GetXinputRightShoulder() { return _xinput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]; }
        // A�{�^��
        bool GetXinputButtonA() { return _xinput.Buttons[XINPUT_BUTTON_A]; }
        // B�{�^��
        bool GetXinputButtonB() { return _xinput.Buttons[XINPUT_BUTTON_B]; }
        // X�{�^��
        bool GetXinputButtonX() { return _xinput.Buttons[XINPUT_BUTTON_X]; }
        // Y�{�^��
        bool GetXinputButtonY() { return _xinput.Buttons[XINPUT_BUTTON_Y]; }
        // ���g���K�[
        bool GetXinputLeftTrigger() { return _xinput.LeftTrigger; }
        // �E�g���K�[
        bool GetXinputRightTrigger() { return _xinput.RightTrigger; }
        // ���X�e�B�b�N�̉����l
        bool GetXinputThumbLX() { return _xinput.ThumbLX; }
        // ���X�e�B�b�N�̏c���l
        bool GetXinputThumbLY() { return _xinput.ThumbLY; }
        // �E�X�e�B�b�N�̉����l
        bool GetXinputThumbRX() { return _xinput.ThumbRX; }
        // �E�X�e�B�b�N�̏c���l
        bool GetXinputThumbRY() { return _xinput.ThumbRY; }
    private:
        int _InputInfo = 0;  //! ���͏��
        int _TrgInfo = 0;  //! �g���K�[���͏��
        XINPUT_STATE _xinput{ 0 };  //! XInput�p���͏��
        XINPUT_STATE _triggerKey{ 0 };  //! XInput�p�g���K�[���͏��
        DINPUT_JOYSTATE _DInput{ 0 };  //! DirectInput�p���͏��
        DINPUT_JOYSTATE _DTrigger{ 0 };  //! DirectInput�p�g���K�[���͏��
    };

}
