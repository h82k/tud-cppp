template<typename InIt, typename RetT, typename RHS>
RetT reduce(InIt first, InIt last, RetT initialVal, RetT(*func)(RetT i, RHS j));
