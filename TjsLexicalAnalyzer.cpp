//
// Created by murasame on 23-4-30.
//

#include "TjsLexicalAnalyzer.h"

namespace tjs_analysis {

template <typename State, typename Input>
State AbstractDfa<State,Input>::transition(State current_state,Input input) const {
    TransitionKey key = std::make_pair(current_state, input);
    auto it = transition_table_.find(key);

    if (it != transition_table_.end()) {
        return it->second;
    } else {
        return reject_state();
    }
}

} // tjs_analysis