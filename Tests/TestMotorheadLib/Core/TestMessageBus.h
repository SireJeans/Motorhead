#pragma once

#include "Motorhead/Core/MessageBus.h"
#include "../Test.h"

using namespace motor;

struct DummyMessage : core::Message
{

};

void Func1(DummyMessage) {
	std::cout << "Func1 call" << "\n";
}

struct Structure {
	void FuncStruct(DummyMessage) {
		std::cout << "FuncStruct call" << "\n";
	}
};

class EngineTest : public Test {
public:
	bool Initialize() override {
		return true;
	}

	void Run() override {
		DummyMessage msg;

		do {
			std::cout << core::Message::Id<DummyMessage>() << "\n";
			auto container = core::MessageContainer<DummyMessage>{};
			auto bus = core::MessageBus{};
			core::Delegate<void(DummyMessage)> d;
			d.Bind<&Func1>();
			Structure pouet;
			core::Delegate<void(DummyMessage)> sd;
			sd.Bind<Structure, &Structure::FuncStruct>(&pouet);
			auto handle = bus.Subscribe<DummyMessage>(d);
			auto handle2 = bus.Subscribe<DummyMessage>(sd);
			bus.Publish(msg);
			bus.Unsubscribe(handle);
			bus.Unsubscribe(handle2);
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override {

	}

private:

	void PrintResult() {
	}

};
