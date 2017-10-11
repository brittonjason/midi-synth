#include "instrument.hpp"

/** Construct a Default Instrument using the specified track.
* \param track the track to read events from. 
*/
DefaultInstrument::DefaultInstrument(const Track & track) {
	tr = track;
	realTimeElapsed = 0;
	iterator = tr.begin();
	MClockRate = tr.getTicksPerBeat();
	std::cout << MClockRate << "\n";
	tempo = 500000;
}

/** Returns true of the DefaultInstrument has stopped processing events.
* This can occu e.g. if all events have been consumed or a EndTrackEvent
* has been processed.
*/
bool DefaultInstrument::halted() {
	if (iterator == tr.end() || EndTrackEventProcessed)
		return true;

	return false;
}

/** Return the sample after the (real) time increment. Samples the 
* instrument based on its state after processing all events prior 
* to this time.
* \param deltaT the time increment in seconds.
*/
double DefaultInstrument::sample(double deltaT) {
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

	realTimeElapsed += deltaT;

	bool eventsProcessed = false;
	while (!eventsProcessed) {
		double eventRealTime = (*iterator).getTickTime() * tempo / 1000000.0 / MClockRate;

		if (eventRealTime < realTimeElapsed) {
			// process event
			if ((*iterator).isEndTrackEvent()) {
				std::cout << "EndTrackEvent\n";
				EndTrackEventProcessed = true;
				break;
			}
			if ((*iterator).isTempoEvent()) {
				tempo = (*iterator).asTempoEvent().getTempo();
				std::cout << "tempo changed to " << tempo << " at time " 
					<< eventRealTime << "\n";
			}
			if ((*iterator).isNoteEvent()) {
				std::cout << "note event " << (*iterator).asNoteEvent().getNoteOn() << " for note " 
					<< freq((*iterator).asNoteEvent().getNoteNumber()) << " at time " << eventRealTime << "\n";
				if ((*iterator).asNoteEvent().getNoteOn()) {
					activeNotes.push_back(Note((*iterator).asNoteEvent().getNoteNumber(), eventRealTime, 
						(*iterator).asNoteEvent().getNoteVelocity()));
				}
			}
			iterator++;
		}
		else {
			eventsProcessed = true;
		}
	}
	double v = sumActiveNotes(realTimeElapsed);
	return v;
}

double DefaultInstrument::getEnvelope(Note n, double time) {
	double noteLength = 0.25;
	double t0 = 0 * noteLength;
	double t1 = 0.25 * noteLength;
	double t2 = 0.45 * noteLength;
	double t3 = 0.8 * noteLength;
	double t4 = 1 * noteLength;
	double S = 0.8;

	double currentTime = time - n.getTimeStart();

	if (currentTime >= t0 && currentTime <= t1) {
		return (1 / t1 * currentTime);
	}
	else if (currentTime > t1 && currentTime <= t2) {
		return 1 - (currentTime - t1);
	}
	else if (currentTime > t2 && currentTime <= t3) {
		return S;
	}
	else if (currentTime > t3 && currentTime <= t4) {
		return S - ((S / (t4 - t3)) * (currentTime - t3));
	}
	else
		return 0;
}

double DefaultInstrument::sumActiveNotes(double time) {
	double val = 0;

	for (Note n : activeNotes) {
		double noteVal = 200 * n.getVelocity() * getEnvelope(n, time) * 
			sin(2 * M_PI * freq(n.getNoteNum()) * (time - n.getTimeStart()));
		val += noteVal;
	}
	return val;
}

