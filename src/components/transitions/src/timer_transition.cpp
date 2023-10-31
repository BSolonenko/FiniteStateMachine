#include "timer_transition.h"

namespace fsm
{
	namespace transition
	{
		Timer::Timer(const size_t time, const std::string& targetState, std::weak_ptr<FSMControllerInterface> fsmController)
			: Transition(targetState, fsmController)
			, m_time(time)
		{
		}

		void Timer::OnActivate()
		{
			Transition::OnActivate();
			m_timeCounter = 0;
			m_counting = true;
		}

		void Timer::Update(const size_t dt)
		{
			Transition::Update(dt);
			m_timeCounter += dt;
			if (m_timeCounter >= m_time && m_counting)
			{
				m_counting = false;
				OnTransition();
			}
		}
	}
}
