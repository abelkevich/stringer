#pragma once

#include <string>
#include <list>

#include "field.h"

namespace Stringer
{
	class ClassDescriptor
	{
	private:
		std::string m_class_name;
		std::list<Field> m_fields;

	public:
		ClassDescriptor(std::string class_name, std::initializer_list<Field> fields);

		std::string toString(const void* p);
	};
}