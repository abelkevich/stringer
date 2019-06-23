#include <list>
#include <map>
#include <typeinfo>
#include <functional>
#include <string>
#include <iostream>
#include <tuple>

class Sample final
{
private:
	uint16_t m_id;
	std::string m_name;

public:
	Sample(uint16_t id, std::string name)
		: m_id(id)
		, m_name(name)
	{

	}

	uint16_t getId(bool flag) const { return flag ? m_id : 9999; }
	std::string getName() const { return m_name; }

	void setId(uint16_t id) { m_id = id; }
};

class Field
{
private:
	std::string m_name;
	std::function<std::string(const void*)> m_function_to_string;

public:
	Field(std::string name, std::function<std::string(const void*)> function_to_string)
		: m_name(name)
		, m_function_to_string(function_to_string)
	{

	}

	std::string toString(const void* p)
	{
		return m_name + m_function_to_string(p);
	}
};

class ClassDescriptor
{
private:
	std::string m_class_name;
	std::list<Field> m_fields;

public:
	ClassDescriptor(std::string class_name, std::initializer_list<Field> fields)
		: m_class_name(class_name)
	{
		for (Field f : fields)
		{
			m_fields.push_back(f);
		}
	}

	std::string toString(const void* p)
	{
		std::string result; 
		for (auto f : m_fields)
		{
			result += f.toString(p);
		}

		return result;
	}
};

class Parsable
{
private:
	static std::map<size_t, ClassDescriptor> m_map_class_descriptors;

public:

	template <typename T>
	static std::string toString(const T &obj)
	{
		auto it = m_map_class_descriptors.find(typeid(T).hash_code());

		if (it == m_map_class_descriptors.end()) return "Cannot find rules for class!";

		return it->second.toString(&obj);
	}

	template <typename T>
	static void addDescriptor(ClassDescriptor descriptor)
	{
		auto record = std::make_pair(typeid(T).hash_code(), descriptor);
		m_map_class_descriptors.insert(record);
	}
};

std::map<size_t, ClassDescriptor> Parsable::m_map_class_descriptors = std::map<size_t, ClassDescriptor>();

template<typename T_CLASS, typename T_RETVAL, typename... TARGS>
Field makeField(std::string name, std::function<std::string(T_RETVAL)> f_to_string, T_RETVAL(T_CLASS::*getter)(TARGS...) const, TARGS... args)
{
	auto to_string = [=](const void* p) -> std::string 
		{ 
			return f_to_string(std::invoke(getter, reinterpret_cast<const T_CLASS*>(p), std::forward<TARGS>(args)...)); 
		};

	return Field(name, to_string);
}

int main()
{
	Sample sample_0(0, "zero");

	auto std_to_string = [=](auto val) -> std::string {return std::to_string(val); };
	auto none = [=](auto val) -> std::string { return val; };

	bool flag = false;

	Parsable::addDescriptor<Sample>
	( 
		ClassDescriptor("Sample",
			{ makeField<Sample, uint16_t, bool>("id", std_to_string, &Sample::getId, false)
			, makeField<Sample, std::string>("name", none, &Sample::getName) })
	);

	std::cout << Parsable::toString(sample_0) << std::endl;

	sample_0.setId(1);

	std::cout << Parsable::toString(sample_0) << std::endl;
}