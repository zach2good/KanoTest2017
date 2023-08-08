#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <string>
#include "Challenge.h"

std::string valid_json_1 = R"""(
{
	"title":"Welcome",
	"steps":[
		{
		"instruction":"type \"say hello\"",
		"validate":"say hello"
		},
		{
		"instruction":"What is your name?",
		"validate":"[a-zA-Z]+"
		}
	]
}
)""";

std::string valid_json_2 = R"""(
{
	"title":"Joke",
	"steps":[
		{
		"instruction": "Knock knock. Type \"who's there\"",
		"validate": "who\\'?s there\\??"
		},
		{
		"instruction": "Art. Type \"Art who\"",
		"validate": "art who\\??"
		},
		{
		"instruction": "R2-D2. Did you like my joke?",
		"validate": "(yes|no)"
		}
	]
}
)""";

std::string invalid_json = R"""(
<?xml version="1.0" encoding="UTF-8"?>
<root>
   <steps>
      <element>
         <instruction>type "say hello"</instruction>
         <validate>say hello</validate>
      </element>
      <element>
         <instruction>What is your name?</instruction>
         <validate>[a-zA-Z]+</validate>
      </element>
   </steps>
   <title>Welcome</title>
</root>
)""";

TEST_CASE("Challenges can be created from valid JSON", "[challenge]") {
	REQUIRE_NOTHROW(Challenge(valid_json_1));
}

TEST_CASE("Challenges cannot be created from invalid JSON", "[challenge]") {
	REQUIRE_THROWS(Challenge(invalid_json));
}

TEST_CASE("Challenges can be given a title correctly", "[challenge]") {
	Challenge chal = Challenge(valid_json_1);

	REQUIRE(chal.GetTitle() == std::string("Welcome"));
}

TEST_CASE("Challenges can validate correct input", "[challenge]") {
	Challenge chal = Challenge(valid_json_1);

	auto step_0 = chal[0];
	auto step_1 = chal[1];
	
	REQUIRE(step_0.Validate("say hello")); // type "say hello"
	REQUIRE(step_1.Validate("Zach")); // What is your name?
}

TEST_CASE("Challenges can reject incorrect input", "[challenge]") {
	Challenge chal = Challenge(valid_json_1);

	auto step_0 = chal[0];
	auto step_1 = chal[1];

	REQUIRE_FALSE(step_0.Validate("say goodbye")); // type "say hello"
	REQUIRE_FALSE(step_1.Validate("Strange entry #1")); // What is your name?
}

TEST_CASE("Challenge 1 can be passed", "[challenge]") {
	Challenge chal = Challenge(valid_json_1);

	auto step_0 = chal[0];
	auto step_1 = chal[1];

	REQUIRE(step_0.Validate("say hello")); // type "say hello"
	REQUIRE(step_1.Validate("Zach")); // What is your name?
}

TEST_CASE("Challenge 1 can be failed", "[challenge]") {
	Challenge chal = Challenge(valid_json_1);

	auto step_0 = chal[0];
	auto step_1 = chal[1];

	REQUIRE_FALSE(step_0.Validate("say goodbye")); // type "say hello"
	REQUIRE_FALSE(step_1.Validate("Silly test string #2")); // What is your name?
}

TEST_CASE("Challenge 2 can be passed", "[challenge]") {
	Challenge chal = Challenge(valid_json_2);

	auto step_0 = chal[0];
	auto step_1 = chal[1];
	auto step_2 = chal[2];

	REQUIRE(step_0.Validate("who's there?")); // "Knock knock. Type "who's there",
	REQUIRE(step_1.Validate("art who?")); // Type "Art who",
	REQUIRE(step_2.Validate("yes")); // "R2-D2. Did you like my joke?",
}

TEST_CASE("Challenge 2 can be failed", "[challenge]") {
	Challenge chal = Challenge(valid_json_2);

	auto step_0 = chal[0];
	auto step_1 = chal[1];
	auto step_2 = chal[2];

	REQUIRE_FALSE(step_0.Validate("who's yonder?")); // "Knock knock. Type "who's there",
	REQUIRE_FALSE(step_1.Validate("not right now")); // Type "Art who",
	REQUIRE_FALSE(step_2.Validate("may the force be with you")); // "R2-D2. Did you like my joke?",
}