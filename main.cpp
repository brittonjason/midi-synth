#include <vector>
#include <string>

#include "midi.hpp"
#include "synthesizer.hpp"
#include "wav.hpp"

// TODO: implement the main entry point for synth here

int main(int argc, char *argv[])
{
	std::vector<std::string> arguments;
    for(int i = 0; i < argc; ++i) arguments.push_back(argv[i]);

    TrackListType tracks = readMIDIFromFile(argv[1]);
	Signal signal = synthesize(tracks.front());
	write_wav(signal, argv[2]);

	return EXIT_SUCCESS;
}
