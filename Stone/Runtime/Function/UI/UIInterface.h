#pragma once
#include "Function/Render/Interface/FrameBuffer.h"
namespace Stone
{
    class UIInterface
    {
    public:
        virtual void run() {}

        virtual void tick() {}
    };
}