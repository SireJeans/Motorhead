#pragma once

#include "CoreMinimal.h"

namespace motor::core {

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;

	template<typename T>
	using UniquePtr = std::unique_ptr<T>;

	template<typename T>
	using WeakPtr = std::weak_ptr<T>;
}
