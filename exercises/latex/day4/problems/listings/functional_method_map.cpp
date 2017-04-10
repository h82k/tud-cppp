template <typename InIt, typename OutIt, typename ObjType>
OutIt map(InIt first, InIt last, OutIt out_first, ObjType *object, double (ObjType::* method)(double));
