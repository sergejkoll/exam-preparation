#ifndef EXAM_PREPARATION_LOCK_GUARD_HPP
#define EXAM_PREPARATION_LOCK_GUARD_HPP

template <class Mutex>
class lock_guard {
    Mutex& mut;

public:
    explicit lock_guard(Mutex& mut)
            : mut(mut)
    {
        mut.lock();
    }
    lock_guard(Mutex& mut, std::adopt_lock_t t)
            : mut(mut)
    {}

    ~lock_guard()
    {
        mut.unlock();
    }

    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;
};

#endif //EXAM_PREPARATION_LOCK_GUARD_HPP
