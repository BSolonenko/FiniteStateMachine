#pragma once
#include <string>
#include <memory>

namespace fsm
{
	class TransitionInterface;
	class StateHandlerInterface;
	class FSMInterface;
	class FSMControllerInterface;

	class StateInterface
	{
	public:
		virtual ~StateInterface() = default;

		virtual void OnEnter() = 0;
		virtual void Update(const size_t dt) = 0;
		virtual void OnExit() = 0;

		virtual void AddTransition(std::shared_ptr<TransitionInterface> transition) = 0;
		virtual void AddStateHandler(std::shared_ptr<StateHandlerInterface> stateHandler) = 0;

		virtual const std::string& Name() const = 0;
		virtual bool HasTransition(const std::string& name) const = 0;
		virtual std::weak_ptr<FSMInterface> GetSubFSM() = 0;
		virtual std::weak_ptr<FSMControllerInterface> GetSubFSMController() = 0;

		virtual std::string GetFullPathName() = 0;
	};
}
