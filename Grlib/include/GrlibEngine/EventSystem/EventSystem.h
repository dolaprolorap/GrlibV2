#pragma once 
#include <windows.h>

#include "GrlibEngine/EventSystem/Event.h"

#include "GrlibExceptions/EngineExceptions/EventSystem/EventSystemException.h"

// Class handling all types of events
class EventSystem {
public:
	// Event for pressing arbitrary key
	static Event<unsigned int> on_key_pressed;

	// Handle all events
	static void handle();

	// Init event system
	static void init();

private:
	static HANDLE h;
};