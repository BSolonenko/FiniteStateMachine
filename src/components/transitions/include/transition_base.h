#pragma once

#include <memory>
#include "transition_interface.h"

namespace fsm
{
	class FSMControllerInterface;
	namespace transition
	{
		namespace base
		{
			class Transition : public TransitionInterface
			{
			public:
				Transition(const std::string& targetState, std::weak_ptr<FSMControllerInterface> fsmController);
				
				const std::string& TargetState() const override;
				bool Activate() const override;
				void OnActivate() override;
				void Update(const size_t dt) override {};
				void OnDeactivate() override;
			
			protected:
				void OnTransition() const;

			private:
				const std::string m_targetState;
				bool m_acive = false;
				std::weak_ptr<FSMControllerInterface> m_fsmController;
			};
		}
	}
}


