#ifndef EXAM_PREPARATION_UNIQUE_LOCK_HPP
#define EXAM_PREPARATION_UNIQUE_LOCK_HPP


template <class Mutex>
class unique_lock {
    Mutex* m_Device_;
    bool m_Own_;

public:
    unique_lock() noexcept
            : m_Device_(nullptr)
            , m_Own_(false)
    {}

    ~unique_lock() {
        if (m_Own_) {
            unlock();
        }
    }

    unique_lock(unique_lock&& other) noexcept
            : m_Device_(other.m_Device_)
            , m_Own_(other.m_Own_)
    {
        other.m_Device_ = nullptr;
        other.m_Own_ = false;
    }

    explicit unique_lock(Mutex& m) {
        m_Device_ = &m;
        (*m_Device_).lock();
        m_Own_ = true;
    }

    unique_lock(Mutex& m, std::defer_lock_t) noexcept {
        m_Device_ = &m;
        m_Own_ = false;
    }

    /*adopt_lock_t это грубо говоря флаг который указывает lock_guard`у,
    что передаваемый mutex уже захвачен и не нужно вызывать вызыватьт метод lock,
    в противном случае будет повторный захват mutex`а и неопределенное поведение*/

    unique_lock(Mutex& m, std::adopt_lock_t) {
        m_Device_ = &m;
        m_Own_ = true;
    }

    void lock() {
        if (!m_Device_) {
            throw std::invalid_argument("Operation not permitted");
        } else if (!m_Own_) {
            throw std::invalid_argument("Resource deadlock would occur");
        } else {
            m_Device_->lock();
            m_Own_ = true;
        }
    }

    void unlock() {
        if (!m_Own_) {
            throw std::invalid_argument("Operation not permitted");
        } else {
            m_Device_->unlock();
            m_Own_ = false;
        }
    }

    unique_lock<Mutex>& operator=(unique_lock<Mutex>&& rhs) noexcept {
        if (m_Own_) {
            unlock();
        }

        unique_lock(std::move(rhs).swap(*this));

        rhs.m_Own_ = false;
        rhs.m_Device_ = nullptr;

        return *this;
    }
};
#endif //EXAM_PREPARATION_UNIQUE_LOCK_HPP
