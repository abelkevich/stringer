#pragma once
#include <string>
#include <functional>

namespace Stringer
{
	class Field
	{
	private:
		std::string m_name;
		std::function<std::string(const void*)> m_function_to_string;

	public:
		Field(std::string name, std::function<std::string(const void*)> function_to_string);
		std::string toString(const void* p);
	};
}