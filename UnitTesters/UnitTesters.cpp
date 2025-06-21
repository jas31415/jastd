#include "UnitTesters.hpp"

/*
	UnitTesterBase
*/

void UnitTesterBase::LogSuccess(jastd::string& testName)
{
	m_TestsLog.push_back(testName + "\n\tSuccess.");
}

void UnitTesterBase::LogFailure(jastd::string& testName, const jastd::string& details)
{
	m_TestsLog.push_back(testName + "\n\tFailure: " + details);
}

/*
	StringTester
*/

template<typename StringType>
void StringTester<StringType>::PerformTests()
{
	
}

template<typename StringType>
void StringTester<StringType>::NewString_Is_Empty()
{
	StringType
}