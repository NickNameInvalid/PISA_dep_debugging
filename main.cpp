#include "realtime_heap_allocate.hpp"
//#include "pisa/tools/app.hpp"
using namespace pisa;

using wand_raw_index = wand_data<wand_data_raw>;
using wand_uniform_index = wand_data<wand_data_compressed<>>;
using wand_uniform_index_quantized = wand_data<wand_data_compressed<PayloadType::Quantized>>;
using query_function = std::function<std::vector<typename topk_queue::entry_type>(Query)>;
using scorers = std::unique_ptr<index_scorer<wand_data<wand_data_raw>>, std::default_delete<index_scorer<wand_data<wand_data_raw>>>>;
using documents = Payload_Vector<std::string_view>;
using sources = shared_ptr<mio::mmap_source>;

//struct term_and_didlist {
//    const Query single_query;
//    std::vector<uint64_t> vec_target_did;
//};
//
//term_and_didlist get_term_and_didlist(std::string input_line, App<arg::Index,
//        arg::WandData<arg::WandMode::Required>,
//        arg::Query<arg::QueryMode::Ranked>,
//        arg::Algorithm,
//        arg::Scorer,
//        arg::Thresholds,
//        arg::Threads> &
//        app) {
//    std::vector<uint64_t> vec_target_did{0};
//    term_and_didlist term_didlist_to_return = {app.lookup(input_line), vec_target_did};
////    for(auto & i : term_didlist_to_return.vec_target_did)
////    {
////        std::cout << i << std::endl;
////    }
//    return term_didlist_to_return;
//}
//
//template <typename IndexType, typename WandType>
//void termdid_score(
//        documents & docmap,
//        scorers & scorer,
//        query_function & query_fun,
//        IndexType & index,
//        WandType & wdata,
//        App<arg::Index,
//                arg::WandData<arg::WandMode::Required>,
//                arg::Query<arg::QueryMode::Ranked>,
//                arg::Algorithm,
//                arg::Scorer,
//                arg::Thresholds,
//                arg::Threads> & app)
//{
//        termdidlist_search td_s;
//
//        string a("oklahoma");
//        term_and_didlist tmp_struct = get_term_and_didlist(a, app);
////        std::cout << "2" << std::endl;
//        const Query& single_query = tmp_struct.single_query;
//        std::vector<uint64_t> & vec_target_did = tmp_struct.vec_target_did;
////        std::cout << "3" << std::endl;
//        std::vector<double> lookup_score = td_s(make_max_scored_cursors(index, wdata, *scorer, single_query) , index.num_docs(), vec_target_did);
//        for(auto & i : lookup_score)
//        {
//            std::cout << i << " " << std::endl;
//        }
////        std::cout << "4" << std::endl;
//    }
//
//template <typename IndexType, typename WandType>
//auto MapData(const string & documents_filename, App<arg::Index,
//        arg::WandData<arg::WandMode::Required>,
//        arg::Query<arg::QueryMode::Ranked>,
//        arg::Algorithm,
//        arg::Scorer,
//        arg::Thresholds,
//        arg::Threads> & app)
//{
//    struct result_of
//    {
////        IndexType & index;
////        WandType & wand;
//        scorers scorer;
//        documents docmap;
//        query_function query_fun;
//        sources source;
//    };
//
////    IndexType index(MemorySource::mapped_file(app.index_filename()));
////    WandType wdata(MemorySource::mapped_file(app.wand_data_path()));
//    auto index = make_unique<IndexType>(MemorySource::mapped_file(app.index_filename()));
//    auto wdata = make_unique<WandType>(MemorySource::mapped_file(app.wand_data_path()));
//
//    auto scorer = scorer::from_params(app.scorer_params(), wdata);
//    std::function<std::vector<typename topk_queue::entry_type>(Query)> query_fun;
//
//    auto source = std::make_shared<mio::mmap_source>(documents_filename.c_str());
//    Payload_Vector docmaps = Payload_Vector<>::from(*source);
////    return result_of{index, wand, scorer, docmaps, query_fun, source};
//    return std::make_tuple(std::move(index.get()), std::move(wdata.get()), std::move(scorer), std::move(docmaps), std::move(query_fun), std::move(source));
//};

