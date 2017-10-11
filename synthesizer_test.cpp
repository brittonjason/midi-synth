/** \file Integration tests for synthesizer function.
*/
#include "catch.hpp"

#include "track.hpp"
#include "synthesizer.hpp"

TEST_CASE("Test synthesizing signal from track.", "[synthesizer]") {
	Track t;	
	t.addNoteEvent(8, 86, 50, 1);
	t.addEndEvent(100);
	Signal s = synthesize(t);

	REQUIRE(s.size() > 0);
}
