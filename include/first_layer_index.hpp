#include <string>
#include <utility>

namespace candidates {

    struct postings
    {
        std::string did;
        short score;
        int type;
        int64_t ptr;
        int64_t ends;

        postings(std::string did, short score, int type, int64_t ptr, int64_t ends)
            : did(std::move(did)), score(score), type(type), ptr(ptr), ends(ends) {}

        bool operator<(const postings & a) const
        {
            return this->score < a.score;
        }

        bool operator>(const postings & a) const
        {
            return this->score > a.score;
        }

        bool operator==(const postings & a) const
        {
            return this->score == a.score;
        }
    };

}

