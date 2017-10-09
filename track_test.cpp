/** \file Unit tests for Track Module
*/
#include "catch.hpp"

#include "track.hpp"

TEST_CASE("Test the Track constructor and ticks per beat.", "[Track]") {
	Track t1;
	Track t2(100000);

	REQUIRE(t1.getTicksPerBeat() == 500000);
	REQUIRE(t2.getTicksPerBeat() == 100000);
}

TEST_CASE("Test adding events to a track and iterator.", "[Track]") {
	Track t;
	t.addEndEvent(1);
	t.addTempoEvent(500000, 1000);
	t.addNoteEvent(8, 86, 50, 2000);

	Track::ConstIteratorType iterator = t.begin();
	REQUIRE((*iterator).isEndTrackEvent() == true);
	iterator++;
	REQUIRE((*iterator).isTempoEvent() == true);
	iterator++;
	REQUIRE((*iterator).isNoteEvent() == true);
	Track::ConstIteratorType iterator2 = t.end();
	REQUIRE(iterator != iterator2);
}
