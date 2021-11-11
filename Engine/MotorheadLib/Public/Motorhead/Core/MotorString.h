#pragma once

#include <string>

#include "PrimitiveTypes.h"

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



}
