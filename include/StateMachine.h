#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include <stack>
#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

class IState;

class StateMachine
{
    public:
        StateMachine();

        void run(std::unique_ptr<IState> state);

        void nextState();
        void lastState();

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

        bool isRunning(){return mRunning;}
        void quit(){mRunning = false;}

        template <typename T>
        static std::unique_ptr<T> build(StateMachine& machine, bool replace = true);

    private:
        // The stack of states
        std::stack<std::unique_ptr<IState>> mStates;

        bool mResume;
        bool mRunning;
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, bool replace)
{
	return std::unique_ptr<T>(new T(machine, replace));
}

#endif // STATEMACHINE_H
