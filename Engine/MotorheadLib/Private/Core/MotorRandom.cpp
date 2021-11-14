#include "Motorhead/Core/CorePCH.h"
#include "Motorhead/Core/CoreCommon.h"

namespace motor::random {

	mtwister mt_settraversal{ (u64)time(nullptr) };

	u16 FindNextPrime(u16 value) {
		if (value >= MOTORMATH_PRIMES_MAXVALUE)
			return MOTORRAND_PRIMES_INVALID;

		for (int i{ 0 }; i < MOTORMATH_PRIMES_SIZE; ++i) {
			if (math::primes[i] > value) {
				return math::primes[i];
			}
		}

		return MOTORRAND_PRIMES_INVALID;
	}

	core::Vector<u32> PRSetTraversal(u16 set_size) {
		u32 skip = 0;
		u32 prime = (u32)FindNextPrime(set_size);
		assert(prime != MOTORRAND_PRIMES_INVALID);
		u32 next_member = 0;


		while (skip % prime == 0) {
			u32 ra = (mt_settraversal() % prime) + 1;
			u32 rb = (mt_settraversal() % prime) + 1;
			u32 rc = (mt_settraversal() % prime) + 1;
			skip = ra * set_size * set_size + rb * set_size + rc;
		}

		core::Vector<u32> result;

		for (u32 i{ 0 }; i < set_size; ++i) {
			do {
				next_member += skip;
				next_member %= prime;
			} while (next_member <= 0 || next_member > set_size);
			result.push_back(next_member - 1);
		}

		return result;
	}


}