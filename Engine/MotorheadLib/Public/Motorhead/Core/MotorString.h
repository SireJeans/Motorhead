#pragma once

#include "CoreMinimal.h"

#include "Hash.h"

#define INTERN_STR(str)		::motor::core::GenerateHash(##str)

namespace motor::core {

	using String = std::string;
	using WString = std::wstring;
	using StringID = u32;

	constexpr StringID stringid_invalid{ ((StringID)-1) };

	StringID InternString(const core::String);
	StringID InternString(const core::WString);
	StringID InternString(const charA*);
	StringID InternString(const charW*);
	u32 StrLen(const charA*);
	u32 StrLen(const charW*);
	u32 StrByteLen(const charA*);
	u32 StrByteLen(const charW*);
	core::String GetStringFromTable(StringID id);
	core::WString GetWideStrFromTable(StringID id);

	namespace {

		template <core::sizeT I>
		struct CompileHash
		{
			template <core::sizeT N>
			constexpr static inline u32 Generate(const charA(&str)[N])
			{
				return static_cast<u32>(static_cast<u64>(CompileHash<I - 1u>::Generate(str) ^ u32(str[I - 1u])) * 16777619ull);
			}

			template <core::sizeT N>
			constexpr static inline u32 Generate(const charW(&str)[N])
			{
				//u8* tmp = (u8*)str[I - 1u];

				//u32 intermediate = static_cast<u32>(static_cast<u64>(CompileHash<I - 1u>::Generate(str) ^ u32(tmp)) * 16777619ull);
				//result = static_cast<u64>(CompileHash<I - 1u>::Generate(str) ^ u32(str[I - 1u])) * 16777619ull
				return static_cast<u32>(static_cast<u64>(CompileHash<I - 1u>::Generate(str) ^ u32(str[I - 1u])) * 16777619ull);
			}

			template <core::sizeT N>
			constexpr static inline u64 Generate64(const charA(&str)[N])
			{
				return static_cast<u64>(CompileHash<I - 1u>::Generate64(str) ^ u64(str[I - 1u])) * 1099511628211ull;
			}

			template <core::sizeT N>
			constexpr static inline u64 Generate64(const charW(&str)[N])
			{
				return static_cast<u64>(CompileHash<I - 1u>::Generate64(str) ^ u64(str[I - 1u])) * 1099511628211ull;
			}

		};

		template <>
		struct CompileHash<0u>
		{
			template <core::sizeT N>
			constexpr static inline u32 Generate(const charA(&str)[N])
			{
				return 2166136261u;
			}

			template <core::sizeT N>
			constexpr static inline u32 Generate(const charW(&str)[N])
			{
				return 2166136261u;
			}

			template <core::sizeT N>
			constexpr static inline u64 Generate64(const charA(&str)[N])
			{
				return 14695981039346656037ull;
			}

			template <core::sizeT N>
			constexpr static inline u64 Generate64(const charW(&str)[N])
			{
				return 14695981039346656037ull;
			}

		};



		template <typename T>
		struct HashHelper {};

		template <core::sizeT N>
		struct HashHelper<charA[N]>
		{
			constexpr static inline u32 Generate(const charA(&str)[N])
			{
				return CompileHash<N - 1u>::Generate(str);
			}
		};

		template <>
		struct HashHelper<const charA*>
		{
			static inline u32 Generate(const charA* str)
			{
				return hash::Fnv1aHash(str);
			}
		};

		template <core::sizeT N>
		struct HashHelper<charW[N]>
		{
			constexpr static inline u32 Generate(const charW(&str)[N])
			{
				return CompileHash<N - 1u>::Generate(str);
			}
		};

		template <>
		struct HashHelper<const charW*>
		{
			static inline u32 Generate(const charW* str)
			{
				return hash::Fnv1aHash(str);
			}
		};
	}

	template <typename T>
	constexpr static inline u32 GenerateHash(const T& str)
	{
		return HashHelper<T>::Generate(str);
	}


	class Name
	{
	public:
		Name(const charT* str)
			: m_hash(GenerateHash(str))
			, m_str(str)
		{
			// nothing to do
		}

		Name(const Name& rhs)
			: m_hash(rhs.Hash())
			, m_str(rhs.Str())
		{
			// nothing to do
		}

		const u32 Hash() const
		{
			return m_hash;
		}

#if USE_UTF16OR32
		const core::WString Str() const
		{
			return m_str;
		}
#else
		const core::String Str() const
		{
			return m_str;
		}
#endif

	private:
		const u32			m_hash;
#if USE_UTF16OR32
		const core::WString	m_str;
#else
		const core::String	m_str;
#endif
	};
}
