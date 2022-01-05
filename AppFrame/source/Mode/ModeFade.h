
/*****************************************************************//**
 * @file   ModeFade.h
 * @brief  モードのフェードクラス宣言
 *         画面の最前面にフルスクリーンサイズの画像を重ねてアルファ値によるフェードを行う
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeBase.h"

namespace AppFrame {

    class ModeFade : public ModeBase {
    public:
        ModeFade(GameBase& game);
        virtual ~ModeFade();
        virtual void Init() override;
        virtual void Enter() override;
        virtual void Process() override;
        virtual void Render() override;

    protected:
        int _width{ 1920 };
        int _height{ 1080 };
        unsigned int _color{ 0 };
        float _alpha{ 0 };
        float _deltaAlpha{ 0 };
    };

    class ModeFadeIn : public ModeFade {
    public:
        ModeFadeIn(GameBase& game);
        virtual ~ModeFadeIn();
        void Enter() override;
        void Process() override;
    };

    class ModeFadeOut : public ModeFade {
    public:
        ModeFadeOut(GameBase& game);
        virtual ~ModeFadeOut();
        void Enter() override;
        void Process() override;
    };

}