#include "../include/realtime_heap_allocate.h"

namespace candidates {

    lexicon realtime_heap_allocate::load_lexicon(const std::string& gram_path, std::string lexicon_path) {
        lexicon lex = {};
        std::fstream in_gram(gram_path, std::ios::in | std::ios::binary);
        std::fstream in_lex(lexicon_path, std::ios::in | std::ios::binary);
        std::string gramline, lexline;
        std::vector<std::string> lex_pair;
        while(getline(in_gram, gramline))
        {
            getline(in_lex, lexline);
            boost::split(lex_pair, lexline, boost::is_any_of(" "), boost::token_compress_on);
            lex[gramline] = lexicon_offset(std::stoll(lex_pair[0], nullptr, 0), std::stoll(lex_pair[1], nullptr, 0));
        }
        in_gram.close();
        in_lex.close();
        return lex;
    }

    lexicon_offset realtime_heap_allocate::get_offset(const std::string& substructure, lexicon & substructure_lex) {
        lexicon_offset offset{0, 0};
        if(substructure_lex.find(substructure) != substructure_lex.end())
        {
            offset = substructure_lex[substructure];
        }
        return offset;
    }

    std::unordered_map<int, std::vector<float>>
    realtime_heap_allocate::compute_hit_ratio(std::string query, std::vector<int> & budget, std::vector<int> & topk,
                                              std::bitset<4> & types, std::string output_path, std::string metrics) {
        int max_budget = *std::max_element(std::begin(budget), std::end(budget));
        std::vector<std::string> query_terms;
        boost::split(query_terms, query, boost::is_any_of("_"), boost::token_compress_on);
        std::string queries = query_terms.back();
        boost::split(query_terms, queries, boost::is_any_of(" "), boost::token_compress_on);
        auto [lst_sin, lst_dup, lst_tri, lst_quad] = this->get_comb(query_terms, types);
        std::priority_queue<postings> hp_posting = {};
        for(auto & single : lst_sin)
        {
            auto [start_pos, end_pos] = get_offset(single, this->structLexicon.sinsublex);
            if(start_pos && end_pos)
            {
                int64_t cur_pos = start_pos + 4;
                this->structInput.sinsub.seekg(cur_pos);
                int did;
                short score;
                this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&score), 1);
                hp_posting.push(postings(std::to_string(did), score, 1, cur_pos + 5, end_pos));
            }
        }
        for(auto & dup : lst_dup)
        {
            auto [start_pos, end_pos] = get_offset(dup, this->structLexicon.sinsublex);
            if(start_pos && end_pos)
            {
                int64_t cur_pos = start_pos + 4;
                this->structInput.sinsub.seekg(cur_pos);
                int did;
                std::pair<short, short> scores;
                this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&scores.first), 1);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&scores.second), 1);
                hp_posting.push(postings(std::to_string(did), scores.first + scores.second, 2, cur_pos + 6, end_pos));
            }
        }
        for(auto & tri : lst_tri)
        {
            auto [start_pos, end_pos] = get_offset(tri, this->structLexicon.sinsublex);
            if(start_pos && end_pos)
            {
                int64_t cur_pos = start_pos + 4;
                this->structInput.sinsub.seekg(cur_pos);
                int did;
                std::tuple<short, short, short> scores;
                this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<0>(scores)), 1);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<1>(scores)), 1);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<2>(scores)), 1);
                hp_posting.push(postings(std::to_string(did), std::get<0>(scores) + std::get<1>(scores) + std::get<2>(scores), 3, cur_pos + 7, end_pos));
            }
        }
        for(auto & quad : lst_quad)
        {
            auto [start_pos, end_pos] = get_offset(quad, this->structLexicon.sinsublex);
            if(start_pos && end_pos)
            {
                int64_t cur_pos = start_pos + 4;
                this->structInput.sinsub.seekg(cur_pos);
                int did;
                std::tuple<short, short, short, short> scores;
                this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<0>(scores)), 1);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<1>(scores)), 1);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<2>(scores)), 1);
                this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<3>(scores)), 1);
                hp_posting.push(postings(std::to_string(did), std::get<0>(scores) + std::get<1>(scores) + std::get<2>(scores) + std::get<3>(scores), 4, cur_pos + 8, end_pos));
            }
        }

        std::vector<std::string> pred_did = {};
        while (!hp_posting.empty() && max_budget > 0)
        {
            postings cur_obj = hp_posting.top();
            hp_posting.pop();
            max_budget--;

            if(cur_obj.ptr < cur_obj.ends)
            {
                int64_t cur_pos = cur_obj.ptr;
                int64_t end_pos = cur_obj.ends;
                if(cur_obj.type == 1)
                {
                    this->structInput.sinsub.seekg(cur_pos);
                    int did;
                    short score;
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&score), 1);
                    hp_posting.push(postings(std::to_string(did), score, 1, cur_pos + 5, end_pos));
                }
                else if(cur_obj.type == 2)
                {
                    this->structInput.sinsub.seekg(cur_pos);
                    int did;
                    std::pair<short, short> scores;
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&scores.first), 1);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&scores.second), 1);
                    hp_posting.push(postings(std::to_string(did), (short)(scores.first + scores.second), 2, cur_pos + 6, end_pos));
                }
                else if(cur_obj.type == 3)
                {
                    this->structInput.sinsub.seekg(cur_pos);
                    int did;
                    std::tuple<short, short, short> scores;
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<0>(scores)), 1);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<1>(scores)), 1);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<2>(scores)), 1);
                    hp_posting.push(postings(std::to_string(did), std::get<0>(scores) + std::get<1>(scores) + std::get<2>(scores), 3, cur_pos + 7, end_pos));
                }
                else if(cur_obj.type == 4)
                {
                    this->structInput.sinsub.seekg(cur_pos);
                    int did;
                    std::tuple<short, short, short, short> scores;
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&did), 4);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<0>(scores)), 1);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<1>(scores)), 1);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<2>(scores)), 1);
                    this->structInput.sinsub.read(reinterpret_cast<char*>(&std::get<3>(scores)), 1);
                    hp_posting.push(postings(std::to_string(did), std::get<0>(scores) + std::get<1>(scores) + std::get<2>(scores) + std::get<3>(scores), 4, cur_pos + 8, end_pos));
                }
            }
        }
        int max_topk = *std::max_element(std::begin(topk), std::end(topk));
        std::vector<std::string> real_did = {};
        std::fstream output(output_path + "/" + query, std::ios::in | std::ios::binary);
        int cnt_top = 0;
        std::string line;
        std::vector<std::string> line_splt;
        while (getline(output, line) && cnt_top < max_topk)
        {
            boost::split(line_splt, line, boost::is_any_of(" "), boost::token_compress_on);
            real_did.emplace_back(line_splt[1]);
            cnt_top ++;
        }
        output.close();

        std::unordered_map<int, std::unordered_map<int, bool>> topk_dict;
        if(metrics != "Recall") {
            for (auto i: topk) {
                for (auto j: budgets) {
                    topk_dict[i][j] = true;
                }
            }
        }


        std::unordered_map<int, std::vector<float>> query_acc = {};
        for(auto i : topk)
        {
            std::vector<std::string> real_tmp(real_did.begin(), real_did.begin() + i);
            for(auto j : budgets)
            {
                std::vector<std::string> lst_pred(pred_did.begin(), pred_did.begin() + j);
            }
        }
        return query_acc;
    }

    void realtime_heap_allocate::get_accuracy(std::string set_path, std::vector<int> & budget, std::vector<int> & topk, std::bitset<4> types, std::string metric="Recall") {
        std::vector<std::string> files{};
        for (const auto & entry : std::filesystem::directory_iterator(set_path))
            files.emplace_back(entry.path().string());
        std::unordered_map<int, std::vector<float>> avgacc;
        std::unordered_map<int, std::vector<std::vector<float>>> aux;

        for(auto & file : files)
        {
            std::unordered_map<int, std::vector<float>> dictacc = this->compute_hit_ratio(file, budget, topk, types, set_path, metric);
            this->query_name.emplace_back(file);
            for(auto & vk : dictacc)
            {
                for(int k = 0; k < budget.size(); k++)
                {
                    if(vk.second.at(k) != 0)
                    {
                        aux[vk.first][k].emplace_back(vk.second[k]);
                    }
                }
            }
        }
        for(auto & vk : aux)
        {
            for(int k = 0; k < vk.second.size(); k++)
            {
                avgacc[vk.first].emplace_back(std::accumulate(vk.second[k].begin(), vk.second[k].end(), 0) * 1.0 / vk.second[k].size());
            }
        }
        for(auto & vk : avgacc)
        {
            std::cout << "When k = " << vk.first << std::endl;
            for (auto i: vk.second)
                std::cout << i << " ";
        }
    }

    realtime_heap_allocate::realtime_heap_allocate(index_path single, index_path duplet, index_path triplet,
                                                   index_path quadruplet) {
        this->structPath.sinind = single;
        this->structPath.dupind = duplet;
        this->structPath.triind = triplet;
        this->structPath.quadind = quadruplet;

        this->structInput.sinsub.open(single.first, std::ios::in | std::ios::binary);
        this->structInput.dupsub.open(duplet.first, std::ios::in | std::ios::binary);
        this->structInput.trisub.open(triplet.first, std::ios::in | std::ios::binary);
        this->structInput.quadsub.open(quadruplet.first, std::ios::in | std::ios::binary);
    }


    comb_grams realtime_heap_allocate::get_comb(std::vector<std::string> &terms, std::bitset<4> & comb_type) {
        comb_grams comb = {};
        if(comb_type[0])
        {
            for (auto&& i : iter::combinations(terms, 1)) {
                std::string grams = boost::join(std::vector<std::string>(i.begin(), i.end()), " ");
                std::get<0>(comb).emplace_back(grams);
            }
        }
        if(comb_type[1])
        {
            for (auto&& i : iter::combinations(terms, 2)) {
                std::string grams = boost::join(std::vector<std::string>(i.begin(), i.end()), " ");
                std::get<1>(comb).emplace_back(grams);
            }
        }
        if(comb_type[2])
        {
            for (auto&& i : iter::combinations(terms, 3)) {
                std::string grams = boost::join(std::vector<std::string>(i.begin(), i.end()), " ");
                std::get<2>(comb).emplace_back(grams);
            }
        }
        if(comb_type[3])
        {
            for (auto&& i : iter::combinations(terms, 4)) {
                std::string grams = boost::join(std::vector<std::string>(i.begin(), i.end()), " ");
                std::get<3>(comb).emplace_back(grams);
            }
        }
        return comb;
    }

    float realtime_heap_allocate::metric_score(std::string metric, std::unordered_map<std::string, std::string> topk_dict,
                                               std::vector<std::string> topk_lst, std::vector<std::string> topk_pred) {
        if(topk_lst.empty())
        {
            return 0;
        }

        if(metric == "Recall")
        {
            std::vector<std::string> intersections;
            std::sort(topk_lst.begin(), topk_lst.end());
            std::sort(topk_pred.begin(), topk_pred.end());
            std::set_intersection(topk_lst.begin(),topk_lst.end(),topk_pred.begin(),topk_pred.end(), std::insert_iterator<std::vector<std::string>>(intersections,intersections.begin()));
            return intersections.size() * 1.0 / topk_lst.size();
        }
        else if(metric == "MAP")
        {
            auto [lst_index, denominator, numerator] = std::tuple<int, int, int>{0, 0, 0};
            std::vector<float> precisions = {};
            std::unordered_map<std::string, bool> topk_included = {};
            while(lst_index < topk_pred.size())
            {
                denominator++;
                if((topk_dict.find(topk_pred[lst_index]) != topk_dict.end()) &&
                    (topk_included.find(topk_pred[lst_index]) == topk_included.end()))
                {
                    topk_included[topk_pred[lst_index]] = true;
                    numerator++;
                    precisions.emplace_back(numerator * 1.0 / denominator);
                }
            }
            return precisions.empty() ? 0 : std::accumulate(precisions.begin(), precisions.end(), 0) * 1.0 / precisions.size();
        }
        else if(metric == "MRR")
        {
            for(int i = 0; i < topk_pred.size(); i++)
            {
                if(topk_dict.find(topk_pred[i]) != topk_dict.end())
                    return 1.0 / (i + 1);
            }
        }

        return 0;
    }

}