#pragma once
#include <vector>
#include "macros.hpp"
#include "string.hpp"

class UnitTesterBase
{
public:
	virtual void PerformTests() = 0;
	
protected:
	void AddFailure(const jastd::string98& testName, const jastd::string98& reason);

private:
	std::vector<jastd::string98> m_FailuresLog;
};

// Unit tester for String classes
template<typename string_type>
class StringTester : UnitTesterBase
{
public:
	virtual void PerformTests();

private:
	void NewString_Is_Empty();
};
