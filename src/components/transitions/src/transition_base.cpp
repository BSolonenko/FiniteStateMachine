#include "transition_base.h"
#include "fsm_controller_interface.h"

namespace fsm
{
	namespace transition
	{
		namespace base
		{
			Transition::Transition(const std::string& targetState, std::weak_ptr<FSMControllerInterface> fsmController)
				: m_targetState(targetState)
				, m_fsmController(fsmController)
			{
			}

			const std::string& Transition::TargetState() const
			{
				return m_targetState;
			}

			bool Transition::Activate() const
			{
				return m_acive;
			}

			void Transition::OnActivate()
			{
				m_acive = true;
			}

			void Transition::OnDeactivate()
			{
				m_acive = false;
			}

			void Transition::OnTransition() const
			{
				if (Activate())
				{
					if (auto fsmControllerShared = m_fsmController.lock())
					{
						fsmControllerShared->SwitchToState(TargetState());
					}
				}
			}
		}
	}
}
