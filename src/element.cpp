#include <iostream>
#include "element.hpp"

// Byte
size_t Byte::operator[](size_t index)
{
    if (index == 0)
        return static_cast<unsigned int>(m_b0);
    if (index == 1)
        return static_cast<unsigned int>(m_b1);
    if (index == 2)
        return static_cast<unsigned int>(m_b2);
    if (index == 3)
        return static_cast<unsigned int>(m_b3);
    if (index == 4)
        return static_cast<unsigned int>(m_b4);
    if (index == 5)
        return static_cast<unsigned int>(m_b5);
    if (index == 6)
        return static_cast<unsigned int>(m_b6);
    if (index == 7)
        return static_cast<unsigned int>(m_b7);

    return -1;
}

// Element
size_t Element::operator[](size_t index)
{
    size_t byteNo = index / 8;
    size_t bitNo = index % 8;

    return m_bytes[byteNo][bitNo];
}

bool Element::operator<(const Element &other)
{
    return m_value < other.m_value;
}

// MultisetElement
size_t MultisetElement::operator[](size_t index)
{
    return m_element[index];
}

bool MultisetElement::operator<(const MultisetElement &other)
{
    return m_element < other.m_element;
}

void grayCodeGeneration(int n, MultisetElement* array, int depth, int occurrenceNo)
{
    int i, t = (1 << (depth - 1));

    if (depth == 0)
    {
        array[0].m_element.setValue(0);
        array[0].m_occurrenceNo = occurrenceNo;
    }
    else
    {
        for (i = 0; i < t; ++i)
        {
            array[t + i].m_element.setValue(array[t - i - 1].m_element.getValue() + (1 << (depth - 1)));
            array[t + i].m_occurrenceNo = occurrenceNo;
        }
    }
    if (depth != n)
        grayCodeGeneration(n, array, depth + 1, occurrenceNo);
}
