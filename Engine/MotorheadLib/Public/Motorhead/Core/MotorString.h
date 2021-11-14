#pragma once

#include "CoreMinimal.h"

#include "Hash.h"

#define INTERN_STR(str)		::motor::core::GenerateHash(##str)

namespace motor::core {

	using string = std::string;
	using wstring = std::wstring;
	using StringID = u32;

	constexpr StringID stringid_invalid{ ((StringID)-1) };

	StringID InternString(const string);
	StringID InternString(const wstring);
	StringID InternString(const charA*);
	StringID InternString(const charW*);
	u32 StrLen(const charA*);
	u32 StrLen(const charW*);
	u32 StrByteLen(const charA*);
	u32 StrByteLen(const charW*);
	core::string GetStringFromTable(StringID id);
	core::wstring GetWideStrFromTable(StringID id);

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
				return static_cast<u32>(static_cast<u64>(CompileHash<I - 1u>::Generate(str) ^ u32(str[I - 1u])) * 16777619ull);
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
		const core::wstring Str() const
		{
			return m_str;
		}
#else
		const core::string Str() const
		{
			return m_str;
		}
#endif

	private:
		const u32			m_hash;
#if USE_UTF16OR32
		const core::wstring	m_str;
#else
		const core::string	m_str;
#endif
	};
}
