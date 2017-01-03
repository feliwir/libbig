#include <libbig/manager.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	libbig::Manager mngr;
	mngr.AddBig("test.big");
	auto big = mngr.GetArchive("test.big");

	for (const auto& e : big->ListEntries())
	{
		std::cout << e << ": " << std::endl;
		std::cout << mngr.GetEntry(e) << std::endl;
	}

	return 0;
}