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
			_result = hash::GetCrc(_result, (u8*)data, 10);
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
		std::cout << "CRC=" << _result << "\n";
	}

	u32 _result{ 0 };

};
