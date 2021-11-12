#pragma once

#include "StdIncludes.h"

namespace motor::core {

	template<typename T>
	using vector = std::vector<T>;

	template<typename T>
	using deque = std::deque<T>;

	template<typename K, typename V>
	using map = std::map<K, V>;

	template<typename H, typename V>
	using hash_map = std::unordered_map<H, V>;

	template<typename T>
	using List = std::list<T>;
}
