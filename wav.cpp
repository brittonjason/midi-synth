#include "wav.hpp"

/** \fn Write a signal to a WAV file. Returns true on success, false on failure.
 * The signal should be quantized into a 16 bit integer using rounding to nearest.
 * \param sound the signal to write.
 * \param filename the filename to write to.
 */
bool write_wav(Signal & sound, const std::string &filename) {
	std::ofstream outStream = std::ofstream(filename + "-0.wav", std::ios::binary);

	std::size_t numSamples = sound.size();
	int32_t Subchunk2Size = numSamples * NumChannels * BitsPerSample / 8;
	int32_t ChunkSize = 4 + (8 + Subchunk1Size) + (8 + Subchunk2Size);

	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int8_t (*)[4]>(&ChunkID)), sizeof ChunkID);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(&ChunkSize), sizeof ChunkSize);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int8_t (*)[4]>(&Format)), sizeof Format);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int8_t (*)[4]>(&Subchunk1ID)), sizeof Subchunk1ID);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int32_t*>(&Subchunk1Size)), sizeof Subchunk1Size);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int16_t*>(&AudioFormat)), sizeof AudioFormat);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int16_t*>(&NumChannels)), sizeof NumChannels);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int32_t*>(&SampleRate)), sizeof SampleRate);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int32_t*>(&ByteRate)), sizeof ByteRate);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int16_t*>(&BlockAlign)), sizeof BlockAlign);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int16_t*>(&BitsPerSample)), sizeof BitsPerSample);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(const_cast<int8_t (*)[4]>(&Subchunk2ID)), sizeof Subchunk2ID);
	outStream.write(reinterpret_cast<std::fstream::char_type*>(&Subchunk2Size), sizeof Subchunk2Size);

	for (int i = 0; i < numSamples; i++) {
		int16_t f = sound[i];
		//std::cout << sound[i] << "\n";
		outStream.write(reinterpret_cast<std::fstream::char_type*>(&f), sizeof f);
	}

	outStream.close();

	return true;
}
