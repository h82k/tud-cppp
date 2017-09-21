#include <algorithm> // std::copy
#include <iterator>  // std::back_inserter
#include <vector>
// ...
Array<int> array(10);
std::vector<int> vector;
std::copy(array.begin(), array.end() - 1, std::back_inserter(vector));
