//
// Created by murasame on 23-4-30.
//

#ifndef TJS2JSON_TJS_LEXICAL_ANALYZER_H
#define TJS2JSON_TJS_LEXICAL_ANALYZER_H

#include <utility>
#include <map>

namespace tjs_analysis {

template <typename State, typename Input>
class AbstractDfa {
  public:
    using TransitionKey = std::pair<State, Input>;
    using TransitionTable = std::map<TransitionKey, State>;

    AbstractDfa(State start_state, State reject_state):
                start_state_(start_state), reject_state_(reject_state) {}

    [[nodiscard]] virtual bool accept() const = 0;
    [[nodiscard]] virtual bool reject() const = 0;

    void transition(Input input) const;
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

class TjsLexicalDfa: public AbstractDfa<int, char> {

};

class TjsIdentifierDfa: public AbstractDfa<int, char> {

};

class TjsLexicalAnalyzer {
};

} // tjs_analysis

#endif //TJS2JSON_TJS_LEXICAL_ANALYZER_H
