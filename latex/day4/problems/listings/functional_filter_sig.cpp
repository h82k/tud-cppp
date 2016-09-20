template<typename InIt, typename OutIt>
OutIt filter(InIt first, InIt last, OutIt out_first, bool(*pred)(int i));
