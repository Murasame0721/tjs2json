//
// Created by murasame on 23-4-30.
//

#include "TjsLexicalAnalyzer.h"

namespace tjs_analysis {

// AbstractDfa
template <typename State, typename Input>
void AbstractDfa<State,Input>::transition(Input input) const {
    TransitionKey key = std::make_pair(current_state_, input);
    auto it = transition_table_.find(key);

    if (it != transition_table_.end()) {
        current_state_ = it->second;
    } else {
        current_state_ = reject_state_;
    }
}
template <typename State, typename Input>
State AbstractDfa<State,Input>::get_state() {
    return current_state_;
}
template <typename State, typename Input>
State AbstractDfa<State,Input>::get_start_state() const {
    return start_state_;
}
template <typename State, typename Input>
State AbstractDfa<State,Input>::get_reject_state() const {
    return reject_state_;
}



} // tjs_analysis