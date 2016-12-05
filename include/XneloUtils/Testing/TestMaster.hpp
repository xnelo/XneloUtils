#ifndef ___XNELO_TESTING_TESTMASTER__HPP__10_06_2016___
#define ___XNELO_TESTING_TESTMASTER__HPP__10_06_2016___

#include "../Config.hpp"
#include "IReportGenerator.hpp"
#include "Test.hpp"
#include <string>
#include <vector>

#include <iostream> //for testing remove when creating build

namespace XNELO
{
	namespace TESTING
	{
		class TestMaster
		{
		private:
			std::vector<Test*> _test_classes;
			std::vector<TestResult*> _lone_test_results;
			IReportGenerator * _output_generator;

			static TestMaster * _instance;
			static void CleanUp();

			XNELO_API TestMaster();

		public:
			XNELO_API ~TestMaster();

			XNELO_API static TestMaster * GetInstance();
			
			template<typename T>
			XNELO_API static TestResult * CheckEqual(T condition, T expected, const char * description);
			template<typename T>
			XNELO_API static TestResult * CheckNotEqual(T condition, T expected, const char * description);

			/**
			  * Any 'Test' class added with this method will **NOT** be deleted by the 'TestMaster' instance.
			  */
			XNELO_API void AddTest(Test * to_add);

			/**
			  * Any 'TestResult' class added with this function will be deleted by this class.
			  */
			XNELO_API void AddTestResult(TestResult * to_add);

			XNELO_API IReportGenerator * GetReportGenerator();

			XNELO_API void RunAllTest();

			XNELO_API void PrintResults();
		};
	}
}

inline XNELO::TESTING::IReportGenerator * XNELO::TESTING::TestMaster::GetReportGenerator()
{
	return _output_generator;
}

template<typename T>
inline XNELO::TESTING::TestResult * XNELO::TESTING::TestMaster::CheckEqual(T condition, T expected, const char * description)
{
	XNELO::TESTING::TestResult * result = new XNELO::TESTING::TestResult();

	result->passed = (condition == expected);
	result->name = new char[std::strlen(description) + 1];
	std::strcpy(result->name, description);

	return result;
}

template<typename T>
inline XNELO::TESTING::TestResult * XNELO::TESTING::TestMaster::CheckNotEqual(T condition, T expected, const char * description)
{
	XNELO::TESTING::TestResult * result = new XNELO::TESTING::TestResult();

	result->passed = (condition != expected);
	result->name = new char[std::strlen(description) + 1];
	std::strcpy(result->name, description);

	return result;
}

#endif //___XNELO_TESTING_TESTMASTER__HPP__10_06_2016___
