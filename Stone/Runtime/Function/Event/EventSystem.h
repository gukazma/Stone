#pragma once
#include <list>
#include <map>
using std::multimap;
using std::list;
using std::pair;

#include "Event.h"
#include "Listener.h"
#include "Core/Base/PublicSingleton.h"


namespace Stone
{
    class EventSystem : public PublicSingleton<EventSystem>
    {
    private:
        // Database of Clients & their events
        multimap<EVENTID, Listener*> database;

        // List of events to be processed
        list<Event> currentEvents;

        // Helper Methods
        bool alreadyRegistered(EVENTID eventId, Listener* client);
        void dispatchEvent(Event* event);

    public:
        // Destructor
        ~EventSystem() { this->shutdown(); }

        // Registers a client to start listening for an event
        void registerClient(EVENTID event, Listener* client);

        // Unregisters a client from a specific event
        void unregisterClient(EVENTID event, Listener* client);

        // Unregister a client from all events
        void unregisterAll(Listener* client);

        // Send an event
        void sendEvent(EVENTID eventId, void* data = 0);

        // Process all events
        void processEvents();

        // Clear events
        void clearEvents();

        // Shutdown event system
        void shutdown();
    };
}
