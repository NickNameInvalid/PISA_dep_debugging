#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <first_layer_index.hpp>
#include <bitset>
#include "cppitertools/combinations.hpp"
#include <boost/algorithm/string/join.hpp>
#include <queue>
#include <numeric>
#include <filesystem>

namespace candidates {
    using lexicon_offset = std::pair<int64_t, int64_t>;
    using lexicon = std::unordered_map<std::string, lexicon_offset>;
    using index_path = std::pair<std::string, std::string>;
    using comb_grams = std::tuple<std::vector<std::string>, std::vector<std::string>, std::vector<std::string>, std::vector<std::string>>;

    struct struct_path
    {
        index_path sinind = {};
        index_path dupind = {};
        index_path triind = {};
        index_path quadind = {};
    };

    struct struct_lexicon
    {
        lexicon sinsublex = {};
        lexicon dupsublex = {};
        lexicon trisublex = {};
        lexicon quadsublex = {};
    };

    struct struct_input
    {
        std::ifstream sinsub;
        std::ifstream dupsub;
        std::ifstream trisub;
        std::ifstream quadsub;
    };

    class realtime_heap_allocate {
        public:
            lexicon load_lexicon(const std::string& gram_path, std::string lexicon_path);
            lexicon_offset get_offset(const std::string& substructure, lexicon & substructure_lex);
            std::unordered_map<int, std::vector<float>> compute_hit_ratio(std::string query, std::vector<int> & budget, std::vector<int> & topk, std::bitset<4> & types, std::string output_path, std::string metrics);
            void get_accuracy(std::string set_path, std::vector<int> & budget, std::vector<int> & topk, std::bitset<4> types, std::string metric);
            comb_grams get_comb(std::vector<std::string> & terms, std::bitset<4> & comb_type);
            float metric_score(std::string metric, std::unordered_map<std::string, std::string> topk_dict, std::vector<std::string> topk_lst, std::vector<std::string> topk_pred);
            realtime_heap_allocate(index_path single, index_path duplet, index_path triplet, index_path quadruplet);

        private:
            std::vector<int> budgets = {};
            std::vector<std::string> query_name = {};
            struct_path structPath = {};
            struct_lexicon structLexicon = {};
            struct_input structInput = {};
    };

}

