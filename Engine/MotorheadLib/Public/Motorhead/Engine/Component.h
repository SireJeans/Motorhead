#pragma once

#include "Motorhead/Core/CoreCommon.h"

namespace motor::ecs {

	class IComponent {
	public:
		virtual void EmplaceBack() = 0;
		virtual void Resize(u32 size) = 0;
	private:
	};

	class ComponentRegistry {
	public:
		static void Register(IComponent* component) {
			assert(component != nullptr);
			_register.push_back(component);
		}

		static void Unregister(IComponent* component) {
			assert(component != nullptr);
			u32 i = 0;
			for (auto var : _register) {
				if (var == component) {
					_register.erase(_register.begin() + i);
					return;
				}
				++i;
			}
		}

		static void GrowVectors() {
			for (auto var : _register) {
				var->EmplaceBack();
			}
		}

		static void ResizeVectors(u32 size) {
			for (auto var : _register) {
				var->Resize(size);
			}
		}

	private:
		static core::vector<IComponent*> _register;
	};

	core::vector<IComponent*> ComponentRegistry::_register;

	template<typename INFO, typename ID>
	class ComponentBase : public IComponent {
	public:
		ComponentBase() {
			ComponentRegistry::Register(this);
		}

		INFO GetInfo(ID id) { 
			assert(id::IsValid(id));
			const id::genid_type index{ id::Index(id) };
			assert(index != id::internal::index_mask);
			assert(index < _ids.size());
			assert(index < _data.size());
			return _data[index];
		}

		void Remove(ID id) { 
			assert(id::IsValid(id));
			const id::genid_type index{ id::Index(id) };
			assert(index != id::internal::index_mask);
			assert(index < _ids.size());
			assert(index < _data.size());
			_ids[index] = id::NewGeneration(_ids[index]);
		}

		void Create(ID id) {
			assert(id::IsValid(id));
			const id::genid_type index{ id::Index(id) };
			assert(index != id::internal::index_mask);
			assert(!_ids[index].IsValid());
			
		}
		
		virtual void EmplaceBack() override {
			_data.emplace_back();
			_ids.emplace_back();
		}
		
		virtual void Resize(u32 size) override {
			_data.resize(size, _default_info);
			_ids.resize(size, id::invalid_id);
		}

	protected:
		static core::vector<INFO>			_data;
		static core::vector<ID>				_ids;
		static ComponentBase<INFO,ID>		_instance;
		static const INFO					_default_info;
	};

	template<typename INFO, typename ID> core::vector<INFO> ComponentBase<INFO, ID>::_data;
	template<typename INFO, typename ID> core::vector<ID> ComponentBase<INFO, ID>::_ids;
	template<typename INFO, typename ID> ComponentBase<INFO, ID> ComponentBase<INFO, ID>::_instance;
	template<typename INFO, typename ID> const INFO ComponentBase<INFO, ID>::_default_info;


}
