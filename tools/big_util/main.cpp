#include <libbig/big.hpp>
#include <iostream>
#include <iomanip>
#include <cxxopts.hpp>
using namespace libbig;

int main(int argc, char** argv)
{
	//option parsing
	cxxopts::Options options("Big util", "A program to work with EA big archives");
	options.add_options()
		("e,extract", "Extract the arcchive")
		("p,pack", "Pack a folder structure to a big archive")
		("f,file", "Name of the archive that should be extracted/generated", cxxopts::value<std::string>())
		("s,search","Search for an entry", cxxopts::value<std::string>())
		("l,list","List all entries");

	options.parse(argc, argv);
	if(options.count("file")==0)
	{
		std::cout << "Please specify an input file." << std::endl << options.help() << std::endl;
		return EXIT_FAILURE;
	}

	bool extract = options["pack"].as<bool>();
	bool pack = options["pack"].as<bool>();
	bool list = options["list"].as<bool>();
	std::string file = options["file"].as<std::string>();
	std::string search = options["search"].as<std::string>();
	bool bsearch = search.size()>0;
	
	if(!(pack^extract^list^bsearch))
	{
		std::cout << "Please specify exactly one operation that should be executed" << std::endl
		<< options.help() << std::endl;
	}

	Big arch;
	if(!pack)
	{
		if(!arch.Load(file))
		{
			std::cout << "Failed to open "<< file << std::endl;
			return -1;
		}
		if(list)
		{
			std::cout.fill('-');
			std::cout << "NAME" << std::setw(70) << "SIZE" << std::endl;
			std::cout.fill(' ');
			for (const auto& e : arch.ListEntries())
			{
				Big::Entry info = arch.GetInfo(e);
				std::cout<< std::left << std::setw(70) << e << std::right << " " <<info.Size << std::endl;
			}
		}
	}
	

	return 0;
}