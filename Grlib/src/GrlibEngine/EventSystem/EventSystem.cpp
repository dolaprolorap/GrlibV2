#include "GrlibEngine/EventSystem/EventSystem.h"

Event<unsigned int> EventSystem::on_key_pressed;
HANDLE EventSystem::h;

void EventSystem::handle() {
    static DWORD cc;
    static INPUT_RECORD irec;
    GetNumberOfConsoleInputEvents(h, &cc);
    if (cc) {
        ReadConsoleInput(h, &irec, 1, &cc);
        if (irec.EventType == KEY_EVENT
            && ((KEY_EVENT_RECORD&)irec.Event).bKeyDown)
        {
            unsigned int pressed_key = ((KEY_EVENT_RECORD&)irec.Event).uChar.AsciiChar;
            EventSystem::on_key_pressed.execute(pressed_key);
        }
    }
}

void EventSystem::init() {
    EventSystem::h = GetStdHandle(STD_INPUT_HANDLE);

    if (EventSystem::h == NULL) {
        throw EventSystemException("Invalid console handler");
    }
}