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

    State transition(State current_state, Input input) const;

    virtual State start_state() const = 0;
    virtual State accept_state() const = 0;
    virtual State reject_state() const = 0;

  protected:
    TransitionTable transition_table_;
};

class TjsLexicalAnalyzer {

};

} // tjs_analysis

#endif //TJS2JSON_TJS_LEXICAL_ANALYZER_H
