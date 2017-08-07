std::vector<double> numbers = { 1, 2, 3, 4, 5 };

map(numbers.begin(), numbers.end(), numbers.begin(), square);
// numbers now [ 1, 4, 9, 16, 25 ]
