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

		const charT* data = TXT("1234567890");

		do {
			_result = hash::Crc32Hash((u8*)data, 10, _result);
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
		std::cout << "CRC=" << _result << "\n";
		std::cout << core::GenerateHash("Pouët") << "\n";
		std::cout << core::GenerateHash(L"Pouët") << "\n";
		std::cout << core::GenerateHash(TXT("Pouët")) << "\n";
		const charT* caca = TXT("CACAAAAAA!");
		const charA* cacaA = "CACAAAAAA!";
		const charW* cacaW = L"CACAAAAAA!";
		std::cout << core::GenerateHash(caca) << "\n";
		std::cout << core::GenerateHash(cacaA) << "\n";
		std::cout << core::GenerateHash(cacaW) << "\n";
	}

	u32 _result{ 0 };

};
