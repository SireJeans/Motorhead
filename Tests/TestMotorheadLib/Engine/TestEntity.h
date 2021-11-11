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
				CreateRandom();
				RemoveRandom();
			}
			PrintResult();
		} while (getchar() != 'q');
	}
	
	void Shutdown() override { 
	}
private:
	void CreateRandom() {
		u32 count = rand() % 20;
		if (_entities.empty()) {
			count = 1000;
		}

		while (count > 0) {
			++_added;
			ecs::Entity entity{ ecs::CreateGameEntity() };
			assert(entity.IsValid());
			_entities.push_back(entity);
			--count;
		}
	}

	void RemoveRandom() {
		u32 count = rand() % 20;
		if (_entities.size() < 1000) {
			return;
		}

		while (count > 0) {
			const u32 index{ (u32)rand() % (u32)_entities.size() };
			const ecs::Entity entity{ _entities[index] };
			assert(entity.IsValid());
			
			ecs::RemoveGameEntity(entity);
			_entities.erase(_entities.begin() + index);
			assert(!ecs::IsAlive(entity));
			++_removed;
			--count;
		}
	}

	void PrintResult() {
		std::cout << "Entities created : " << _added << "\n";
		std::cout << "Entities deleted : " << _removed << "\n";
	}

	core::vector<ecs::Entity> _entities;
	u32 _added{ 0 };
	u32 _removed{ 0 };
	u32 _num_entities{ 0 };
};
