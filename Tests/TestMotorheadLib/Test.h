#pragma once

// Reccurent headers
#include <ctime>
#include <iostream>

class Test {
public:
	virtual bool Initialize() = 0;
	virtual void Run() = 0;
	virtual void Shutdown() = 0;
};
