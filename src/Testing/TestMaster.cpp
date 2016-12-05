#include "XneloUtils/Testing/TestMaster.hpp"
#include "XneloUtils/Testing/OutStreamGenerator.hpp"

#include <cstdlib>
#include <iostream>

namespace XNELO
{
	namespace TESTING
	{
		TestMaster * TestMaster::_instance = NULL;

		TestMaster::TestMaster(): _test_classes(), _lone_test_results(), _output_generator(NULL)
		{
			_output_generator = new OutStreamGenerator();

			std::atexit(CleanUp);
			//std::cout << "TestMaster Constructing" << std::endl;
		}

		TestMaster::~TestMaster()
		{
			//std::cout << "TestMaster destructor" << std::endl;
			_test_classes.clear();

			for (std::vector<TestResult*>::iterator it = _lone_test_results.begin(); 
			     it != _lone_test_results.end(); 
			     ++it)
			{
				delete (*it);
			}
			_lone_test_results.clear();

			if (_output_generator != NULL)
				delete _output_generator;
		}

		TestMaster * TestMaster::GetInstance()
		{
			if (_instance == NULL)
				_instance = new TestMaster();

			return _instance;
		}

		void TestMaster::CleanUp()
		{
			delete _instance;
			_instance = NULL;
		}

		void TestMaster::AddTest(Test * to_add)
		{
			_test_classes.push_back(to_add);
		}

		void TestMaster::AddTestResult(TestResult * to_add)
		{
			_lone_test_results.push_back(to_add);
		}

		void TestMaster::RunAllTest()
		{
			int numberPassed = 0;
			int numberFailed = 0;

			for (std::vector<Test*>::iterator it = _test_classes.begin(); it != _test_classes.end(); ++it)
			{
				_output_generator->StartTestCase(*it);
				(*it)->Run();
				if ((*it)->GetNumFailed() > 0)
					++numberFailed; 
				else
					++numberPassed;

				_output_generator->EndTestCase(*it);
			}

			_output_generator->FinalizeTestRun(numberPassed, numberFailed);

			//this->PrintResults();
		}

		void TestMaster::PrintResults()
		{
			if (!_output_generator)
				return;

			for (size_t i = 0; i < _test_classes.size(); ++i)
			{
				Test * temp_test = _test_classes[i];
				for (int j = 0; j < temp_test->GetNumTestResults(); ++j)
				{
					_output_generator->PrintTestResult(temp_test->GetTestResult(j));
				}
			}
		}
	}
}