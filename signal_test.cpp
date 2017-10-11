/** \file Unit tests for Signal Module
*/
#include "catch.hpp"

#include "signal.hpp"

TEST_CASE("Test constructor and sample rate.", "[signal]") {
	Signal s1;
	Signal s2(1);

	REQUIRE(s1.getSampleRate() == 44100);
	REQUIRE(s2.getSampleRate() == 1);
}

TEST_CASE("Test adding and accessing signal samples and total signal size.", "[signal]") {
	Signal s;

	REQUIRE(s.size() == 0);

	for (int i = 0; i < 5; i++) {
		s.push_back(i);
	}

	REQUIRE(s.size() == 5);
	REQUIRE(s[3] == 3);
}

TEST_CASE("Test normalizing signal.", "[signal]") {
	Signal s;

	for (int i = 0; i < 5; i++) {
		s.push_back(i);
	}

	s.normalize();

	REQUIRE(s.size() == 5);
}
