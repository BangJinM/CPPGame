#pragma once

#include "Config.h"
#include "MyMath.h"
#include "Widget.h"

namespace GameEngine
{
    class Label : public Widget
    {
    private:
        /* data */
        int m_Font_Size;
        std::string m_Text;
        VecterFloat2 m_Content_Size;

    public:
        Label(/* args */);
        ~Label();

        void setFontSize(int size);
        int getFontSize();

        void setText(std::string str);
        std::string getText();

        void setContentSize(VecterFloat2 contentSize);
        VecterFloat2 getContentSize();
    };
}  // namespace GameEngine