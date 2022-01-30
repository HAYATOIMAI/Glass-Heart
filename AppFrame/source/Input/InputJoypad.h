
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
        bool GetXinputUp() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_UP]; }
        // 方向キー下
        bool GetXinputDown() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_DOWN]; }
        // 方向キー左
        bool GetXinputLeft() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_LEFT]; }
        // 方向キー右
        bool GetXinputRight() { return _xInput.Buttons[XINPUT_BUTTON_DPAD_RIGHT]; }
        // STARTボタン
        bool GetXinputStart() { return _xInput.Buttons[XINPUT_BUTTON_START]; }
        // BACKボタン
        bool GetXinputBack() { return _xInput.Buttons[XINPUT_BUTTON_BACK]; }
        // 左スティック押し込み
        bool GetXinputLeftThumb() { return _xInput.Buttons[XINPUT_BUTTON_LEFT_THUMB]; }
        // 右スティック押し込み
        bool GetXinputRightThumb() { return _xInput.Buttons[XINPUT_BUTTON_RIGHT_THUMB]; }
        // LBボタン
        bool GetXinputLeftShoulder() { return _xInput.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]; }
        // RBボタン
        bool GetXinputRightShoulder() { return _xInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]; }
        // Aボタン
        bool GetXinputButtonA() { return _xInput.Buttons[XINPUT_BUTTON_A]; }
        // Bボタン
        bool GetXinputButtonB() { return _xInput.Buttons[XINPUT_BUTTON_B]; }
        // Xボタン
        bool GetXinputButtonX() { return _xInput.Buttons[XINPUT_BUTTON_X]; }
        // Yボタン
        bool GetXinputButtonY() { return _xInput.Buttons[XINPUT_BUTTON_Y]; }
        // 左トリガー
        bool GetXinputLeftTrigger() { return _xInput.LeftTrigger; }
        // 右トリガー
        bool GetXinputRightTrigger() { return _xInput.RightTrigger; }
        // 左スティックの横軸値
        bool GetXinputThumbLX() { return _xInput.ThumbLX; }
        // 左スティックの縦軸値
        bool GetXinputThumbLY() { return _xInput.ThumbLY; }
        // 右スティックの横軸値
        bool GetXinputThumbRX() { return _xInput.ThumbRX; }
        // 右スティックの縦軸値
        bool GetXinputThumbRY() { return _xInput.ThumbRY; }
        /**  左スティックの横軸値 */
        short GetAnalogStickLX() { return _xInput.ThumbLX; }
        /** 左スティックの縦軸値 */
        short GetAnalogStickLY() { return _xInput.ThumbLY; }

        /** トリガ入力を取得 */
        XINPUT_STATE& GetTrg() { return _xTrigger; }
        // 方向キー上
        bool GetXTriggerUp() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_UP]; }
        // 方向キー下
        bool GetXTriggerDown() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_DOWN]; }
        // 方向キー左
        bool GetXTriggerLeft() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_LEFT]; }
        // 方向キー右
        bool GetXTriggerRight() { return _xTrigger.Buttons[XINPUT_BUTTON_DPAD_RIGHT]; }
        // STARTボタン
        bool GetXTriggerStart() { return _xTrigger.Buttons[XINPUT_BUTTON_START]; }
        // BACKボタン
        bool GetXTriggerBack() { return _xTrigger.Buttons[XINPUT_BUTTON_BACK]; }
        // 左スティック押し込み
        bool GetXTriggerLeftThumb() { return _xTrigger.Buttons[XINPUT_BUTTON_LEFT_THUMB]; }
        // 右スティック押し込み
        bool GetXTriggerRightThumb() { return _xTrigger.Buttons[XINPUT_BUTTON_RIGHT_THUMB]; }
        // LBボタン
        bool GetXTriggerLeftShoulder() { return _xTrigger.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]; }
        // RBボタン
        bool GetXTriggerRightShoulder() { return _xTrigger.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]; }
        // Aボタン
        bool GetXTriggerButtonA() { return _xTrigger.Buttons[XINPUT_BUTTON_A]; }
        // Bボタン
        bool GetXTriggerButtonB() { return _xTrigger.Buttons[XINPUT_BUTTON_B]; }
        // Xボタン
        bool GetXTriggerButtonX() { return _xTrigger.Buttons[XINPUT_BUTTON_X]; }
        // Yボタン
        bool GetXTriggerButtonY() { return _xTrigger.Buttons[XINPUT_BUTTON_Y]; }

    private:
        int _inputInfo{ 0 };  //!< 入力情報
        int _trgInfo{ 0 };  //!< トリガー入力情報
        XINPUT_STATE _xInput{ 0 };  //!< XInput用入力情報
        XINPUT_STATE _xTrigger{ 0 };  //!< XInput用トリガー入力情報
        DINPUT_JOYSTATE _dInput{ 0 };  //!< DirectInput用入力情報
        DINPUT_JOYSTATE _dTrigger{ 0 };  //!< DirectInput用トリガー入力情報
    };

}
