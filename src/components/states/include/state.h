#pragma once
#include <string>
#include <map>
#include <vector>
#include "state_interface.h"

namespace fsm
{
	class SimpleFSM;
	class State : public StateInterface
	{
	public:
		explicit State(const std::string& name);

		void OnEnter() override;
		void Update(const size_t dt) override;
		void OnExit() override;

		void AddTransition(std::shared_ptr<TransitionInterface> transition) override;
		void AddStateHandler(std::shared_ptr<StateHandlerInterface> stateHandler) override;

		const std::string& Name() const override;
		std::string GetFullPathName() override;
		bool HasTransition(const std::string& name) const override;

		std::weak_ptr<FSMInterface> GetSubFSM() override;
		std::weak_ptr<FSMControllerInterface> GetSubFSMController() override;

	private:
		std::string m_name;
		std::vector<std::shared_ptr<StateHandlerInterface>> m_stateHandlers;
		std::map<std::string, std::shared_ptr<TransitionInterface>> m_transitions;
		std::shared_ptr<SimpleFSM> m_subFSM;
	};
}
