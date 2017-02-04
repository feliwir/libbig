#include <libbig/big.hpp>
#include <iostream>
using namespace libbig;

int main(int argc, char** argv)
{
	Big arch;
	if(!arch.Load("test.big"))
	{
		std::cout << "Failed to open test.big!" << std::endl;
		return -1;
	}

	for (const auto& e : arch.ListEntries())
	{
		std::cout << e << ": " << std::endl;
		std::cout << arch.GetEntry(e) << std::endl;
	}

	return 0;
}