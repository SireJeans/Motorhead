#pragma once

#include "Motorhead/Common.h"
#include "../Test.h"

using namespace motor;

class EngineTest : public Test {
public:
	bool Initialize() override {
		srand((u32)time(nullptr));
		return true;
	}

	void Run() override {
		do {
			for (u32 i{ 0 }; i < 10000; i++) {
				u32 size = rand() % 10000;
				ecs::ComponentRegistry::ResizeVectors(size);
				_total_size += size;
			}
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
		std::cout << "Total size : " << _total_size << "\n";
	}

	u32		_total_size{ 0 };
};

