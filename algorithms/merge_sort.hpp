#ifndef EXAM_PREPARATION_MERGE_SORT_HPP
#define EXAM_PREPARATION_MERGE_SORT_HPP

template <typename Iterator1, typename Iterator2>
Iterator2 merge(Iterator1 first1, Iterator1 last1, Iterator1 first2, Iterator1 last2, Iterator2 output) {
    auto it1 = first1;
    auto it2 = first2;

    while (it1 != last1 && it2 != last2) {
        // *(output++) = (*it1 < *it2) ? *(it1++) : *(it2++);
        
        if (*it1 < *it2) {
            *output = *it1;
            ++it1;
        } else {
            *output = *it2;
            ++it2;
        }
        ++output;
    }

    while (it1 != last1) {
        *output = *it1;
        ++it1;
        ++output;
    }

    while (it2 != last2) {
        *output = *it2;
        ++it2;
        ++output;
    }

    return output;
}

#endif //EXAM_PREPARATION_MERGE_SORT_HPP
