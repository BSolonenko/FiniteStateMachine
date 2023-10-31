#include "state_logger.h"

namespace fsm
{
	namespace state_handler
	{
		StateLogger::StateLogger(std::ostream& stream)
			: m_logStream(stream)
		{
		}

		void StateLogger::OnJoinedToState(const std::string& stateName)
		{
			m_stateName = stateName;
		}

		void StateLogger::OnEnter()
		{
			if (!m_stateName.empty() && m_logStream)
			{
				m_logStream << "On enter " << m_stateName << " state.\n";
			}
		}

		void StateLogger::OnExit()
		{
			if (!m_stateName.empty() && m_logStream)
			{
				m_logStream << "On exit " << m_stateName << " state.\n";
			}
		}
	}
}
