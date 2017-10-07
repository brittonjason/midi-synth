/** \file Unit tests for Event Module
*/
#include "catch.hpp"

#include "event.hpp"

TEST_CASE("Test the TempoEvent constructor and tempo.", "[TempoEvent]") {
	TempoEvent e1;
	TempoEvent e2(100000);

	REQUIRE(e1.getTempo() == 500000);
	REQUIRE(e2.getTempo() == 100000);
}

TEST_CASE("Test the NoteEvent constructor, change type, number, and velocity.", "[NoteEvent]") {
	NoteEvent n1(true, 86, 50);

	REQUIRE(n1.getNoteOn() == true);
	REQUIRE(n1.getNoteNumber() == 86);
	REQUIRE(n1.getNoteVelocity() == 50);
}

TEST_CASE("Test the MIDIEvent constructors, event type, and tick time." "[MIDIEvent]") {
	TempoEvent e1;
	EndTrackEvent e2;
	NoteEvent e3(true, 86, 50);
	MIDIEvent m1(e1, 100);
	MIDIEvent m2(e2, 200);
	MIDIEvent m3(e3, 300);

	REQUIRE(m1.isTempoEvent() == true);
	REQUIRE(m1.isEndTrackEvent() == false);
	REQUIRE(m1.isNoteEvent() == false);
	REQUIRE(m1.getTickTime() == 100);

	REQUIRE(m2.isTempoEvent() == false);
	REQUIRE(m2.isEndTrackEvent() == true);
	REQUIRE(m2.isNoteEvent() == false);
	REQUIRE(m2.getTickTime() == 200);

	REQUIRE(m3.isTempoEvent() == false);
	REQUIRE(m3.isEndTrackEvent() == false);
	REQUIRE(m3.isNoteEvent() == true);
	REQUIRE(m3.getTickTime() == 300);
}

TEST_CASE("Test the MIDIEvent casting." "[MIDIEvent]") {
	TempoEvent e1;
	NoteEvent e2(true, 86, 50);
	MIDIEvent m1(e1, 100);
	MIDIEvent m2(e2, 200);

	REQUIRE(m1.asTempoEvent().getTempo() == 500000);
	REQUIRE(m2.asNoteEvent().getNoteOn() == true);
}
