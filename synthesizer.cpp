#include "synthesizer.hpp"

/** \fn Synthesize a Track into a Signal.
 * Returned signal is empty on failure.
 * \param track the track to synthesize.
 */
Signal synthesize(Track & track) {
	Signal signal;
	DefaultInstrument instrument(track);
	while (!instrument.halted()) {
		signal.push_back(instrument.sample(1/44100.0));
	}
	return signal;
}
