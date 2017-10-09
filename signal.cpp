#include "signal.hpp"

/** Construct a Signal given a sampling rate in samples-per-second (Hz). The default rate is
* 44.1 kHz.
* \param sampleRate the sampling rate in Hz
*/
Signal::Signal(unsigned int sampleRate) {
	sr = sampleRate;
	numSamples = 0;
}

/** return the sampling rate in Hz.*/
unsigned int Signal::getSampleRate() {
	return sr;
}

/** Normalize the Signal to fit into a 16 bit integer 
* when quantized.
*/
void Signal::normalize() {

}

/** Add a sample to the signal. 
* \param value the double sample value to add.
*/
void Signal::push_back(double value) {
	samples.push_back(value);
	numSamples++;
}

/** Return the number of samples in the signal. */
std::size_t Signal::size() {
	return numSamples;
}

/** Return the sample at given index. 
* \param index the index of the sample to return.
*/
double Signal::operator[](std::size_t index) {
	return samples.at(index);
}
