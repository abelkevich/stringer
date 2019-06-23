#include "class_descriptor.h"

namespace Stringer
{
	ClassDescriptor::ClassDescriptor(std::string class_name, std::initializer_list<Field> fields)
		: m_class_name(class_name)
	{
		for (Field f : fields)
		{
			m_fields.push_back(f);
		}
	}

	std::string ClassDescriptor::toString(const void* p)
	{
		std::string result;
		for (auto f : m_fields)
		{
			result += f.toString(p);
		}

		return result;
	}
}