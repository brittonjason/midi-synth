#include "track.hpp"

/** Construct Track with ticks per beat in microsec.
* default is 120 BPM = 0.5 sec per beat = 500000 microsec per beat
*/
Track::Track(intmax_t ticks_per_beat) {
	ticksPerBeat = ticks_per_beat;
}

/** Get ticks per beat in microsec. */
intmax_t Track::getTicksPerBeat() const {
	return ticksPerBeat;
}

/** Get iterator to first event. */
Track::ConstIteratorType Track::begin() const {
	return eventList.begin();
}

/** Get iterator to end of event sequence. */
Track::ConstIteratorType Track::end() const {
	Track::ConstIteratorType iter;
	for (Track::ConstIteratorType i = eventList.begin(); i != eventList.end(); i++) {
		iter = i;
	}
	return iter;
}

/** Add an EndEvent to the track sequence. 
* \param tick_time, the MIDI tick time of the event.
*/
void Track::addEndEvent(intmax_t tick_time) {
	eventList.push_back(MIDIEvent(EndTrackEvent(), tick_time));
}

/** Add a TempoEvent to the track sequence. 
* \param tempo the new tempo of the track after this tick
* \param tick_time the MIDI tick time of the event.
*/
void Track::addTempoEvent(intmax_t tempo, intmax_t tick_time) {
	eventList.push_back(MIDIEvent(TempoEvent(tempo), tick_time));
}

/** Add a NoteEvent to the track sequence.
* \param code the event code (8 = On, 9 = Off unless data2 = 0)
* \param data1 the first data byte (holding the note number) 
* \param data2 the second data byte (holding the velocity)
* \param tick_time, the MIDI tick time of the event.
*/
void Track::addNoteEvent(uint8_t code, uint8_t data1, uint8_t data2, intmax_t tick_time) {
	bool on;
	if (code == 8)
		on = true;
	if (code == 9)
		on = false;
	eventList.push_back(MIDIEvent(NoteEvent(on, data1, data2), tick_time));
}
