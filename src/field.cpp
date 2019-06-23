#include "field.h"

namespace Stringer
{
	Field::Field(std::string name, std::function<std::string(const void*)> function_to_string)
		: m_name(name)
		, m_function_to_string(function_to_string)
	{

	}

	std::string Field::toString(const void* p)
	{
		return m_name + m_function_to_string(p);
	}
}