int main(int argc, const char** argv) {

    std::string documents_file;

    App<arg::Index,
    arg::WandData<arg::WandMode::Required>,
    arg::Query<arg::QueryMode::Ranked>,
    arg::Algorithm,
    arg::Scorer,
    arg::Thresholds,
    arg::Threads>
            app{"Retrieves query results in TREC format."};
    app.add_option("--documents", documents_file, "Document lexicon")->required();

    CLI11_PARSE(app, argc, argv);
    std::string query_root_path = "/home/jg6226/data/Hit_Ratio_Project";

    std::string single_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Lexicon/CW09B.fwd.terms";
    std::string single_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/single_with_termscore/single_lexicon.txt";
    std::string single_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/single_with_termscore/single_prefix";

    std::string duplet_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/Prefix_Grams/duplet_cleaned.txt";
    std::string duplet_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/duplet_with_termscore/duplet_lexicon.txt";
    std::string duplet_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/duplet_with_termscore/duplet_prefix";
//
    std::string triplet_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/Prefix_Grams/triplet_cleaned.txt";
    std::string triplet_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/triplet_with_termscore/triplet_lexicon.txt";
    std::string triplet_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/triplet_with_termscore/triplet_prefix";

    std::string quadruplet_gram_path = "/home/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/Prefix_Grams/quadruplet_cleaned.txt";
    std::string quadruplet_substructure_lexicon_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/quadruplet_with_termscore/quadruplet_lexicon.txt";
    std::string quadruplet_substructure_path = "/ssd3/jg6226/data/Hit_Ratio_Project/Real_Time_Query_System/First_Layer_Index/quadruplet_with_termscore/quadruplet_prefix";

    candidates::index_path single = std::make_tuple(single_gram_path, single_substructure_lexicon_path, single_substructure_path);
    candidates::index_path duplet = std::make_tuple(duplet_gram_path, duplet_substructure_lexicon_path, duplet_substructure_path);
    candidates::index_path triplet = std::make_tuple(triplet_gram_path, triplet_substructure_lexicon_path, triplet_substructure_path);
    candidates::index_path quadruplet = std::make_tuple(quadruplet_gram_path, quadruplet_substructure_lexicon_path, quadruplet_substructure_path);

    candidates::realtime_heap_allocate allocate(single, duplet, triplet, quadruplet);
    block_simdbp_index index(MemorySource::mapped_file(app.index_filename()));
    wand_raw_index wdata(MemorySource::mapped_file(app.wand_data_path()));
    auto scorer = scorer::from_params(app.scorer_params(), wdata);
    std::function<std::vector<typename topk_queue::entry_type>(Query)> query_fun;
    auto source = std::make_shared<mio::mmap_source>(documents_file.c_str());
    Payload_Vector docmap = Payload_Vector<>::from(*source);
//    double res = allocate.did_score<block_simdbp_index, wand_raw_index>(index, wdata, scorer, query_fun, docmap, app, "oklahoma", 0);
//    std::cout << res << std::endl;

//    block_simdbp_index index(MemorySource::mapped_file(app.index_filename()));
//    wand_raw_index wdata(MemorySource::mapped_file(app.wand_data_path()));
//    auto [index, wdata, scorer, docmap, query_fun, source] = MapData<block_simdbp_index, wand_raw_index>(documents_file, app);

//    termdid_score<std::shared_ptr<block_simdbp_index>, std::shared_ptr<wand_raw_index>>(docmap, scorer, query_fun, index, wdata, app);

////    // load lexicon
//    realtime_heap_allocate_obj.initialize();
//
//    // experiment configuration
//    std::vector<int> lst_budget = {500, 1000, 2000, 3000, 4000, 5000, 6000, 8000, 12000, 15000,
//                                   18000, 25000, 35000, 50000, 65000, 80000, 100000, 120000, 140000, 160000,
//                                   180000, 200000, 225000, 250000, 275000, 300000, 350000, 400000, 500000};
//    std::vector<int> lst_top_k = {10, 100, 1000};
//
////    std::vector<int> lst_budget = {5000};
////    std::vector<int> lst_top_k = {1000};
//    //std::vector<int> lst_type = {1, 2, 3, 4};
//    std::bitset<4> lst_type("1111");
//    std::string query_set_path = "/home/jg6226/data/Hit_Ratio_Project/Split_Test_Output_Quantized";
//    std::unordered_map<int, std::vector<float>> one_query_result;
//    std::vector<std::string> a = realtime_heap_allocate_obj.split("1003_com paparazziphotoart www", " ");
////
////    for(auto & jj : a)
////    {
////        std::cout << jj << std::endl;
////    }
////
//    clock_t start, end;
//    start = clock();
//    one_query_result = realtime_heap_allocate_obj.compute_hit_ratio("/home/jg6226/data/Hit_Ratio_Project/Split_Test_Output_Quantized/1003_com paparazziphotoart www", lst_budget, lst_top_k, lst_type, "Recall");
//    end = clock();
//    double one_query_running_time = double(end - start) / double(CLOCKS_PER_SEC);
//    std::cout << "Time to compute one query: " << one_query_running_time << "s\n";
////
////
////
//    for (auto top_k: lst_top_k) {
//        std::cout << "When k = " << top_k << ":\n";
//        std::cout << '[';
//        for (auto acc: one_query_result[top_k]) {
//            std::cout << acc << ", ";
//        }
//        std::cout << "]\n";
//    }
//
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
}
