#include "event.hpp"

/** Construct a TempoEvent. The default tempo is 0.5 bpm
*/
TempoEvent::TempoEvent(intmax_t t) {
	tempo = t;
}

/** Get the tempo in micro-sec per beat.
*/
intmax_t TempoEvent::getTempo() const {
	return tempo;
}

/** Construct a note event. 
* \param on true if the note should be turned on, false if it should be 
*           turned off.
* \param notenum the MIDI note number (0-127) to be modified.
* \param notevelocity the velocity of the note change.
*/
NoteEvent::NoteEvent(bool on, int8_t notenum, int8_t notevelocity) {
	noteOn = on;
	noteNum = notenum;
	noteVel = notevelocity;
}

/** Get note change type. true if ON, false if OFF. 
*/
bool NoteEvent::getNoteOn() {
	return noteOn;
}

/** Get MIDI note number to change. Takes on values in [0,127]
*/
int8_t NoteEvent::getNoteNumber() const {
	return noteNum;
}

/** Get the velocity of the note change. 
*/
int8_t NoteEvent::getNoteVelocity() const {
	return noteVel;
}

/** Construct a MIDI event holding a TempoEvent at ticktime.
*/
MIDIEvent::MIDIEvent(TempoEvent e, intmax_t ticktime) {
	event_.tempoEvent = e;
	eventType_ = tempo;
	tickTime = ticktime;
}

/** Construct a MIDI event holding an EndTrackEvent at ticktime.
*/
MIDIEvent::MIDIEvent(EndTrackEvent e, intmax_t ticktime) {
	event_.endTrackEvent = e;
	eventType_ = endtrack;
	tickTime = ticktime;
}

/** Construct a MIDI event holding a NoteEvent at ticktime.
*/
MIDIEvent::MIDIEvent(NoteEvent e, intmax_t ticktime) {
	event_.noteEvent = e;
	eventType_ = note;
	tickTime = ticktime;
}

/** True if event is a TempoEvent, else false.
*/
bool MIDIEvent::isTempoEvent() const {
	return eventType_ == tempo;
}

/** True if event is an EndTrackEvent, else false.
*/
bool MIDIEvent::isEndTrackEvent() const {
	return eventType_ == endtrack;
}

/** True if event is a NoteEvent, else false.
*/
bool MIDIEvent::isNoteEvent() const {
	return eventType_ == note;
}

/** Get the MIDI tick time of this event (ticks per beat)
*/
intmax_t MIDIEvent::getTickTime() const {
	return tickTime;
}

/** Cast the MIDI event as a TempoEvent. Only valid if 
* isTempoEvent() returns true. 
*/
TempoEvent MIDIEvent::asTempoEvent() const {
	if (isTempoEvent()) {
		return event_.tempoEvent;
	}
}

/** Cast the MIDI event as a NoteEvent. Only valid if 
* isNoteEvent() returns true. 
*/
NoteEvent MIDIEvent::asNoteEvent() const {
	if (isNoteEvent()) {
		return event_.noteEvent;
	}
}
