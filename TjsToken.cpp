//
// Created by murasame on 23-4-30.
//

#include <cassert>
#include "TjsToken.h"

namespace tjs_analysis {

// getType() is implemented in the base class.
template<typename T>
TjsTokenType TjsToken<T>::getType() {
  return type_;
}

// getAttribute() is a pure virtual function, so it must be implemented in the derived class.
// here are the implementations of all derived classes.
const bool *TjsNoAttributeToken::getAttribute() {
  assert(false);  // never call this function
}
int64_t TjsIntegerToken::getAttribute() {
  return attribute_;
}
double TjsRealToken::getAttribute() {
  return attribute_;
}
std::string TjsStringToken::getAttribute() {
  return attribute_;
}
bool TjsBooleanToken::getAttribute() {
  return attribute_;
}
std::string TjsIdentifierToken::getAttribute() {
  return attribute_;
}

} // tjs_analysis