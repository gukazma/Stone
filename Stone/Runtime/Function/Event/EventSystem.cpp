#include "EventSystem.h"
namespace Stone
{
    bool EventSystem::alreadyRegistered(EVENTID eventId, Listener* client) {
        // Assume they are not already registered
        bool alreadyRegistered = false;

        // Range iterator
        pair<multimap<EVENTID, Listener*>::iterator,
            multimap<EVENTID, Listener*>::iterator> range;

        // Find all the clients able to receive this event
        range = database.equal_range(eventId);

        // Go through the list of clients
        for (multimap<EVENTID, Listener*>::iterator iter = range.first;
            iter != range.second; iter++) {
            // If this client is already subscribed
            if ((*iter).second == client) {
                // Already registered, quit now
                alreadyRegistered = true;
                break;
            }
        }

        return alreadyRegistered;
    }

    void EventSystem::dispatchEvent(Event* event) {
        // Iterator needed
        pair<multimap<EVENTID, Listener*>::iterator,
            multimap<EVENTID, Listener*>::iterator> range;

        // Get all the clients who respond to this event
        range = database.equal_range(event->eventId());

        // For every client
        for (multimap<EVENTID, Listener*>::iterator iter = range.first;
            iter != range.second; iter++) {
            // Handle the event
            (*iter).second->handleEvent(event);
        }
    }

    // Registers a client to start listening for an event
    void EventSystem::registerClient(EVENTID event, Listener* client) {
        // If the client is null, or already registered
        if (!client || alreadyRegistered(event, client)) {
            // Quit now
            return;
        }

        // Insert the client into the database
        database.insert(make_pair(event, client));
    }

    // Unregisters a client from a specific event
    void EventSystem::unregisterClient(EVENTID event, Listener* client) {
        // Iterator
        pair<multimap<EVENTID, Listener*>::iterator,
            multimap<EVENTID, Listener*>::iterator> range;

        //  Find all the clients able to receive this event
        range = database.equal_range(event);

        // For every client who can respond to this event
        for (multimap<EVENTID, Listener*>::iterator iter = range.first;
            iter != range.second; iter++) {
            // If this is the guy we remove
            if ((*iter).second == client) {
                // Erase the bastard & quit
                iter = database.erase(iter);
                break;
            }
        }
    }

    // Unregister a client from all events
    void EventSystem::unregisterAll(Listener* client) {
        if (database.size() > 0) {
            // Iterator
            multimap<EVENTID, Listener*>::iterator iter = database.begin();
            // For every entry in the database
            while (iter != database.end()) {
                // If this is the chosen one
                if ((*iter).second == client) {
                    // Destroy him
                    iter = database.erase(iter);
                }
                else {
                    // Move on
                    iter++;
                }
            }
        }
    }

    // Send an event
    void EventSystem::sendEvent(EVENTID eventId, void* data) {
        // Create the events
        Event newEvent(eventId, data);
        // Queue it up
        currentEvents.push_back(newEvent);
    }

    // Process all events
    void EventSystem::processEvents() {
        // For every event
        while (currentEvents.size()) {
            // Dispatch the event
            dispatchEvent(&currentEvents.front());
            // Remove it from the list
            currentEvents.pop_front();
        }
    }

    // Clear events
    void EventSystem::clearEvents() {
        // Clear the events
        currentEvents.clear();
    }

    // Shutdown event system
    void EventSystem::shutdown() {
        database.clear();
        currentEvents.clear();
    }
}
