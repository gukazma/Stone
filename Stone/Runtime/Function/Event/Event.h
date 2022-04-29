#pragma once
// Customize your Event type here
#include <string>
#define EVENTID std::string
namespace Stone
{
    class Event {
    private:
        // Members
        EVENTID m_EventId;
        void* m_Parameter;

    public:
        // Constructor
        Event(EVENTID eventId, void* parameter = 0) {
            this->m_EventId = eventId;
            this->m_Parameter = parameter;
        }

        // Destructor
        ~Event() {}

        // Accessors
        inline EVENTID eventId() const { return m_EventId; }
        inline void* parameter() { return m_Parameter; }
    };
}