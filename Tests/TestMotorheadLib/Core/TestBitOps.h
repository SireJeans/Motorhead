#pragma once


#include <Motorhead/Common.h>
#include "Motorhead/Core/BitOps.h"
#include "../Test.h"

using namespace motor;

class EngineTest : public Test {
public:
	bool Initialize() override {
		return true;
	}

	void Run() override {


		do {
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {

	}


};
