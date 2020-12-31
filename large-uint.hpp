#ifndef large_uint_hpp
#define large_uint_hpp

#include "types.hpp"

class large_uint
{
	private:
		uint32 *value;
		uint16 length;
		bool zero(void) const;
		uint16 get_length(void);
		
		int comp(const large_uint &) const;
		int comp(uint32) const;
		
		void add (const large_uint &);
		void add (const uint32 &);
		
		void sub (const large_uint &);
		void sub (const uint32 &);
		
		void multi (const large_uint &);
		void multi (const uint32 &);
		
		large_uint div(const large_uint &);
		uint32 div(uint32);
		
		void left_shift (const large_uint &);
		void left_shift (const uint32 &);
		
		void right_shift (const large_uint &);
		void right_shift (const uint32 &);

	public:
		large_uint(uint16);
		large_uint(const large_uint &);
		~large_uint();
		void change_length(uint16);
		
		void set_last_uint32(uint32);
		
		void dump(void) const;
		
		static void pow( large_uint &,  large_uint &, large_uint &, large_uint &);
		static void pow( large_uint &,  large_uint &, large_uint &);
		//static void sqrt(const large_uint &, large_uint &);
		
		void operator = (const large_uint &);
		void operator = (uint32);

		large_uint operator + (const large_uint &) const;//todo:dodac int+obj
		large_uint operator + (const uint32&) const;
		large_uint operator - (const large_uint &) const;
		large_uint operator - (const uint32&) const;
		large_uint operator * (const large_uint &) const;
		large_uint operator * (const uint32&) const;
		large_uint operator / (const large_uint &) const;
		large_uint operator / (const uint32&) const;
		large_uint operator % (const large_uint &) const;
		large_uint operator % (const uint32&) const;
		
		
		large_uint operator &  (const large_uint &);
		large_uint operator &  (const long &);
		large_uint operator |  (const large_uint &);
		large_uint operator |  (const long &);
		large_uint operator ~  ();
		large_uint operator ^  (const large_uint &);
		large_uint operator ^  (const long &);
		//large_uint operator << (const large_uint &);
		large_uint operator << (const uint64 &);
		//large_uint operator >> (const large_uint &);
		large_uint operator >> (const uint64 &);

		bool operator && (const large_uint &) const;
		bool operator && (const uint32&) const;
		bool operator || (const large_uint &) const;
		bool operator || (const uint32&) const;
		bool operator !  () const;

		uint32 operator [] (uint16);
		
		explicit operator uint32 ();
		explicit operator uint64 ();

		large_uint& operator ++ ();//prefix
		large_uint& operator -- ();
		large_uint  operator ++ (int);//postfix
		large_uint  operator -- (int);

		//void operator >>= (const large_uint &);
		void operator >>= (const long &);
		//void operator <<= (const large_uint &);
		void operator <<= (const long &);
		/*void operator &=  (const large_uint &);
		void operator &=  (const long &);
		void operator |=  (const large_uint &);
		void operator |=  (const long &);
		void operator ^=  (const large_uint &);
		void operator ^=  (const long &);*/

		void operator += (const large_uint &);
		void operator += (uint32);
		void operator -= (const large_uint &);
		void operator -= (uint32);
		void operator *= (const large_uint &);
		void operator *= (uint32);
		void operator /= (const large_uint &);
		void operator /= (uint32);
		void operator %= (const large_uint &);
		void operator %= (uint32);

		bool operator == (const large_uint &) const;
		bool operator == (const uint32&) const;
		bool operator != (const large_uint &) const;
		bool operator != (const uint32&n) const;
		bool operator >  (const large_uint &) const;
		bool operator >  (const uint32&) const;
		bool operator >= (const large_uint &) const;
		bool operator >= (const uint32&) const;
		bool operator <  (const large_uint &) const;
		bool operator <  (const uint32&) const;
		bool operator <= (const large_uint &) const;
		bool operator <= (const uint32&) const;

};

/*large_uint operator + (const uint32&, const large_uint &);
large_uint operator - (const uint32&, const large_uint &);
large_uint operator / (const uint32&, const large_uint &);
large_uint operator * (const uint32&, const large_uint &);
large_uint operator % (const uint32&, const large_uint &);

large_uint operator & (const uint32&, const large_uint &);
large_uint operator | (const uint32&, const large_uint &);
large_uint operator ^ (const uint32&, const large_uint &);
large_uint operator << (const uint32&, const large_uint &);
large_uint operator >> (const uint32&, const large_uint &);

bool operator && (const uint32&, const large_uint &);
bool operator || (const uint32&, const large_uint &);

uint32operator >>= (const uint32&, const large_uint &);
uint32operator <<= (const uint32&, const large_uint &);
uint32operator &= (const uint32&, const large_uint &);
uint32operator |= (const uint32&, const large_uint &);
uint32operator ^= (const uint32&, const large_uint &);*/

bool operator == (const uint32&, const large_uint &);
bool operator != (const uint32&, const large_uint &);
bool operator >  (const uint32&, const large_uint &);
bool operator >= (const uint32&, const large_uint &);
bool operator <  (const uint32&, const large_uint &);
bool operator <= (const uint32&, const large_uint &);


#endif