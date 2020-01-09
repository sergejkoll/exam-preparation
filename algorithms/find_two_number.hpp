#ifndef EXAM_PREPARATION_FIND_TWO_NUMBER_HPP
#define EXAM_PREPARATION_FIND_TWO_NUMBER_HPP

template <typename Iterator, typename T>
std::pair<bool, std::pair<Iterator, Iterator> > find_two_elements_with_sum(Iterator first, Iterator last, T c) {
    auto begin = first;
    auto end = last;

    while (begin != end) {
        if (*begin + *end == c) {
            return std::make_pair(true, std::make_pair(begin, end));
        }
        else if (*begin + *end < c) {
            ++begin;
        } else {
            --end;
        }
    }

    return std::make_pair(false, std::make_pair(first, last));
}

#endif //EXAM_PREPARATION_FIND_TWO_NUMBER_HPP
