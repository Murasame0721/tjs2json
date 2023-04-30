//
// Created by murasame on 23-4-30.
//

#ifndef TJS2JSON_ABSTRACT_DFA_H
#define TJS2JSON_ABSTRACT_DFA_H

#include <map>
#include <utility>

template <typename State, typename Input>
class AbstractDfa {
  public:
    using TransitionKey = std::pair<State, Input>;
    using TransitionTable = std::map<TransitionKey, State>;

    AbstractDfa(State start_state, State reject_state):
                start_state_(start_state), reject_state_(reject_state) {}

    [[nodiscard]] virtual bool Accept() const = 0;
    [[nodiscard]] virtual bool Reject() const = 0;

    void transition(Input input) const;

    virtual State Transition(State state, Input input) const;
    // in some case, you can override this function to implement a more efficient algorithm.

    [[nodiscard]] State get_start_state() const;
    [[nodiscard]] State get_reject_state() const;
    [[nodiscard]] State get_state();

  protected:
    TransitionTable transition_table_;
    State current_state_;
    State start_state_;
    State reject_state_;
};
#endif //TJS2JSON_ABSTRACT_DFA_H
