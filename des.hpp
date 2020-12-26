#ifndef des_hpp
#define des_hpp

class des
{
	private:
		
		static const short init_permutation[64];
		static const short final_permutation[64];
		static const short expanding_permutation[48];
		
		static const short first_key_permutation[56];
		static const short second_key_permutation[48];
		static const short p_permutation[32];
		
		static const short s1[4][16];
		static const short s2[4][16];
		static const short s3[4][16];
		static const short s4[4][16];
		static const short s5[4][16];
		static const short s6[4][16];
		static const short s7[4][16];
		static const short s8[4][16];
		void init_sTables(void);
	public:
		
	
};

#endif