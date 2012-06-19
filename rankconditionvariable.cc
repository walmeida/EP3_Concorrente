#include "rankconditionvariable.h"
#include "thread.h"
#include <stdexcept>
#include <cassert>

RankConditionVariable::RankConditionVariable (unsigned int num_ranks) :
    num_ranks_(num_ranks), queue_(num_ranks),
    queue_size_(num_ranks, 0) {}

RankConditionVariable::~RankConditionVariable () {}

void RankConditionVariable::insert (sem_t* s, unsigned int rank) {
    assert(rank < num_ranks_);
    queue_[rank].push (s);
    queue_size_[rank]++;
}

sem_t* RankConditionVariable::remove () {
    unsigned int rank = getMinRank ();
    if (rank == num_ranks_) {
        throw std::out_of_range("RankConditionVariable<>::Remove(): empty queue");
    }
    sem_t* s = queue_[rank].front ();
    queue_[rank].pop ();
    queue_size_[rank]--;
    return s;
}

bool RankConditionVariable::empty () const {
    unsigned int rank = getMinRank ();
    if (rank == num_ranks_)
        return true;
    return false;
}

unsigned int RankConditionVariable::getMinRank () const {
    unsigned int rank = 0;
    while (rank < num_ranks_ && queue_size_[rank] == 0)
        ++rank;
    return rank;
}
