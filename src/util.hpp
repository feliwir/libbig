#pragma once
#include <fstream>
#include <stdint.h>
namespace libbig
{
    inline uint32_t reverse(uint32_t v)
    {
        _asm {
            mov eax, v
                xchg al, ah
                rol eax, 16
                xchg al, ah
        }
    }

    template <class T>
	inline T read(std::fstream& stream)
	{
		T result;
		stream.read(reinterpret_cast<char*>(&result), sizeof(T));
		return result;
	}

	inline std::string readString(std::fstream& stream)
	{
		std::string buffer;
		char c;
		while ((c = stream.get()) != '\0') {
			buffer += c;
		}

		return buffer;
	}
}