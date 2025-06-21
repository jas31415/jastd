#pragma once
#include <vector>
#include "string.hpp"

class UnitTesterBase
{
public:
	virtual void PerformTests() = 0;
	
protected:
	void LogSuccess(jastd::string& testName);
	void LogFailure(jastd::string& testName, const jastd::string& details);
	
private:
	std::vector<jastd::string> m_TestsLog;
};

// Unit tester for String classes
template<typename StringType>
class StringTester : UnitTesterBase
{
public:
	virtual void PerformTests();

private:
	void NewString_Is_Empty();
};
