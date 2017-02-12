#pragma once
#include <streambuf>
#include <libbig/big.hpp>

namespace libbig
{
    class EntryStream : public std::streambuf
    {
        public:
            EntryStream(Big& arch, Big::Entry& entry): m_arch(arch), m_entry(entry)
            {

            }

            virtual int overflow(int c)
            {

            }

            virtual int underflow()
            {

            }
        private:
            Big& m_arch;
            Big::Entry& m_entry;
            uint32_t m_pos;
    };
}