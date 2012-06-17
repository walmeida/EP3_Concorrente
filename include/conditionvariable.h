#ifndef CONDITION_VARIABLE_H_
#define CONDITION_VARIABLE_H_

#include "thread.h"
#include <queue>
#include <vector>
#include <stdexcept>

template<class T>
class ConditionVariable {
    public:
        ConditionVariable (unsigned int num_ranks);
        ~ConditionVariable ();
        void Insert (T t, int rank);
        T Remove ();
    private:
        unsigned int num_ranks_;
        std::vector<std::queue<T> > queue_;
        std::vector<unsigned int> queue_size_;
};

template<class T>
ConditionVariable<T>::ConditionVariable (unsigned int num_ranks) :
    num_ranks_(num_ranks), queue_(num_ranks),
    queue_size_(num_ranks, 0) {}

template<class T>
ConditionVariable<T>::~ConditionVariable () {}

template<class T>
void ConditionVariable<T>::Insert (T t, int rank) {
    queue_[rank].push (t);
    queue_size_[rank]++;
}

template<class T>
T ConditionVariable<T>::Remove () {
    unsigned int rank = 0;
    while (rank < num_ranks_ && queue_size_[rank] == 0)
        ++rank;
    if (rank == num_ranks_) {
        throw std::out_of_range("ConditionVariable<>::Remove(): empty queue");
    }
    T t = queue_[rank].front ();
    queue_[rank].pop ();
    queue_size_[rank]--;
    return t;
}

#endif
