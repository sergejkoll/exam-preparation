#ifndef EXAM_OPTIONAL_HPP
#define EXAM_OPTIONAL_HPP

#include <exception>
#include <optional>

using byte = char;

template <typename T>
class optional {
public:
    constexpr optional() noexcept : dummy{}, flag{false} {}
    constexpr optional(std::nullopt_t) noexcept : optional() {}
    constexpr optional( const optional& other ) = default;
    constexpr optional( optional&& other ) noexcept = default;
    optional<T>& operator=(const optional<T>&) = default;
    optional<T>& operator=(optional<T>&&) noexcept = default;

    T& operator*() {
        return val;
    }

    T* operator->() {
        return *val;
    }
    operator bool() const {
        return flag;
    }
    T& value() {
        if (flag) return val;
        else throw std::bad_optional_access();
    }

    template <class U>
    T value_or(U&& default_value) {
        if (flag) return val;
        else return static_cast<T>(std::forward<U>(default_value));
    }

private:
    union {
        byte dummy;
        std::remove_const_t<T> val;
    };
    bool flag;
};

#endif //EXAM_OPTIONAL_HPP
