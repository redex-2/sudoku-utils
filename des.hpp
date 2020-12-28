#ifndef des_hpp
#define des_hpp

#include <string>

class des
{
	private:
		
		static const short first_permutation_table[64];
		static const short final_permutation_table[64];
		static const short expanding_permutation_table[48];
		
		static const short first_key_permutation_table[56];
		static const short second_key_permutation_table[48];
		static const short p_permutation_table[32];
		
		static const short s1[4][16];
		static const short s2[4][16];
		static const short s3[4][16];
		static const short s4[4][16];
		static const short s5[4][16];
		static const short s6[4][16];
		static const short s7[4][16];
		static const short s8[4][16];
		
		unsigned int leftKey;
		unsigned int rightKey;
		unsigned int left;
		unsigned int right;
		unsigned int temp_right;
		unsigned long long key48;
		unsigned long long key56;
		unsigned long long temp;
		unsigned long long keys[16];
		unsigned char row;
		unsigned char col;
		unsigned char i;
		char j;
		
		
		void split (unsigned long long, unsigned int *, unsigned int * );
		void splitKey (unsigned long long, unsigned int *, unsigned int * );
		void genKeyTable(unsigned long long, unsigned long long [16] );
		unsigned int sBox (unsigned long long);
		
		unsigned long long first_permutation( unsigned long long );
		unsigned long long final_permutation( unsigned long long );
		unsigned long long expand_permutation( unsigned int );
		unsigned int p_permutation( unsigned int );
		unsigned long long first_key_permutation( unsigned long long );
		unsigned long long second_key_permutation( unsigned long long );
	public:
		unsigned long long encrypt (unsigned long long, unsigned long long );
		unsigned long long decrypt (unsigned long long, unsigned long long );
};

#endif