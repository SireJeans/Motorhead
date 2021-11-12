#pragma once

#include "Motorhead/Common.h"
#include "../Test.h"

using namespace motor;

void Func0(void)
{
}

int Func1(int a)
{
	return a + 10;
}

float Func2(float a, float b)
{
	return a + b;
}


struct ClassX
{
	void Func0(void)
	{
	}

	void Func0(void) const
	{
	}

	int Func1(int a)
	{
		return a + 20;
	}

	int Func1(int a) const
	{
		return a + 20;
	}

	float Func2(float a, float b)
	{
		return a + b;
	}

	float Func2(float a, float b) const
	{
		return a + b;
	}
};


class EngineTest : public Test {
public:
	bool Initialize() override {
		return true;
	}

	void Run() override {

		do {
			// delegate with zero arguments
			{
				typedef core::Delegate<void(void)> TestDelegate;
				TestDelegate d;
				d.Bind<&Func0>();
			}

			// delegate with one argument
			{
				typedef core::Delegate<int(int)> TestDelegate;
				TestDelegate d;
				d.Bind<&Func1>();
				std::cout << d.Invoke(10) << "\n";

				ClassX t;
				d.Bind<ClassX, &ClassX::Func1>(&t);
				std::cout << d.Invoke(10) << "\n";


				const ClassX ct;
				d.Bind<ClassX, &ClassX::Func1>(&ct);
				std::cout << d.Invoke(10) << "\n";

			}

			// delegate with two arguments
			{
				typedef core::Delegate<float(float, float)> TestDelegate;
				TestDelegate d;
				d.Bind<&Func2>();
				std::cout << d.Invoke(10.0f, 20.0f) << "\n";

				ClassX t;
				d.Bind<ClassX, &ClassX::Func2>(&t);
				std::cout << d.Invoke(10.0f, 20.0f) << "\n";

				const ClassX ct;
				d.Bind<ClassX, &ClassX::Func2>(&ct);
				std::cout << d.Invoke(10.0f, 20.0f) << "\n";
			}
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
	}

};
