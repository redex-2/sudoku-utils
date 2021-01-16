#ifndef hash_hpp
#define hash_hpp

#include "types.hpp"

class _hash
{
	private:
		uint64 i;
	protected:
		void split_message(const char *message, uint64 len, uint32** &out, uint64 &out_len, uint16 block_size);
		void split_file(const char *file_name, uint32** &out, uint64 &out_len, uint16 block_size);
};

class _reverse_hash
{
	private:
		uint64 i;
	protected:
		void split_message(const char *message, uint64 len, uint32** &out, uint64 &out_len, uint16 block_size);
		void split_file(const char *file_name, uint32** &out, uint64 &out_len, uint16 block_size);
};

#endif