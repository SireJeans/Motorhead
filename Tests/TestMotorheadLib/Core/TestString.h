#pragma once

#include "Motorhead/Common.h"
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

			std::cout << "\nGenerateHash (compile time):\n";
			std::cout << core::GenerateHash("1234567890") << " 1234567890\n";
			std::wcout << core::GenerateHash(L"1234567890") << L" L1234567890\n";
			std::cout << core::GenerateHash("ABCDEFGHIJKLMNOPQRSTUVWXYZ") << " ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
			std::wcout << core::GenerateHash(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ") << L" LABCDEFGHIJKLMNOPQRSTUVWXYZ\n";

			std::cout << "\nGenerateHash (pointers):\n";
			std::cout << core::GenerateHash(cstr) << " " << cstr << "\n";
			std::wcout << core::GenerateHash(wstr) << " " << wstr << "\n";
			std::cout << core::GenerateHash(std_string.c_str()) << " " << std_string.c_str() << "\n";
			std::wcout << core::GenerateHash(wide_string.c_str()) << " " << wide_string.c_str() << "\n";

			std::cout << STRHASH32("CACA") << " CACA" << "\n";
			std::cout << WSTRHASH32("CACA") << " CACA" << "\n";
			std::cout << TXTHASH32("CACA") << " CACA" << "\n";
			std::cout << STRHASH64("CACA") << " CACA" << "\n";
			std::cout << WSTRHASH64("CACA") << " CACA" << "\n";
			std::cout << TXTHASH64("CACA") << " CACA" << "\n";

			const char* ptr = "pouet";

			u32 choice = hash::Fnv1a32::Hash(ptr);

			switch (choice)
			{
			case STRHASH32("pouet"):
				std::wcout << "pouet a gagné\n";
				break;
			case STRHASH32("castou"):
				std::wcout << "castou a gagné\n";
				break;
			default:
				std::wcout << "personne n'a gagné\n";
				break;
			}

			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
		std::cout << "Intern strings:\n";
		std::cout << "cstr: " << cstr_id << " " << cstr_result << "\n";
		std::wcout << "wstr: " << wstr_id << " " << wstr_result << "\n";
		std::cout << "std_string: " << std_string_id << " " << std_string_result << "\n";
		std::wcout << "wide_string: " << wide_string_id << " " << wide_string_result << "\n";
	}

	const charA* cstr{ "1234567890" };
	const charW* wstr{ L"1234567890" };
	core::String std_string{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	core::WString wide_string{ L"ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

	core::StringID cstr_id{ core::stringid_invalid };
	core::StringID wstr_id{ core::stringid_invalid };
	core::StringID std_string_id{ core::stringid_invalid };
	core::StringID wide_string_id{ core::stringid_invalid };

	core::String cstr_result{ };
	core::WString wstr_result{ };
	core::String std_string_result{ };
	core::WString wide_string_result{ };

};
