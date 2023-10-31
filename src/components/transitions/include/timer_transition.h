#pragma once
#include "transition_base.h"

namespace fsm
{
	namespace transition
	{
		class Timer : public base::Transition
		{
		public:
			Timer(const size_t time, const std::string& targetState, std::weak_ptr<FSMControllerInterface> fsmController);

		private:
			void OnActivate() override;
			void Update(const size_t dt) override;

			const size_t m_time;
			size_t m_timeCounter = 0;
			bool m_counting = true;
		};
	}
}

