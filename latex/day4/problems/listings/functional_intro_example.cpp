std::vector<int> numbers = { 1, 2, 3, 4, 5 };

for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
    *it = square(*it); // squaring element pointed to by it
}

// numbers now [ 1, 4, 9, 16, 25 ]
