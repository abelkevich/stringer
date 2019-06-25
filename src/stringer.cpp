#include "stringer.h"

namespace Stringer {
	static std::map<size_t, ClassDescriptor> g_map_class_descriptors = std::map<size_t, ClassDescriptor>();

	std::string toString(size_t hash, const void *p)
	{
		auto it = g_map_class_descriptors.find(hash);

		if (it == g_map_class_descriptors.end()) return "Cannot find rules for class!";

		return it->second.toString(p);
	}


	void addDescriptor(size_t hash, ClassDescriptor descriptor)
	{
		auto record = std::make_pair(hash, descriptor);
		g_map_class_descriptors.insert(record);
	}

}