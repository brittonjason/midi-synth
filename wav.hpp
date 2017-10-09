/** \file WAV Module
 */

#ifndef WAV_HPP
#define WAV_HPP

#include <string>
#include <fstream>
#include <cstdint>
#include "signal.hpp"

/** \fn Write a signal to a WAV file. Returns true on success, false on failure.
 * The signal should be quantized into a 16 bit integer using rounding to nearest.
 * \param sound the signal to write.
 * \param filename the filename to write to.
 */
bool write_wav(Signal & sound, const std::string &filename);

const int8_t  ChunkID[4] = {'R', 'I', 'F', 'F'};
//	  int32_t ChunkSize;								// 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
const int8_t  Format[4] = {'W', 'A', 'V', 'E'};
const int8_t  Subchunk1ID[4] = {'f', 'm', 't', ' '};
const int32_t Subchunk1Size = 16;
const int16_t AudioFormat = 1;
const int16_t NumChannels = 1;							// Mono
const int32_t SampleRate = 44100;						// Samples per second
const int32_t ByteRate = 88200;							// SampleRate * NumChannels * BitsPerSample/8
const int16_t BlockAlign = 2;							// NumChannels * BitsPerSample/8
const int16_t BitsPerSample = 16;						// 8 bits = 8, 16 bits = 16
const int8_t  Subchunk2ID[4] = {'d', 'a', 't', 'a'};
//	  int32_t Subchunk2Size;							// NumSamples * NumChannels * BitsPerSample/8
//	  int16_t Data[NUMSAMPLES];							// the Pulse Code Modulated data

#endif
