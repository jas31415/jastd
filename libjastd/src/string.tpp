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
	
	/**
	 *  @brief  Merges strings from a list with an optional separator between them.
	 * 	@param strs  Object at the start of the array.
	 *  @param count  Number of strings to join.
	 *  @param between  Characters to put between each item. (default "")
	 * 	@return  The new string.
	 */
	template<typename str_t>
	str_t concat(const str_t& strs, size_t count, const char* between)
	{
		str_t retstr = strs;
		
		for (int idx = 1; idx < count; idx++)
		{		
			retstr += between + (&strs)[idx];
		}
		
		return retstr;
	}
	
#endif /* 98 */
};