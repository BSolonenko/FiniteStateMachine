#pragma once
#include <functional>
#include <memory>
#include "transition_base.h"

namespace fsm
{
	namespace transition
	{
		class Predicat : public base::Transition
		{
		public:
			using Func = std::function<bool(const size_t)>;

			Predicat(const Func& func, const std::string& targetState, std::weak_ptr<FSMControllerInterface> fsmController);

			void Update(const size_t dt) override;

		private:
			Func m_func;
		};
	}
}


