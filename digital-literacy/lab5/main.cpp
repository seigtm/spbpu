#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> vec;
    for(auto i{ 0 }; i < 222'222; ++i)
        vec.push_back(std::to_string(i));
    const auto vecSize{ vec.size() };
    for(auto i{ vec.size() / 2 }; i < vecSize; ++i)
        vec.erase(vec.begin() + i);

    return 0;
}
