#include "synthesizer.hpp"

/** \fn Synthesize a Track into a Signal.
 * Returned signal is empty on failure.
 * \param track the track to synthesize.
 */
Signal synthesize(Track & track) {
	Signal signal;
	DefaultInstrument instrument(track);
	while (!instrument.halted()) {
		double val = instrument.sample(1/44100.0);
		//std::cout << val << "\n";
		signal.push_back(val);
	}
	return signal;
}
