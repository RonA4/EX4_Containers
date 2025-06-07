#ifndef __MYCONTAINER_HPP
#define __MYCONTAINER_HPP
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
/**
 * A generic container class with multiple custom iteration strategies.
 * The MyContainer class is a templated container that stores elements in a dynamic array (std::vector).
 * It supports basic operations such as adding and removing elements, and provides several iterator types
 * to traverse the elements in different logical orders:
 1. AscendingIterator: Iterates from smallest to largest.
 2.  DescendingIterator: Iterates from largest to smallest.
 3. SideCrossIterator: Alternates between the lowest and highest remaining elements.
 4.  ReverseOrder: Iterates in reverse insertion order.
 5.  Order: Iterates in the original insertion order.
 6. MiddleOutOrder: Starts from the middle and expands outward alternately.
 * All iterators inherit from a common abstract base class, BaseIterator, which implements shared logic  such as dereferencing, incrementing, and comparison. Each derived iterator class constructs its ow traversal order while reusing this common functionality.
 * Each iterator class also includes static begin() and end() methods as required, making them usable independently for container traversal.
 * The container throws exceptions when attempting to remove a non-existent elemen.
 */

namespace ariel
{
    /**
     * @class --->  MyContainer
     *  A templated container class that holds elements and provides multiple iteration strategies.
     * This container supports dynamic insertion and removal of elements and provides size querying and
     * printing functionalities. It serves as a basis for various custom iterators implemented as inner classes.
     * @tparam ---> T The type of elements stored in the container. Defaults to int.
     */
    template <typename T = int> //< Internal storage of elements.
    class MyContainer
    {

    private:
        std::vector<T> elements;

    public:
        /**
         *  Adds an element to the container.
         * @param val ---> The element to be added.
         */
        void addElement(const T &val) { elements.push_back(val); }

        /**
         * Removes the first occurrence of an element from the container.
         * @param val ---> The element to be removed.
         * @throws ---> std::invalid_argument if the element is not found.
         */
        void removeElement(const T &val)
        {
            auto original_size = elements.size();
            elements.erase(std::remove(elements.begin(), elements.end(), val), elements.end());
            if (elements.size() == original_size)
            {
                throw std::invalid_argument("Element not found in container");
            }
        }
        /**
         *  Returns the number of elements currently in the container.
         * @return ---> The size of the container.
         */
        size_t size() const
        {
            return elements.size();
        }

        /**
         *  Prints all elements in the container to the output stream.
         * @param os ---> The output stream.
         * @param container ---> The container to print.
         * @return ---> A reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const MyContainer<T> &container)
        {
            for (auto iterator = container.elements.begin(); iterator != container.elements.end(); iterator++)
                os << *iterator << " ";
            return os;
        }

        /**
         * @class BaseIterator
         *  base class for iterators over MyContainer.
         * This class provides common logic for all iterators such as element access,
         * increment, and comparison operations. Each derived iterator defines its own traversal order.
         */

        class BaseIterator
        {
        protected:
            const MyContainer<T> &container; //< Reference to the container being iterated.
            std::vector<T> order;            //< Ordered list of elements to iterate over.
            size_t index;                    //< Current index in the iteration.

        public:
            /**
             *  Constructs a BaseIterator with a given container and order.
             * @param contain ---> The container to iterate.
             * @param vec ---> The traversal order of elements.
             */
            BaseIterator(const MyContainer<T> &contain, std::vector<T> vec)
                : container(contain), order(std::move(vec)), index(0) {}

            /**
             * Dereference operator to access current element.
             * @return ---> The current element.
             * @throws --->  std::out_of_range if the index is beyond the end.
             */
            T operator*() const
            {
                if (index >= order.size())
                {
                    throw std::out_of_range("Dereferencing past-the-end iterator");
                }
                return order.at(index);
            }

            /**
             *  Pre-increment operator.
             * @return ---> Reference to this iterator after incrementing.
             */
            BaseIterator &operator++()
            {
                index++;
                return *this;
            }

            /**
             *  Post-increment operator.
             * @return ---> Copy of this iterator before incrementing.
             */
            BaseIterator operator++(int)
            {
                BaseIterator temp = *this;
                ++(*this);
                return temp;
            }
            /**
             *  Equality operator.
             * @param other ---> Another iterator to compare.
             * @return ---> True if both iterators are at the same position.
             */
            bool operator==(const BaseIterator &other) const
            {
                return index == other.index;
            }
            /**
             *  Inequality operator.
             * @param other --->  Another iterator to compare.
             * @return --->  True if the iterators are not at the same position.
             * @throws---->  std::invalid_argument if the iterators belong to different containers.
             */
            bool operator!=(const BaseIterator &other) const
            {
                if (&container != &other.container)
                {
                    throw std::invalid_argument("Cannot compare iterators from different containers");
                }
                return index != other.index;
            }
        };

