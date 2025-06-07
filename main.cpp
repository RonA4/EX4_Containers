// ronamsalem4@gmail.com
#include <iostream>
#include "MyContainer.hpp"
using namespace ariel;
/**
 This file serves as a comprehensive demonstration of the MyContainer class and its various iterators. It shows how to add and remove elements, print the container using the overloaded << operator, and iterate over the elements using six different traversal strategies. In addition, the program handles duplicate values ​​and exceptions. The output clearly illustrates the different behaviors of each iterator in practice.
Note: This is intentionally not fully documented, as the output after execution shows what actually happens.
 */
int main()
{
    MyContainer<int> container;
    container.addElement(7);
    container.addElement(15);
    container.addElement(6);
    container.addElement(1);
    container.addElement(2);

    std::cout << " Original container: " << container << std::endl;
    std::cout << "📦 Size: " << container.size() << std::endl;

    std::cout << "\n Ascending order: ";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << " Descending order: ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << "Side-cross order: ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << "Reverse order: ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << " Insertion order: ";
    for (auto it = container.begin_order(); it != container.end_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    std::cout << " Middle-out order: ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    MyContainer<int> container1;
    container1.addElement(4);
    container1.addElement(15);
    container1.addElement(4);
    container1.addElement(1);
    container1.addElement(4);
    std::cout << "\n Container with duplicates: " << container1 << std::endl;

    container1.removeElement(4);
    std::cout << " After removing all 4s: " << container1 << std::endl;

    try
    {
        container1.removeElement(999);
    }
    catch (const std::exception &e)
    {
        std::cout << " Exception caught: " << e.what() << std::endl;
    }
    MyContainer<int> container2;
    container2.addElement(33);
    container2.addElement(55);
    container2.addElement(22);
    container2.addElement(11);
    container2.addElement(44);
    auto it1 = container2.begin_ascending_order();
    std::cout << *it1 << std::endl;
  
    auto it2 = container2.begin_descending_order();
    std::cout << *it2 << std::endl;

    auto it3 = container2.begin_side_cross_order();
    std::cout << *it3 << std::endl;
   
    auto it4 = container2.begin_reverse_order();
    std::cout << *it4 << std::endl;

    auto it5 = container2.begin_order();
    std::cout << *it5 << std::endl;
    
    auto it6 = container2.begin_middle_out_order();
    std::cout << *it6 << std::endl;
    return 0;
}
