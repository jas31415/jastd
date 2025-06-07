#include "string.hpp"

namespace jastd
{
	template<typename str_t, class param_t>
	str_t to_string(const param_t& param)
	{
		return static_cast<std::ostringstream*>(&(std::ostringstream() << param))->str();
	}
};