        /**
         * @class ---> AscendingIterator
         * Iterator that traverses elements of MyContainer in ascending order.
         * Constructs a sorted view of the container's elements from smallest to largest.
         * If constructed with 'end=true', points to one past the last element.
         */

        class AscendingIterator : public BaseIterator
        {
        public:
            AscendingIterator(const MyContainer &contain, bool end = false) : BaseIterator(contain, contain.elements)
            {
                if (contain.elements.empty())
                {
                    if (end)
                        this->index = 0;
                    return;
                }

                for (size_t i = 0; i < this->order.size(); i++)
                {
                    for (size_t j = 0; j < this->order.size() - 1 - i; j++)
                        if (this->order[j] > this->order[j + 1])
                            std::swap(this->order[j], this->order[j + 1]);
                }
                if (end)
                    this->index = this->order.size();
            }
            /**
             * Returns an AscendingIterator to the beginning of the container.
             */
            static AscendingIterator begin(const MyContainer &c) { return AscendingIterator(c); }
            /**
             *Returns an AscendingIterator to the beginning of the container.
             */
            static AscendingIterator end(const MyContainer &c) { return AscendingIterator(c, true); }
        };

        /**
         * @class ---> DescendingIterator
         *  Iterator that traverses elements of MyContainer in descending order.
         * Constructs a sorted view of the container's elements from largest to smallest.
         * If constructed with 'end=true', points to one past the last element.
         */
        class DescendingIterator : public BaseIterator
        {
        public:
            DescendingIterator(const MyContainer &contain, bool end = false) : BaseIterator(contain, contain.elements)
            {
                if (contain.elements.empty())
                {
                    if (end)
                        this->index = 0;
                    return;
                }
                for (size_t i = 0; i < this->order.size(); i++)
                {
                    for (size_t j = 0; j < this->order.size() - 1 - i; j++)
                        if (this->order[j] < this->order[j + 1])
                            std::swap(this->order[j], this->order[j + 1]);
                }
                if (end)
                    this->index = this->order.size();
            }
            /**
             * Returns a DescendingIterator to the beginning of the container.
             */
            static DescendingIterator begin(const MyContainer &c) { return DescendingIterator(c); }
            /**
             *  Returns a DescendingIterator to the end of the container.
             */
            static DescendingIterator end(const MyContainer &c) { return DescendingIterator(c, true); }
        };

        /**
         * @class ---> SideCrossIterator
         * Iterator that alternates between the smallest and largest remaining elements.
         * First yields the smallest, then the largest, then second smallest, second largest, etc.
         * Useful for symmetric or center-out patterns.
         */

        class SideCrossIterator : public BaseIterator
        {
        public:
            SideCrossIterator(const MyContainer &contain, bool end = false) : BaseIterator(contain, {})
            {
                if (contain.elements.empty())
                {
                    if (end)
                        this->index = 0;
                    return;
                }

                std::vector<T> temp = contain.elements;
                std::sort(temp.begin(), temp.end());
                size_t left = 0, right = temp.size() - 1;
                while (left <= right)
                {
                    this->order.push_back(temp[left]);
                    left++;
                    if (left <= right)
                    {
                        this->order.push_back(temp[right]);
                        right--;
                    }
                }
                if (end)
                    this->index = this->order.size();
            }
            /**
             * Returns a SideCrossIterator to the beginning of the container.
             */
            static SideCrossIterator begin(const MyContainer &c) { return SideCrossIterator(c); }
            /**
             * Returns a SideCrossIterator to the end of the container.
             */
            static SideCrossIterator end(const MyContainer &c) { return SideCrossIterator(c, true); }
        };

        /**
         * @class ---> ReverseOrder
         * Iterator that traverses elements in reverse insertion order.
         * The last element added is visited first.
         */
        class ReverseOrder : public BaseIterator
        {
        public:
            ReverseOrder(const MyContainer &contain, bool end = false) : BaseIterator(contain, {})
            {
                if (contain.elements.empty())
                {
                    if (end)
                        this->index = 0;
                    return;
                }
                const std::vector<T> &temp = contain.elements;
                for (auto iterator = temp.rbegin(); iterator != temp.rend(); iterator++)
                    this->order.push_back(*iterator);
                if (end)
                    this->index = this->order.size();
            }

