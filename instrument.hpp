/** \file The DefaultInstrument Module
 */
#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "event.hpp"
#include "track.hpp"

/** The default instrument. A simple fixed length note instrument using a
 * a sinusoid weighted by an envelope function.
 */
class DefaultInstrument{
public:

  /** No default constructor. A DefaultInstrument must have an associated 
   * track. 
   */
  DefaultInstrument() = delete;

  /** Cannot be copied. 
   */
  DefaultInstrument(const DefaultInstrument & ) = delete;

  /** Cannot be assigned.
   */
  DefaultInstrument & operator=(const DefaultInstrument & ) = delete;

  /** Construct a Default Instrument using the specified track.
   * \param track the track to read events from. 
   */
  DefaultInstrument(const Track & track);

  /** Returns true of the DefaultInstrument has stopped processing events.
   * This can occu e.g. if all events have been consumed or a EndTrackEvent
   * has been processed.
   */
  bool halted();

  /** Return the sample after the (real) time increment. Samples the 
   * instrument based on its state after processing all events prior 
   * to this time.
   * \param deltaT the time increment in seconds.
   */
  double sample(double deltaT);
  // MIDI time is represented by a tick integer
  // T = microseconds per beat (defined by tempo)
  // M = MIDI clock ticks per beat (defined by MIDI file)
  // T' = (T / 10^6) seconds per beat
  // hence seconds per MIDI clock tick = T' / M

  // Process any new Track events that became active since the last sample time
  // Sum the waveforms for the currently active notes
  // Must maintain a container of notes at the current time
  //  note number
  //  note velocity
  //  time turned on

  // Use a track iterator to process all events up to the current sample time

  // Probably want to define private helper functions to:
  //  convert a note number to a frequency
  //  determine the length of a note
  //  evaluate the envelope functions
  //  sum the active notes

private:  

  // State
  //  container of active notes
  //  for each active note: note number, time turned on, note velocity
  //  event iterator
  //  sample time

  Track tr;
  Track::ConstIteratorType iterator;
  double realTimeElapsed;
  bool EndTrackEventProcessed = false;
  intmax_t MClockRate;
  intmax_t tempo;

  double freq(int8_t noteNum);
};


#endif
