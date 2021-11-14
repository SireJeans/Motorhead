#include "Motorhead/Core/CoreCommon.h"

namespace motor::core {

	namespace {

		core::hash_map<StringID, string> string_table;
		core::hash_map<StringID, wstring> wstring_table;
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

	core::string GetStringFromTable(StringID id) {
		assert(id != stringid_invalid);
		return string_table[id];
	}

	core::wstring GetWideStrFromTable(StringID id) {
		assert(id != stringid_invalid);
		return wstring_table[id];
	}


	StringID InternString(const string str) {
		StringID id{ stringid_invalid };

		id = (StringID)hash::GetCrc(0, (u8*)str.c_str(), str.size());

		if (!string_table.contains(id)) {
			string_table[id] = core::string(str);
		}

		return id;
	}

	StringID InternString(const wstring str) {
		StringID id{ stringid_invalid };

		id = (StringID)hash::GetCrc(0, (u8*)str.c_str(), str.size());

		if (!string_table.contains(id)) {
			wstring_table[id] = core::wstring(str);
		}

		return id;
	}

	StringID InternString(const charA* str) {
		assert(str != nullptr);
		StringID id{ stringid_invalid };

		u32 len = StrByteLen(str);
		id = (StringID)hash::GetCrc(0, (u8*)str, len);

		if (!string_table.contains(id)) {
			string_table[id] = core::string(str);
		}
		
		return id;
	}

	StringID InternString(const charW* str) {
		assert(str != nullptr);
		StringID id{ stringid_invalid };

		u32 len = StrByteLen(str);
		id = (StringID)hash::GetCrc(0, (u8*)str, len);

		if (!string_table.contains(id)) {
			wstring_table[id] = core::wstring(str);
		}

		return id;
	}


}