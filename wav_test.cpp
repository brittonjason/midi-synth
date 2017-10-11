/** \file Unit tests for WAV Module
 */
#include "catch.hpp"

#include "wav.hpp"
#include "synthesizer.hpp"

#include <fstream>

TEST_CASE("Test writing to output file.", "[wav]") {
	Track t;	
	t.addNoteEvent(8, 86, 50, 1);
	t.addEndEvent(100);
	Signal s = synthesize(t);

	write_wav(s, "temp");

	std::ifstream in("temp-0.wav", std::ifstream::ate | std::ifstream::binary);
    REQUIRE(in.tellg() > 0);
}
