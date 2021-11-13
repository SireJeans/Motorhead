#include "Motorhead/Engine/Entity.h"

#pragma warning(disable:4530)

namespace motor::ecs {

	namespace {

		core::vector<id::genid_type>			generations;
		core::deque<entity_id>				free_ids;

	}

	Entity CreateGameEntity()
	{
		entity_id id;

		if (free_ids.size() > id::min_deleted_elements) {
			id = free_ids.front();
			free_ids.pop_front();
			id = entity_id{ id::NewGeneration(id) };
			++generations[id::Index(id)];
		} else {
			id = entity_id{ (id::genid_type)generations.size() };
			generations.push_back(0);
		}

		const Entity new_entity{ id };

		return new_entity;
	}

	bool IsAlive(Entity e) 
	{
		assert(e.IsValid());
		const entity_id id{ e.GetId() };
		const id::genid_type index{ id::Index(id) };
		assert(index < generations.size());
		return (generations[index] == id::Generation(id));
	}

	void RemoveGameEntity(Entity e)
	{
		const entity_id id{ e.GetId() };
		const id::genid_type index{ id::Index(id) };
		//assert(IsAlive(e));
		assert(index < generations.size());
		if (IsAlive(e)) {
			free_ids.push_back(id);
			generations[index] = id::NewGeneration(generations[index]);
		}
	}

}