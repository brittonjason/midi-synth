/** \file Unit tests for DefaultInstrument Module
*/
#include "catch.hpp"

#include "track.hpp"
#include "instrument.hpp"

TEST_CASE("Test constructor and sample.", "[instrument]") {
	Track t;	
	t.addNoteEvent(8, 86, 50, 1);
	t.addEndEvent(100);
	DefaultInstrument i(t);

	REQUIRE(i.sample(1/44100.0) == 0);
}

TEST_CASE("Test halted.", "[instrument]") {
	Track t;
	t.addEndEvent(1);
	DefaultInstrument i(t);

	REQUIRE(i.halted() == false);
	i.sample(1/44100.0);
	REQUIRE(i.halted() == true);	
}

TEST_CASE("Test note frequencies.", "[instrument]") {
	Track t;
	DefaultInstrument j(t);
	for (int i = 0; i < 128; i++) {
		REQUIRE(j.freq(i) > 0);
	}
}