double DefaultInstrument::freq(int8_t noteNum) {
	double C  = 261.63;
	double Cs = 277.18;
	double D  = 293.66;
	double Ds = 311.13;
	double E  = 329.63;
	double F  = 349.63;
	double Fs = 369.994;
	double G  = 392.0;
	double Gs = 415.305;
	double A  = 440.0;
	double As = 466.164;
	double B  = 493.88;

	switch(noteNum) {
		case 0:   return C  / (2*2*2*2*2);
		case 1:   return Cs / (2*2*2*2*2);
		case 2:   return D  / (2*2*2*2*2);
		case 3:   return Ds / (2*2*2*2*2);
		case 4:   return E  / (2*2*2*2*2);
		case 5:   return F  / (2*2*2*2*2);
		case 6:   return Fs / (2*2*2*2*2);
		case 7:   return G  / (2*2*2*2*2);
		case 8:   return Gs / (2*2*2*2*2);
		case 9:   return A  / (2*2*2*2*2);
		case 10:  return As / (2*2*2*2*2);
		case 11:  return B  / (2*2*2*2*2);
		case 12:  return C  / (2*2*2*2);
		case 13:  return Cs / (2*2*2*2);
		case 14:  return D  / (2*2*2*2);
		case 15:  return Ds / (2*2*2*2);
		case 16:  return E  / (2*2*2*2);
		case 17:  return F  / (2*2*2*2);
		case 18:  return Fs / (2*2*2*2);
		case 19:  return G  / (2*2*2*2);
		case 20:  return Gs / (2*2*2*2);
		case 21:  return A  / (2*2*2*2);
		case 22:  return As / (2*2*2*2);
		case 23:  return B  / (2*2*2*2);
		case 24:  return C  / (2*2*2);
		case 25:  return Cs / (2*2*2);
		case 26:  return D  / (2*2*2);
		case 27:  return Ds / (2*2*2);
		case 28:  return E  / (2*2*2);
		case 29:  return F  / (2*2*2);
		case 30:  return Fs / (2*2*2);
		case 31:  return G  / (2*2*2);
		case 32:  return Gs / (2*2*2);
		case 33:  return A  / (2*2*2);
		case 34:  return As / (2*2*2);
		case 35:  return B  / (2*2*2);
		case 36:  return C  / (2*2);
		case 37:  return Cs / (2*2);
		case 38:  return D  / (2*2);
		case 39:  return Ds / (2*2);
		case 40:  return E  / (2*2);
		case 41:  return F  / (2*2);
		case 42:  return Fs / (2*2);
		case 43:  return G  / (2*2);
		case 44:  return Gs / (2*2);
		case 45:  return A  / (2*2);
		case 46:  return As / (2*2);
		case 47:  return B  / (2*2);
		case 48:  return C  / (2);
		case 49:  return Cs / (2);
		case 50:  return D  / (2);
		case 51:  return Ds / (2);
		case 52:  return E  / (2);
		case 53:  return F  / (2);
		case 54:  return Fs / (2);
		case 55:  return G  / (2);
		case 56:  return Gs / (2);
		case 57:  return A  / (2);
		case 58:  return As / (2);
		case 59:  return B  / (2);
		case 60:  return C;
		case 61:  return Cs;
		case 62:  return D;
		case 63:  return Ds;
		case 64:  return E;
		case 65:  return F;
		case 66:  return Fs;
		case 67:  return G;
		case 68:  return Gs;
		case 69:  return A;
		case 70:  return As;
		case 71:  return B;
		case 72:  return C  * (2);
		case 73:  return Cs * (2);
		case 74:  return D  * (2);
		case 75:  return Ds * (2);
		case 76:  return E  * (2);
		case 77:  return F  * (2);
		case 78:  return Fs * (2);
		case 79:  return G  * (2);
		case 80:  return Gs * (2);
		case 81:  return A  * (2);
		case 82:  return As * (2);
		case 83:  return B  * (2);
		case 84:  return C  * (2*2);
		case 85:  return Cs * (2*2);
		case 86:  return D  * (2*2);
		case 87:  return Ds * (2*2);
		case 88:  return E  * (2*2);
		case 89:  return F  * (2*2);
		case 90:  return Fs * (2*2);
		case 91:  return G  * (2*2);
		case 92:  return Gs * (2*2);
		case 93:  return A  * (2*2);
		case 94:  return As * (2*2);
		case 95:  return B  * (2*2);
		case 96:  return C  * (2*2*2);
		case 97:  return Cs * (2*2*2);
		case 98:  return D  * (2*2*2);
		case 99:  return Ds * (2*2*2);
		case 100: return E  * (2*2*2);
		case 101: return F  * (2*2*2);
		case 102: return Fs * (2*2*2);
		case 103: return G  * (2*2*2);
		case 104: return Gs * (2*2*2);
		case 105: return A  * (2*2*2);
		case 106: return As * (2*2*2);
		case 107: return B  * (2*2*2);
		case 108: return C  * (2*2*2*2);
		case 109: return Cs * (2*2*2*2);
		case 110: return D  * (2*2*2*2);
		case 111: return Ds * (2*2*2*2);
		case 112: return E  * (2*2*2*2);
		case 113: return F  * (2*2*2*2);
		case 114: return Fs * (2*2*2*2);
		case 115: return G  * (2*2*2*2);
		case 116: return Gs * (2*2*2*2);
		case 117: return A  * (2*2*2*2);
		case 118: return As * (2*2*2*2);
		case 119: return B  * (2*2*2*2);
		case 120: return C  * (2*2*2*2*2);
		case 121: return Cs * (2*2*2*2*2);
		case 122: return D  * (2*2*2*2*2);
		case 123: return Ds * (2*2*2*2*2);
		case 124: return E  * (2*2*2*2*2);
		case 125: return F  * (2*2*2*2*2);
		case 126: return Fs * (2*2*2*2*2);
		case 127: return G  * (2*2*2*2*2);
	}
}
