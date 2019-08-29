/// <file> ArgParse.cpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary>  </summary>
/// 
/// <copyright> Copyright (c) 2019 </copyright>
/// 
/// <license>
/// The zlib/libpng License
/// 
/// Copyright (c) 2019 Spencer Hoffa
/// 
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
/// 
/// Permission is granted to anyone to use this software for any purpose,
/// including commercial applications, and to alter it and redistribute it
/// freely, subject to the following restrictions:
/// 
/// 		1. The origin of this software must not be misrepresented; you must not
/// 		claim that you wrote the original software. If you use this software in
/// 		a product, an acknowledgment in the product documentation would be
/// 		appreciated but is not required.
/// 
/// 		2. Altered source versions must be plainly marked as such, and must not
/// 		be misrepresented as being the original software.
/// 
/// 		3. This notice may not be removed or altered from any source
/// 		distribution.
/// 
/// This liscense can also be found at: http://opensource.org/licenses/Zlib
/// </license>

#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/ArgParse/ArgParse.hpp"

XNELO_TEST_CASE(ArgParse, ArgParseFullTest)
{

	const char *args[] = { "-s",
						  "--short-test",
						  "pos1",
						  "-t",
						  "arg",
						  "--test",
						  "arg",
						  "pos2",
						  "pos3" };
	const int argc = 9;

	XNELO::ARGS::OptionalArgDef o1('s', "short-test", "ShortTest", XNELO::ARGS::ArgValueTypeEnum::NONE, "Description 1", false);
	XNELO::ARGS::OptionalArgDef o2('t', "test", "Test", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description 2", true);
	XNELO::ARGS::PositionalArgDef p1("Pos1", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description P1");
	XNELO::ARGS::PositionalArgDef p2("Pos2", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description P2");
	XNELO::ARGS::PositionalArgDef p3("Pos3", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description P3");
	std::vector<XNELO::ARGS::ArgDef*> argVec{ &o1, &o2, &p1, &p2, &p3 };
	std::string progName = "ARGPARSEROPTIONALTEST";

	XNELO::ARGS::ArgParse * parser = new XNELO::ARGS::ArgParse(progName, argVec);
	XNELO_TEST_ASSERT_TRUE(parser->Parse(argc, args), "Parsing optional and positional arguments success");
	XNELO_TEST_ASSERT_EQUAL(parser->GetErrorCode(), XNELO::ERRORS::OK, "Check that error code is 'ok'");
	XNELO_TEST_ASSERT_TRUE(parser->Results.OptionalArgValues.count("ShortTest") == 1, "Check that ShortTest arg exists in map");
	XNELO_TEST_ASSERT_TRUE(parser->Results.OptionalArgValues["ShortTest"].Value == "", "Check that ShortTest has no value");
	XNELO_TEST_ASSERT_TRUE(parser->Results.OptionalArgValues.count("Test") == 1, "Check that the 'Test' optional arg exists");
	XNELO_TEST_ASSERT_TRUE(parser->Results.OptionalArgValues["Test"].Value == "arg", "Check that the 'Test' optional arg has correct value");
	XNELO_TEST_ASSERT_EQUAL(parser->Results.PositionalArgValues.size(), (size_t)3, "Check there are 3 positional args");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[0].Value == "pos1", "Check positional argument 1 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[1].Value == "pos2", "Check positional argument 2 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[2].Value == "pos3", "Check positional argument 3 is correct.");
	delete parser;
}

XNELO_TEST_CASE(ArgParse, ArgParseOptionalNotInArgs)
{
	const char *args[] = { "-s",
		"--short-test",
		"pos1",
		"pos2",
		"pos3" };
	const int argc = 5;

	XNELO::ARGS::OptionalArgDef o1('s', "short-test", "ShortTest", XNELO::ARGS::ArgValueTypeEnum::NONE, "Description 1", false);
	XNELO::ARGS::OptionalArgDef o2('t', "test", "Test", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description 2", true);
	XNELO::ARGS::PositionalArgDef p1("Pos1", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description P1");
	XNELO::ARGS::PositionalArgDef p2("Pos2", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description P2");
	XNELO::ARGS::PositionalArgDef p3("Pos3", XNELO::ARGS::ArgValueTypeEnum::STRING, "Description P3");
	std::vector<XNELO::ARGS::ArgDef*> argVec{ &o1, &o2, &p1, &p2, &p3 };
	std::string progName = "ARGPARSEROPTIONALTEST";

	XNELO::ARGS::ArgParse * parser = new XNELO::ARGS::ArgParse(progName, argVec);
	XNELO_TEST_ASSERT_TRUE(parser->Parse(argc, args), "Parsing optional and positional arguments success");
	XNELO_TEST_ASSERT_EQUAL(parser->GetErrorCode(), XNELO::ERRORS::OK, "Check that error code is 'ok'");
	XNELO_TEST_ASSERT_TRUE(parser->Results.OptionalArgValues.count("ShortTest") == 1, "Check that ShortTest arg exists in map");
	XNELO_TEST_ASSERT_TRUE(parser->Results.OptionalArgValues["ShortTest"].Value == "", "Check that ShortTest has no value");
	XNELO_TEST_ASSERT_TRUE(parser->Results.OptionalArgValues.count("Test") == 0, "Check that the 'Test' optional arg does not exist");
	XNELO_TEST_ASSERT_EQUAL(parser->Results.PositionalArgValues.size(), (size_t)3, "Check there are 3 positional args");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[0].Value == "pos1", "Check positional argument 1 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[1].Value == "pos2", "Check positional argument 2 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[2].Value == "pos3", "Check positional argument 3 is correct.");
	delete parser;
}

XNELO_TEST_CASE(ArgParse, ArgParsePositionalTest)
{
	const char *args[] = {"pos1",
						  "pos2",
						  "pos3"};
	const int argc = 3;
	XNELO::ARGS::PositionalArgDef p1("NAME1", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p2("NAME2", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p3("NAME3", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	std::vector<XNELO::ARGS::ArgDef*> argVec {&p1, &p2, &p3};
	std::string progName = "ARGPARSEPOSITIONALTEST";

	XNELO::ARGS::ArgParse * parser = new XNELO::ARGS::ArgParse(progName, argVec);
	XNELO_TEST_ASSERT_TRUE(parser->Parse(argc, args), "Parsing positional arguments success.");
	XNELO_TEST_ASSERT_EQUAL(parser->GetErrorCode(), XNELO::ERRORS::OK, "Check that error code is 'ok'");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[0].Value == "pos1", "Check positional argument 1 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[1].Value == "pos2", "Check positional argument 2 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[2].Value == "pos3", "Check positional argument 3 is correct.");
	delete parser;
}

XNELO_TEST_CASE(ArgParse, ArgParsePositionalTestTooManyArguments)
{
	const char *args[] = {"pos1",
						  "pos2",
						  "pos3",
						  "pos4",
						  "pos4"};
	const int argc = 5;
	XNELO::ARGS::PositionalArgDef p1("NAME1", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p2("NAME2", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p3("NAME3", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	std::vector<XNELO::ARGS::ArgDef*> argVec {&p1, &p2, &p3};
	std::string progName = "ARGPARSEPOSITIONALTEST";

	XNELO::ARGS::ArgParse * parser = new XNELO::ARGS::ArgParse(progName, argVec);
	XNELO_TEST_ASSERT_TRUE(parser->Parse(argc, args), "Parsing positional arguments success.");
	XNELO_TEST_ASSERT_EQUAL(parser->GetErrorCode(), XNELO::ERRORS::ARG_PARSER_ADDITIONAL_POSITIONAL_ARGS, "Check that error code is 'Too many args'");
	XNELO_TEST_ASSERT_TRUE(parser->GetErrorMessage() == "Additional positional args. Expected : 3 received: 5", "Check error message is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[0].Value == "pos1", "Check positional argument 1 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[1].Value == "pos2", "Check positional argument 2 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[2].Value == "pos3", "Check positional argument 3 is correct.");
	delete parser;
}

XNELO_TEST_CASE(ArgParse, ArgParsePositionalTestTooFewArguments)
{
	const char *args[] = {"pos1",
						  "pos2"};
	const int argc = 2;
	XNELO::ARGS::PositionalArgDef p1("NAME1", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p2("NAME2", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p3("NAME3", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	std::vector<XNELO::ARGS::ArgDef*> argVec {&p1, &p2, &p3};
	std::string progName = "ARGPARSEPOSITIONALTEST";

	XNELO::ARGS::ArgParse * parser = new XNELO::ARGS::ArgParse(progName, argVec);
	XNELO_TEST_ASSERT_FALSE(parser->Parse(argc, args), "Parsing positional arguments failed.");
	XNELO_TEST_ASSERT_EQUAL(parser->GetErrorCode(), XNELO::ERRORS::ARG_PARSER_NOT_ENOUGH_POSITIONAL_ARGS, "Check that error code is 'Too many args'");
	XNELO_TEST_ASSERT_TRUE(parser->GetErrorMessage() == "Expected 3 but only found 2 positional arguments.", "Check error message is correct.");
	delete parser;
}

XNELO_TEST_CASE(ArgParse, ArgParsePositionalTestChoices)
{
	const char *args[] = {"pos1",
						  "pos2", 
						  "pos3"};
	const int argc = 3;
	XNELO::ARGS::PositionalArgDef p1("NAME1", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING", {"pos1", "p1", "1"});
	XNELO::ARGS::PositionalArgDef p2("NAME2", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p3("NAME3", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	std::vector<XNELO::ARGS::ArgDef*> argVec {&p1, &p2, &p3};
	std::string progName = "ARGPARSEPOSITIONALTEST";

	XNELO::ARGS::ArgParse * parser = new XNELO::ARGS::ArgParse(progName, argVec);
	XNELO_TEST_ASSERT_TRUE(parser->Parse(argc, args), "Parsing positional arguments passed.");
	XNELO_TEST_ASSERT_EQUAL(parser->GetErrorCode(), XNELO::ERRORS::OK, "Check that error code is 'ok'");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[0].Value == "pos1", "Check positional argument 1 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[1].Value == "pos2", "Check positional argument 2 is correct.");
	XNELO_TEST_ASSERT_TRUE(parser->Results.PositionalArgValues[2].Value == "pos3", "Check positional argument 3 is correct.");
	delete parser;
}

XNELO_TEST_CASE(ArgParse, ArgParsePositionalTestChoicesFail)
{
	const char *args[] = {"zzz",
						  "pos2", 
						  "pos3"};
	const int argc = 3;
	XNELO::ARGS::PositionalArgDef p1("NAME1", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING", {"pos1", "p1", "1"});
	XNELO::ARGS::PositionalArgDef p2("NAME2", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	XNELO::ARGS::PositionalArgDef p3("NAME3", XNELO::ARGS::ArgValueTypeEnum::STRING, "TESTING");
	std::vector<XNELO::ARGS::ArgDef*> argVec {&p1, &p2, &p3};
	std::string progName = "ARGPARSEPOSITIONALTEST";

	XNELO::ARGS::ArgParse * parser = new XNELO::ARGS::ArgParse(progName, argVec);
	XNELO_TEST_ASSERT_FALSE(parser->Parse(argc, args), "Parsing positional arguments passed.");
	XNELO_TEST_ASSERT_EQUAL(parser->GetErrorCode(), XNELO::ERRORS::ARG_PARSER_VALUE_NOT_IN_CHOICES, "Check that error code is 'parse value not in choices'");
	XNELO_TEST_ASSERT_TRUE(parser->GetErrorMessage() == "zzz is not one of the choices for 'NAME1' choices are: (pos1, p1, 1)", "Check the error message is as expected");
	delete parser;
}
