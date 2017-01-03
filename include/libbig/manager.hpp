#pragma once
#include "big.hpp"
#include <string>
#include <map>
#include <memory>
#include <stdint.h>

namespace libbig
{
	class Manager
	{
	public:
		void AddBig(const std::string& file);
		//get big archive
		std::shared_ptr<Big> GetArchive(const std::string& name);
		//get entry binary
		uint8_t* GetEntry(const std::string& entry,uint32_t& size);
		//get entry as string
		std::string GetEntry(const std::string& entry);
	private:
		std::map<std::string,std::shared_ptr<Big>> m_archives;
	};
}