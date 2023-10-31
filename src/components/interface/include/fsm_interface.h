#pragma once
#include <memory>
#include <string>

namespace fsm
{
	class StateInterface;

	class FSMInterface
	{
	public:
		virtual ~FSMInterface() = default;

		virtual void Start() = 0;
		virtual void Start(const std::string& entryPoint) = 0;
		virtual bool Started() const = 0;
		virtual void Update(const size_t dt) = 0;
		virtual void Finish() = 0;

		virtual bool HasState(const std::string& name) const = 0;
		virtual std::weak_ptr<StateInterface> GetState(const std::string& name) = 0;
		virtual std::weak_ptr<StateInterface> GetCurrentState() = 0;

		virtual std::string GetFullCurrentStatePathName() = 0;

		template<class State, class... Args>
		std::weak_ptr<State> AddState(Args&&... args);

	protected:
		virtual bool AddStateImpl(std::shared_ptr<StateInterface> state) = 0;
	};

	template<class State, class ...Args>
	inline std::weak_ptr<State> FSMInterface::AddState(Args&& ...args)
	{
		auto state = std::make_shared<State>(std::forward<Args>(args)...);
		if (AddStateImpl(state))
		{
			return state;
		}
		return {};
	}
}
