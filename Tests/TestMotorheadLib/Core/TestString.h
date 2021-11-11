#pragma once

#include <Motorhead/Common.h>
#include "../Test.h"

using namespace motor;

class EngineTest : public Test {
public:
	bool Initialize() override {
		return true;
	}

	void Run() override {

		do {
			cstr_id = core::InternString(cstr);
			wstr_id = core::InternString(wstr);
			std_string_id = core::InternString(std_string);
			wide_string_id = core::InternString(wide_string);

			cstr_result = core::GetStringFromTable(cstr_id);
			wstr_result = core::GetWideStrFromTable(wstr_id);
			std_string_result = core::GetStringFromTable(std_string_id);
			wide_string_result = core::GetWideStrFromTable(wide_string_id);
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
		std::cout << "cstr: " << cstr_id << " " << cstr_result << "\n";
		std::wcout << "wstr: " << wstr_id << " " << wstr_result << "\n";
		std::cout << "std_string: " << std_string_id << " " << std_string_result << "\n";
		std::wcout << "wide_string: " << wide_string_id << " " << wide_string_result << "\n";
	}

	const charA* cstr{ "1234567890" };
	const charW* wstr{ L"1234567890" };
	core::string std_string{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	core::wstring wide_string{ L"ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

	core::StringID cstr_id{ core::stringid_invalid };
	core::StringID wstr_id{ core::stringid_invalid };
	core::StringID std_string_id{ core::stringid_invalid };
	core::StringID wide_string_id{ core::stringid_invalid };

	core::string cstr_result{ };
	core::wstring wstr_result{ };
	core::string std_string_result{ };
	core::wstring wide_string_result{ };

};
