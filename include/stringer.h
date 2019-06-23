#pragma once

#include <string>
#include <map>

#include "class_descriptor.h"

namespace Stringer
{
	static std::map<size_t, ClassDescriptor> m_map_class_descriptors = std::map<size_t, ClassDescriptor>();

	template <typename T>
	std::string toString(const T &obj)
	{
		auto it = m_map_class_descriptors.find(typeid(T).hash_code());

		if (it == m_map_class_descriptors.end()) return "Cannot find rules for class!";

		return it->second.toString(&obj);
	}

	template <typename T>
	void addDescriptor(ClassDescriptor descriptor)
	{
		auto record = std::make_pair(typeid(T).hash_code(), descriptor);
		m_map_class_descriptors.insert(record);
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
