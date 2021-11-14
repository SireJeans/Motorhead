#include "Motorhead/Core/CorePCH.h"
#include "Motorhead/Core/CoreCommon.h"

namespace motor::core {

	namespace {

		core::hash_map<StringID, core::String> string_table;
		core::hash_map<StringID, core::WString> wstring_table;
	}

	u32 StrLen(const charA* str) {
		assert(str != nullptr);
		u32 len = 0;
		while (str[len] != '\0') {
			++len;
		}
		return len;
	}

	u32 StrLen(const charW* str) {
		assert(str != nullptr);
		u32 len = 0;
		while (str[len] != '\0') {
			++len;
		}
		return len;
	}

	u32 StrByteLen(const charA* str) {
		assert(str != nullptr);
		return StrLen(str);
	}

	u32 StrByteLen(const charW* str) {
		assert(str != nullptr);
		return StrLen(str) * sizeof(charW);
	}

	core::String GetStringFromTable(StringID id) {
		assert(id != stringid_invalid);
		return string_table[id];
	}

	core::WString GetWideStrFromTable(StringID id) {
		assert(id != stringid_invalid);
		return wstring_table[id];
	}


	StringID InternString(const core::String str) {
		StringID id{ stringid_invalid };

		id = (StringID)hash::GetCrc(0, (u8*)str.c_str(), str.size());

		if (!string_table.contains(id)) {
			string_table[id] = core::String(str);
		}

		return id;
	}

	StringID InternString(const core::WString str) {
		StringID id{ stringid_invalid };

		id = (StringID)hash::GetCrc(0, (u8*)str.c_str(), str.size());

		if (!string_table.contains(id)) {
			wstring_table[id] = core::WString(str);
		}

		return id;
	}

	StringID InternString(const charA* str) {
		assert(str != nullptr);
		StringID id{ stringid_invalid };

		u32 len = StrByteLen(str);
		id = (StringID)hash::GetCrc(0, (u8*)str, len);

		if (!string_table.contains(id)) {
			string_table[id] = core::String(str);
		}
		
		return id;
	}

	StringID InternString(const charW* str) {
		assert(str != nullptr);
		StringID id{ stringid_invalid };

		u32 len = StrByteLen(str);
		id = (StringID)hash::GetCrc(0, (u8*)str, len);

		if (!string_table.contains(id)) {
			wstring_table[id] = core::WString(str);
		}

		return id;
	}


}