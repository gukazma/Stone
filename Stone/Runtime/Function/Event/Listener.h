#pragma once
#include "Event.h"
namespace Stone
{
    class Listener {
    public:
        // Constructor
        Listener() {}
        // Destructor
        virtual ~Listener() {}
        // Handles the event passed to it
        virtual void handleEvent(Event* event) = 0;
    };

}
