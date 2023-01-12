#include <vector>
#include <algorithm>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bitset>
#include "cppitertools/combinations.hpp"
#include <boost/algorithm/string/join.hpp>
#include <filesystem>

int main() {

//    std::string path = "/home/ms12416/";
//    for (const auto & entry : std::filesystem::directory_iterator(path))
//        std::cout << entry.path() << std::endl;
//    unsigned char a = 253;
//    std::cout << (short)a << std::endl;
//    std::unordered_map<std::string, std::vector<int>> a;
//    std::vector<int> b{1, 2, 3, 4};
//    std::vector<int> c{100, 200, 300, 400};
//    // a["s"] = b;
//    a["s"].insert(a["s"].end(), c.begin(), c.end());
//    std::cout << a["s"][3] << std::endl;
    std::string a = "323";
    int64_t b = std::stoll(a, nullptr, 0);
    printf("%ld", b+1);

//    std::vector<std::string> terms = {"to", "be", "or", "not"};
//    std::vector<std::string> comb;
//    for (auto&& i : iter::combinations(terms, 3)) {
//        std::string grams = boost::join(std::vector<std::string>(i.begin(), i.end()), " ");
//        comb.emplace_back(grams);
//    }
//    for (auto i : comb)
//    {
//        std::cout << i << std::endl;
//    }

//    std::vector<int> a = {3, 4, 76, 2, -1, -10};
//    int b = *std::max_element(begin(a), end(a));
//    std::cout << b << std::endl;

//    std::vector<int> v = {1,2,3,4,5};
//    std::vector<std::string> v2 = {"1", "2", "3", "4"};
//    for (auto&& i : iter::combinations(v2,0)) {
//        std::vector<std::string> a(i.begin(), i.end());
//        std::string c = boost::join(a, "-");
//        std::cout << c << std::endl;
//    }
//    std::bitset<4> a("0111");
//    std::cout << a[2] << std::endl;
//    std::vector<std::string> a = {"to", "be", "or", "not"};
//    std::string c = boost::join(a, " ");
//    std::cout << c << std::endl;

}
