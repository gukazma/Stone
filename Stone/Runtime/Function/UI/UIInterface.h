#pragma once
#include "Function/Render/FrameBuffer.h"
namespace Stone
{
    class UIInterface
    {
    public:
        virtual void run() {}

        virtual void tick() {}
    };
}