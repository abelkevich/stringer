#include <functional>
#include <string>
#include <iostream>

#include "stringer.h"

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

	uint16_t getId() const { return m_id;}
	std::string getName() const { return m_name; }

	void setId(uint16_t id) { m_id = id; }
};

int main()
{
	using namespace Stringer;

	auto std_to_string = [=](auto val) {return std::to_string(val); };
	auto none = [=](auto val) { return val; };

	addDescriptor<Sample>
	( 
		ClassDescriptor("Sample",
			{ makeField<Sample, uint16_t>("id", &Sample::getId, std_to_string)
			, makeField<Sample, std::string>("name", &Sample::getName, none) })
	);

	Sample sample_0(0, "zero");

	std::cout << toString(sample_0) << std::endl;

	sample_0.setId(1);

	std::cout << toString(sample_0) << std::endl;
}