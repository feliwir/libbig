#include <libbig/manager.hpp>
using namespace libbig;

void Manager::AddBig(const std::string& name)
{
	//check if archive does exist
	auto& it = m_archives.find(name);
	if (it != m_archives.end())
		return;

	auto archive = std::make_shared<Big>();
	archive->Load(name);
	m_archives[name] = archive;
}

std::shared_ptr<Big> Manager::GetArchive(const std::string & name)
{
	return m_archives[name];
}

uint8_t * libbig::Manager::GetEntry(const std::string & entry, uint32_t& size)
{
	uint8_t* data = nullptr;
	for (auto& archive : m_archives)
	{
		data = archive.second->GetEntry(entry, size);
		if (data)
			break;
	}

	if (data == nullptr)
	{
		//could not be found in any archives. Look on the drive now:
		std::ifstream fin(entry, std::ios::binary | std::ios::in);
		if (fin.fail())
			return data;

		fin.seekg(std::ios::end);
		size = fin.tellg();
		fin.seekg(std::ios::beg);
		data = new uint8_t[size];
		fin.read(reinterpret_cast<char*>(data), size);
	}

	return data;
}

std::string libbig::Manager::GetEntry(const std::string & entry)
{
	std::string text;

	for (auto& archive : m_archives)
	{
		text = archive.second->GetEntry(entry);
		if (text.size()>0)
			break;
	}

	if (text.size() == 0)
	{
		//could not be found in any archives. Look on the drive now:
		std::ifstream fin(entry, std::ios::binary| std::ios::in);
		if (fin.fail())
			return text;

		text = std::string((std::istreambuf_iterator<char>(fin)),
			std::istreambuf_iterator<char>());
	}
	

	return text;
}
