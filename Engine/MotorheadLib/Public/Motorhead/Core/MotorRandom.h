#pragma once

#include "CoreMinimal.h"

namespace motor::random {

	using mtwister = std::mt19937_64;

	extern mtwister mt_settraversal;

#define MOTORRAND_PRIMES_INVALID	0xffffui16

	u16 FindNextPrime(u16);

	core::vector<u32> PRSetTraversal(u32);

}
