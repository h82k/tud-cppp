#include <algorithm> // copy
#include <iterator> // back_inserter
#include <vector>
// ...
Array<int> array(10);
std::vector<int> vector;
std::copy(array, array + 4, std::back_inserter(vector));
