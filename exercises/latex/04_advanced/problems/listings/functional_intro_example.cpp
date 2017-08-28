std::vector<double> numbers = { 1, 2, 3, 4, 5 };

for (std::vector<double>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
    *it = square(*it); // squaring element
}

// numbers now [ 1, 4, 9, 16, 25 ]
