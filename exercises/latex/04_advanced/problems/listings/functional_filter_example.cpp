// #include <iterator>

std::vector<double> numbers = { 1, 2, 3, 4, 5 };
std::vector<double> filteredNumbers;

filter_funcpointer(numbers.begin(), numbers.end(), 
                   std::back_inserter(filteredNumbers), is_odd);

// filteredNumbers now [ 1, 3, 5 ]
