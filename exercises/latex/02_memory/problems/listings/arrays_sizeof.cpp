int arr[10];
std::cout << sizeof(arr) << std::endl; // 40 on a typical 32 or 64-bit machine
int len = sizeof(arr) / sizeof(arr[0]);
std::cout << len << std::endl; // always 10
