#pragma once

#include "Motorhead/Core/CoreCommon.h"
#include "Component.h"

namespace motor::component {

	DEFINE_ID_TYPE(transform_id);

	namespace {
		struct TransformInfo {
			f32 position[3]{ };
			f32 rotation[4]{ };
			f32 scale[3]{ 1.f, 1.f, 1.f };
		};
	}

	class Transform : ecs::ComponentBase<TransformInfo, transform_id> {
	public:

	private:
	};

}
