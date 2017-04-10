std::vector<double> numbers = { 1, 2, 3, 4, 5 };

filter(numbers.begin(), numbers.end(), numbers.begin(), isOdd);

// numbers now [ 1, 3, 5, 4, 5 ]
