#ifndef MI_DEREFERENCE_ITERATOR_HPP
#define MI_DEREFERENCE_ITERATOR_HPP

#include <memory>

namespace mi
{

template <typename IteratorType>
class dereference_iterator
{
public:
    using iterator_type            = IteratorType;
    using iterator_pointer         = iterator_type *;
    using iterator_reference       = iterator_type &;
    using iterator_const_reference = iterator_type const &;

    explicit dereference_iterator(iterator_const_reference iterator)
        : m_iterator(iterator)
    {
    }

private:
    iterator_pointer m_iterator;
};

} // namespace mi

#endif /* MI_DEREFERENCE_ITERATOR_HPP */
