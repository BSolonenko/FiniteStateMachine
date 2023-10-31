#include "State.h"
#include <iostream>

#include "transition_interface.h"
#include "state_handler_interface.h"
#include "simple_fsm.h"

namespace fsm
{
	State::State(const std::string& name)
		: m_name(name)
		, m_subFSM(std::make_shared<SimpleFSM>())
	{
	}

	void State::OnEnter()
	{
		for (auto& transiton : m_transitions)
		{
			if (transiton.second)
			{
				transiton.second->OnActivate();
			}
		}

		for (auto& stateHandler : m_stateHandlers)
		{
			if (stateHandler)
			{
				stateHandler->OnEnter();
			}
		}

		if (m_subFSM)
		{
			m_subFSM->Start();
		}
	}

	void State::Update(const size_t dt)
	{
		for (auto& transiton : m_transitions)
		{
			if (transiton.second)
			{
				transiton.second->Update(dt);
			}
		}

		for (auto& stateHandler : m_stateHandlers)
		{
			if (stateHandler)
			{
				stateHandler->Update(dt);
			}
		}

		if (m_subFSM)
		{
			m_subFSM->Update(dt);
		}
	}

	void State::OnExit()
	{
		if (m_subFSM)
		{
			m_subFSM->Finish();
		}

		for (auto& transiton : m_transitions)
		{
			if (transiton.second)
			{
				transiton.second->OnDeactivate();
			}
		}

		for (auto& stateHandler : m_stateHandlers)
		{
			if (stateHandler)
			{
				stateHandler->OnExit();
			}
		}
	}

	void State::AddTransition(std::shared_ptr<TransitionInterface> transition)
	{
		if (transition && !HasTransition(transition->TargetState()))
		{
			m_transitions[transition->TargetState()] = transition;
		}
	}

	void State::AddStateHandler(std::shared_ptr<StateHandlerInterface> stateHandler)
	{
		if (stateHandler)
		{
			m_stateHandlers.push_back(stateHandler);
			m_stateHandlers.back()->OnJoinedToState(Name());
		}
	}

	const std::string& State::Name() const
	{
		return m_name;
	}

	std::string State::GetFullPathName()
	{
		const auto subFsmFullPath = (m_subFSM ? m_subFSM->GetFullCurrentStatePathName() : "");
		return "/" + m_name + subFsmFullPath;
	}

	bool State::HasTransition(const std::string& name) const
	{
		return m_transitions.count(name) != 0;
	}

	std::weak_ptr<FSMInterface> State::GetSubFSM()
	{
		return m_subFSM;
	}

	std::weak_ptr<FSMControllerInterface> State::GetSubFSMController()
	{
		return m_subFSM;
	}
}