            /**
             * Returns a ReverseOrder iterator to the beginning of the container (last inserted element).
             */
            static ReverseOrder begin(const MyContainer &c) { return ReverseOrder(c); }

            /**
             * Returns a ReverseOrder iterator to the end of the container.
             */
            static ReverseOrder end(const MyContainer &c) { return ReverseOrder(c, true); }
        };

        /**
         * @class ---> Order
         * Iterator that preserves the insertion order of elements.
         * Elements are visited in the same sequence they were added.
         */

        class Order : public BaseIterator
        {
        public:
            Order(const MyContainer &contain, bool end = false) : BaseIterator(contain, contain.elements)
            {
                if (end)
                    this->index = this->order.size();
            }
            /**
             * Returns an Order iterator to the beginning of the container.
             */

            static Order begin(const MyContainer &c) { return Order(c); }
            /**
             * Returns an Order iterator to the end of the container.
             */
            static Order end(const MyContainer &c) { return Order(c, true); }
        };

        /**
         * @class ---> MiddleOutOrder
         * Iterator that starts from the middle element and expands outward.
         * For even sizes, starts from left-middle. Then alternates left/right.
         */

        class MiddleOutOrder : public BaseIterator
        {
        public:
            MiddleOutOrder(const MyContainer &contain, bool end = false) : BaseIterator(contain, {})
            {
                const std::vector<T> &temp = contain.elements;
                if (temp.empty())
                {
                    if (end)
                        this->index = 0;
                    return;
                }
                if (temp.size() == 0)
                    return;
                size_t middle = temp.size() / 2;
                if (temp.size() % 2 == 0)
                    middle--;
                this->order.push_back(temp[middle]);
                size_t left = middle;
                size_t right = middle + 1;
                while (left > 0 || right < temp.size())
                {
                    if (left > 0)
                    {
                        left--;
                        this->order.push_back(temp[left]);
                    }
                    if (right < temp.size())
                    {
                        this->order.push_back(temp[right]);
                        right++;
                    }
                }
                if (end)
                    this->index = this->order.size();
            }
            /**
             * Returns a MiddleOutOrder iterator to the beginning of the container.
             */
            static MiddleOutOrder begin(const MyContainer &c) { return MiddleOutOrder(c); }
            /**
             * Returns a MiddleOutOrder iterator to the end of the container.
             */
            static MiddleOutOrder end(const MyContainer &c) { return MiddleOutOrder(c, true); }
        };
        /**
         * Returns an AscendingIterator to the beginning.
         */
        AscendingIterator begin_ascending_order() const { return AscendingIterator(*this); }
        /**
         * Returns an AscendingIterator to the end.
         */
        AscendingIterator end_ascending_order() const { return AscendingIterator(*this, true); }
        /**
         * Returns a DescendingIterator to the beginning.
         */

        DescendingIterator begin_descending_order() const { return DescendingIterator(*this); }
        /**
         * Returns a DescendingIterator to the end.
         */
        DescendingIterator end_descending_order() const { return DescendingIterator(*this, true); }
        /**
         * Returns a SideCrossIterator to the beginning.
         */

        SideCrossIterator begin_side_cross_order() const { return SideCrossIterator(*this); }
        /**
         * Returns a SideCrossIterator to the end.
         */
        SideCrossIterator end_side_cross_order() const { return SideCrossIterator(*this, true); }
        /**
         * Returns a ReverseOrder iterator to the beginning.
         */

        ReverseOrder begin_reverse_order() const { return ReverseOrder(*this); }
        /**
         * Returns a ReverseOrder iterator to the end.
         */
        ReverseOrder end_reverse_order() const { return ReverseOrder(*this, true); }
        /**
         * Returns an Order iterator to the beginning.
         */

        Order begin_order() const { return Order(*this); }
        /**
         * Returns an Order iterator to the end.
         */
        Order end_order() const { return Order(*this, true); }
        /**
         * Returns a MiddleOutOrder iterator to the beginning.
         */

        MiddleOutOrder begin_middle_out_order() const { return MiddleOutOrder(*this); }
        /**
         * Returns a MiddleOutOrder iterator to the end.
         */

        MiddleOutOrder end_middle_out_order() const { return MiddleOutOrder(*this, true); }
    };

#endif
}
