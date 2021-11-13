#pragma once

#include "CoreMinimal.h"

namespace motor::core {

	template <typename T>
	class Delegate {};

	template <typename R, typename... Args>
	class Delegate<R(Args...)>
	{
		typedef R(*ProxyFunction)(void*, Args...);

		template <R(*Function)(Args...)>
		static inline R FunctionProxy(void*, Args... args)
		{
			return Function(std::forward<Args>(args)...);
		}

		template <class C, R(C::* Function)(Args...)>
		static inline R MethodProxy(void* instance, Args... args)
		{
			return (static_cast<C*>(instance)->*Function)(std::forward<Args>(args)...);
		}

		template <class C, R(C::* Function)(Args...) const>
		static inline R ConstMethodProxy(void* instance, Args... args)
		{
			return (static_cast<const C*>(instance)->*Function)(std::forward<Args>(args)...);
		}

	public:
		Delegate()
			: _instance(nullptr)
			, _proxy(nullptr)
		{
		}

		template <R(*Function)(Args...)>
		void Bind(void)
		{
			_instance = nullptr;
			_proxy = &FunctionProxy<Function>;
		}

		template <class C, R(C::* Function)(Args...)>
		void Bind(C* instance)
		{
			_instance = instance;
			_proxy = &MethodProxy<C, Function>;
		}

		template <class C, R(C::* Function)(Args...) const>
		void Bind(const C* instance)
		{
			_instance = const_cast<C*>(instance);
			_proxy = &ConstMethodProxy<C, Function>;
		}

		R Invoke(Args... args) const
		{
			assert((_proxy != nullptr) && "Cannot invoke unbound Delegate. Call Bind() first.");
			return _proxy(_instance, std::forward<Args>(args)...);
		}

	private:
		void* _instance;
		ProxyFunction _proxy;
	};

}
