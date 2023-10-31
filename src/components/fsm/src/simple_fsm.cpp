#include "simple_fsm.h"
#include "state_interface.h"

namespace fsm
{

	SimpleFSM::~SimpleFSM()
	{
		Finish();
	}

	void SimpleFSM::Start()
	{
		Start(m_entryPoint);
	}

	void SimpleFSM::Start(const std::string& entryPoint)
	{
		Finish();

		if (HasState(entryPoint))
		{
			m_currentState = entryPoint;
			m_fsm[m_currentState]->OnEnter();
		}
	}

	void SimpleFSM::Update(const size_t dt)
	{
		if (m_currentState.empty())
		{
			return;
		}

		m_fsm[m_currentState]->Update(dt);
	}

	void SimpleFSM::Finish()
	{
		if (!m_currentState.empty())
		{
			m_fsm[m_currentState]->OnExit();
			m_currentState.clear();
		}
	}

	bool SimpleFSM::HasState(const std::string& name) const
	{
		return m_fsm.count(name) != 0;
	}

	bool SimpleFSM::Started() const
	{
		return !m_currentState.empty();
	}

	std::weak_ptr<StateInterface> SimpleFSM::GetState(const std::string& name)
	{
		if (HasState(name))
		{
			return m_fsm[name];
		}

		return {};
	}

	std::weak_ptr<StateInterface> SimpleFSM::GetCurrentState()
	{
		return GetState(m_currentState);
	}

	std::string SimpleFSM::GetFullCurrentStatePathName()
	{
		if (HasState(m_currentState))
		{
			return m_fsm[m_currentState]->GetFullPathName();
		}
		return "";
	}

	bool SimpleFSM::AddStateImpl(std::shared_ptr<StateInterface> state)
	{
		if (state && !HasState(state->Name()))
		{
			if (m_fsm.empty())
			{
				m_entryPoint = state->Name();
			}

			m_fsm[state->Name()] = state;
			return true;
		}

		return false;
	}

	void SimpleFSM::SwitchToState(const std::string& targetState)
	{
		if (!m_currentState.empty() && HasState(targetState) && m_fsm[m_currentState]->HasTransition(targetState))
		{
			m_fsm[m_currentState]->OnExit();
			m_fsm[targetState]->OnEnter();

			m_currentState = targetState;
		}
	}
}
