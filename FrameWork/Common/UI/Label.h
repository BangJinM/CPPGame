#pragma once

#include "Widget.h"
#include "MyMath.h"
namespace GameEngine
{
    class Label : public Widget
    {
    private:
        /* data */
        int m_Font_Size;
        std::string m_Text;
        vecterFloat2 m_Content_Size;
    public:
        Label(/* args */);
        ~Label();

        void setFontSize(int size);
        int getFontSize();

        void setText(std::string str);
        std::string getText();

        void setContentSize(vecterFloat2 contentSize);
        vecterFloat2 getContentSize();
    };
} // namespace GameEngine