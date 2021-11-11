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
		
		random::mtwister mt_test(time(nullptr));

		do {
			_result = random::PRSetTraversal(10);
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
		std::cout << "Results : ";
		for (auto var : _result) {
			std::cout << var << " ";
		}
		std::cout << "\n";
	}

	core::vector<u32> _result;
};
