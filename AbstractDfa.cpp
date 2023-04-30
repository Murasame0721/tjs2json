//
// Created by murasame on 23-4-30.
//

#include "AbstractDfa.h"

// AbstractDfa
template<typename State, typename Input>
State AbstractDfa<State, Input>::Transition(State state, Input input) const {
    TransitionKey key = std::make_pair(current_state_, input);
    auto it = transition_table_.find(key);

    if (it != transition_table_.end()) {
        return it->second;
    } else {
        return reject_state_;
    }
}

template<typename State, typename Input>
void AbstractDfa<State, Input>::transition(Input input) const {
    current_state_ = Transition(current_state_, input);
}

template<typename State, typename Input>
State AbstractDfa<State, Input>::get_state() {
    return current_state_;
}

template<typename State, typename Input>
State AbstractDfa<State, Input>::get_start_state() const {
    return start_state_;
}

template<typename State, typename Input>
State AbstractDfa<State, Input>::get_reject_state() const {
    return reject_state_;
}


