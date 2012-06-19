#ifndef RANK_CONDITION_VARIABLE_H_
#define RANK_CONDITION_VARIABLE_H_

#include "conditionvariable.h"
#include <queue>
#include <vector>

class RankConditionVariable : public ConditionVariable {
    public:
        RankConditionVariable (unsigned int num_ranks = 1);
        ~RankConditionVariable ();
        void insert (sem_t* s, unsigned int rank);
        sem_t* remove ();
        bool empty () const;
        unsigned int getMinRank () const;
    private:
        unsigned int num_ranks_;
        std::vector<std::queue<sem_t*> > queue_;
        std::vector<unsigned int> queue_size_;
};

#endif
