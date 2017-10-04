#include "track.hpp"

/** Construct Track with ticks per beat in microsec.
* default is 120 BPM = 0.5 sec per beat = 500000 microsec per beat
*/
Track::Track(intmax_t ticks_per_beat) {

}

/** Add an EndEvent to the track sequence. 
* \param tick_time, the MIDI tick time of the event.
*/
void Track::addEndEvent(intmax_t tick_time) {

}

/** Add a TempoEvent to the track sequence. 
* \param tempo the new tempo of the track after this tick
* \param tick_time the MIDI tick time of the event.
*/
void Track::addTempoEvent(intmax_t tempo, intmax_t tick_time) {

}

/** Add a NoteEvent to the track sequence.
* \param code the event code (8 = On, 9 = Off unless data2 = 0)
* \param data1 the first data byte (holding the note number) 
* \param data2 the second data byte (holding the velocity)
* \param tick_time, the MIDI tick time of the event.
*/
void Track::addNoteEvent(uint8_t code, uint8_t data1, uint8_t data2, intmax_t tick_time) {

}
