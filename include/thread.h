#ifndef THREAD_H_
#define THREAD_H_

#include <semaphore.h>
#include <iostream>
#include <cstdio>

void* thread_run_wrapper (void *thread);

class Thread {
    public:
        Thread () : tid_(0) {
            sprintf (sem_name_, "sem_thread%llu", id_);
            semaphore_ = sem_open (sem_name_, O_CREAT | O_EXCL, S_IRWXU, 0);
            id_++;
        }
        ~Thread () {
            pthread_detach(tid_);
            sem_close (semaphore_);
            sem_unlink (sem_name_);
        }
        int start () {
            if (semaphore_ == SEM_FAILED)
                return 1;
            pthread_attr_t tattr;
            if (pthread_attr_init (&tattr))
                return 2;
            if (pthread_attr_setdetachstate (&tattr,PTHREAD_CREATE_DETACHED))
                return 3;
            if (pthread_create (&tid_, &tattr, thread_run_wrapper, (void *) this))
                return 4;
            pthread_attr_destroy (&tattr);
            return 0;
        }
        virtual void run () {}
        sem_t* getSemaphore () const {
            return semaphore_;
        }
    private:
        static unsigned long long id_;
        char sem_name_[100];
        pthread_t tid_;
        sem_t *semaphore_;
};

#endif
