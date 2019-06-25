#pragma once

#include <string>
#include <map>

#include "class_descriptor.h"

namespace Stringer
{
	std::string toString(size_t hash, const void *p);

	template <typename T>
	std::string toString(const T &obj)
	{
		return toString(typeid(T).hash_code(), &obj);
	}


	void addDescriptor(size_t hash, ClassDescriptor descriptor);

	template <typename T>
	void addDescriptor(ClassDescriptor descriptor)
	{
		addDescriptor(typeid(T).hash_code(), descriptor);
	}

	template<typename T_CLASS, typename T_RETVAL>
	Field makeField(std::string name, T_RETVAL(T_CLASS::*getter)() const, std::function<std::string(T_RETVAL)> f_to_string)
	{
		auto to_string = [=](const void* p) -> std::string
		{
			return f_to_string(std::invoke(getter, reinterpret_cast<const T_CLASS*>(p)));
		};

		return Field(name, to_string);
	}
};
