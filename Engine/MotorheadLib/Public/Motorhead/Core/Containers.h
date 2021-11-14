#pragma once

#include "CoreMinimal.h"

namespace motor::core {

	template<typename T>
	using Vector = std::vector<T>;

	template<typename T>
	using Deque = std::deque<T>;

	template<typename K, typename V>
	using Map = std::map<K, V>;

	template<typename H, typename V>
	using HashMap = std::unordered_map<H, V>;

	template<typename T>
	using List = std::list<T>;
}
