#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <mutex>

namespace libbig
{
	class Big
	{
	private:
		enum Version
		{
			CC		= 0,
			BFME	= 1,
		};

		struct Entry
		{
			uint32_t	Size;
			uint32_t	Offset;
		};
	public:
		bool Load(const std::string& name);

		//get entry binary
		uint8_t* GetEntry(const std::string& entry, uint32_t& size);
		//get entry as string
		std::string GetEntry(const std::string& entry);

		std::vector<std::string> ListEntries();
	private:
		std::mutex					m_mutex;
		std::map<std::string,Entry>	m_entries;
		std::fstream				m_stream;
		uint32_t					m_size;
		uint32_t					m_numEntries;
		Version						m_version;
	};
}