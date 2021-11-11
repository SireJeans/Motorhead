#pragma once

#include "Motorhead/Core/CoreCommon.h"

namespace motor::ecs {

	DEFINE_ID_TYPE(entity_id);

	class Entity {
	public:
		constexpr explicit Entity(entity_id id) : _id{ id } { }
		constexpr Entity() : _id{ id::invalid_id } { }
		constexpr entity_id GetId() const { return _id; }
		constexpr bool IsValid() const { return id::IsValid(_id); }
		template <typename T>
		T GetComponent() { return T; }
	private:
		entity_id _id;
	};

	Entity CreateGameEntity();
	bool IsAlive(Entity e);
	void RemoveGameEntity(Entity e);
}
