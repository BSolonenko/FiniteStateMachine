#include "predicat_transition.h"

namespace fsm
{
	namespace transition
	{
		Predicat::Predicat(const Func& func, const std::string& targetState, std::weak_ptr<FSMControllerInterface> fsmController)
			: Transition(targetState, fsmController)
			, m_func(func)
		{
		}

		void Predicat::Update(const size_t dt)
		{
			if (m_func && m_func(dt))
			{
				OnTransition();
			}
		}
	}
}
