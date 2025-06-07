#include "string.hpp"
#include <sstream>

namespace jastd
{
#if USING_CPP(98)

	/**
	 *  @brief  Turns a variable into a string.
	 */
	template<class param_t>
	std::string to_string(const param_t& param)
	{
		return static_cast<std::ostringstream*>(&(std::ostringstream() << param))->str();
	}
	template<class str_t, class param_t>
	
	str_t to_string(const param_t& param)
	{
		return static_cast<std::ostringstream*>(&(std::ostringstream() << param))->str();
	}

#endif /* 98 */
};