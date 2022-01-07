
/*****************************************************************//**
 * @file   InputJoypad.h
 * @brief  ジョイパッドクラスの宣言
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
         * @brief 更新処理
         */
        void Process();
        // 方向キー上
        bool GetXinputUp() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_UP]; }
        // 方向キー下
        bool GetXinputDown() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_DOWN]; }
        // 方向キー左
        bool GetXinputLeft() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_LEFT]; }
        // 方向キー右
        bool GetXinputRight() { return _xinput.Buttons[XINPUT_BUTTON_DPAD_RIGHT]; }
        // STARTボタン
        bool GetXinputStart() { return _xinput.Buttons[XINPUT_BUTTON_START]; }
        // BACKボタン
        bool GetXinputBack() { return _xinput.Buttons[XINPUT_BUTTON_BACK]; }
        // 左スティック押し込み
        bool GetXinputLeftThumb() { return _xinput.Buttons[XINPUT_BUTTON_LEFT_THUMB]; }
        // 右スティック押し込み
        bool GetXinputRightThumb() { return _xinput.Buttons[XINPUT_BUTTON_RIGHT_THUMB]; }
        // LBボタン
        bool GetXinputLeftShoulder() { return _xinput.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]; }
        // RBボタン
        bool GetXinputRightShoulder() { return _xinput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]; }
        // Aボタン
        bool GetXinputButtonA() { return _xinput.Buttons[XINPUT_BUTTON_A]; }
        // Bボタン
        bool GetXinputButtonB() { return _xinput.Buttons[XINPUT_BUTTON_B]; }
        // Xボタン
        bool GetXinputButtonX() { return _xinput.Buttons[XINPUT_BUTTON_X]; }
        // Yボタン
        bool GetXinputButtonY() { return _xinput.Buttons[XINPUT_BUTTON_Y]; }
        // 左トリガー
        bool GetXinputLeftTrigger() { return _xinput.LeftTrigger; }
        // 右トリガー
        bool GetXinputRightTrigger() { return _xinput.RightTrigger; }
        // 左スティックの横軸値
        bool GetXinputThumbLX() { return _xinput.ThumbLX; }
        // 左スティックの縦軸値
        bool GetXinputThumbLY() { return _xinput.ThumbLY; }
        // 右スティックの横軸値
        bool GetXinputThumbRX() { return _xinput.ThumbRX; }
        // 右スティックの縦軸値
        bool GetXinputThumbRY() { return _xinput.ThumbRY; }
    private:
        int _InputInfo = 0;  //! 入力情報
        int _TrgInfo = 0;  //! トリガー入力情報
        XINPUT_STATE _xinput{ 0 };  //! XInput用入力情報
        XINPUT_STATE _triggerKey{ 0 };  //! XInput用トリガー入力情報
        DINPUT_JOYSTATE _DInput{ 0 };  //! DirectInput用入力情報
        DINPUT_JOYSTATE _DTrigger{ 0 };  //! DirectInput用トリガー入力情報
    };

}
