//#include <vector>
//#include <algorithm>
//#include <iostream>
//#include <boost/algorithm/string.hpp>
//#include <bitset>
//#include "cppitertools/combinations.hpp"
//#include <boost/algorithm/string/join.hpp>
//#include <filesystem>
#include "pisa/query/query_stemmer.hpp"
#include <iostream>
#include "realtime_heap_allocate.h"
#include "pisa/include/pisa/query/queries.hpp"

int main() {


//    std::string query_root_path = "/home/jg6226/data/Hit_Ratio_Project";
//
//    std::string single_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Lexicon/CW09B.fwd.terms";
//    std::string single_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/single_with_termscore/single_lexicon.txt";
//    std::string single_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/single_with_termscore/single_prefix";
//
//    std::string duplet_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/Prefix_Grams/duplet_cleaned.txt";
//    std::string duplet_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/duplet_with_termscore/duplet_lexicon.txt";
//    std::string duplet_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/duplet_with_termscore/duplet_prefix";
//
//    std::string triplet_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/Prefix_Grams/triplet_cleaned.txt";
//    std::string triplet_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/triplet_with_termscore/triplet_lexicon.txt";
//    std::string triplet_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/triplet_with_termscore/triplet_prefix";
//
//    std::string quadruplet_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/Prefix_Grams/quadruplet_cleaned.txt";
//    std::string quadruplet_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/quadruplet_with_termscore/quadruplet_lexicon.txt";
//    std::string quadruplet_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/quadruplet_with_termscore/quadruplet_prefix";
//
//    candidates::index_path single = std::make_tuple(single_gram_path, single_substructure_lexicon_path, single_substructure_path);
//    candidates::index_path duplet = std::make_tuple(duplet_gram_path, duplet_substructure_lexicon_path, duplet_substructure_path);
//    candidates::index_path triplet = std::make_tuple(triplet_gram_path, triplet_substructure_lexicon_path, triplet_substructure_path);
//    candidates::index_path quadruplet = std::make_tuple(quadruplet_gram_path, quadruplet_substructure_lexicon_path, quadruplet_substructure_path);
//
//    // initialize an object:
//    candidates::realtime_heap_allocate realtime_heap_allocate_obj(single, duplet, triplet, quadruplet);
//    // load lexicon
//    realtime_heap_allocate_obj.initialize();

    // experiment configuration
//    std::vector<int> lst_budget = {500, 1000, 2000, 3000, 4000, 5000, 6000, 8000, 12000, 15000,
//                                   18000, 25000, 35000, 50000, 65000, 80000, 100000, 120000, 140000, 160000,
//                                   180000, 200000, 225000, 250000, 275000, 300000, 350000, 400000, 500000};
//    std::vector<int> lst_top_k = {10, 100, 1000};

//    std::vector<int> lst_budget = {5000};
//    std::vector<int> lst_top_k = {1000};
    //std::vector<int> lst_type = {1, 2, 3, 4};
//    std::bitset<4> lst_type("1111");
//    std::string query_set_path = "/home/jg6226/data/Hit_Ratio_Project/Split_Test_Output_Quantized";
//    std::unordered_map<int, std::vector<float>> one_query_result;
//    std::vector<std::string> a = realtime_heap_allocate_obj.split("1003_com paparazziphotoart www", " ");
//
//    for(auto & jj : a)
//    {
//        std::cout << jj << std::endl;
//    }
//
//    clock_t start, end;
//    start = clock();
//    one_query_result = realtime_heap_allocate_obj.compute_hit_ratio("/home/jg6226/data/Hit_Ratio_Project/Split_Test_Output_Quantized/1003_com paparazziphotoart www", lst_budget, lst_top_k, lst_type, "Recall");
//    end = clock();
//    double one_query_running_time = double(end - start) / double(CLOCKS_PER_SEC);
//    std::cout << "Time to compute one query: " << one_query_running_time << "s\n";
//
//
//
//    for (auto top_k: lst_top_k) {
//        std::cout << "When k = " << top_k << ":\n";
//        std::cout << '[';
//        for (auto acc: one_query_result[top_k]) {
//            std::cout << acc << ", ";
//        }
//        std::cout << "]\n";
//    }

//    for (auto item: one_query_result) {
//        std::cout << "When k = " << item.first << ":\n";
//        std::cout << '[';
//        for (auto sub_item: item.second) {
//            std::cout << sub_item << ", ";
//        }
//        std::cout << "]\n";
//    }

    // realtime_heap_allocate_obj.get_accuracy(query_set_path, lst_budget, lst_top_k, lst_type);

    return 0;

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
//
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
//
//    std::vector<int> a = {3, 4, 76, 2, -1, -10};
//    int b = *std::max_element(begin(a), end(a));
//    std::cout << b << std::endl;
//
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
