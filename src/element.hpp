#pragma once

class Byte {
public:
    size_t operator[](size_t index);

private:
	unsigned char m_b0 : 1;
	unsigned char m_b1 : 1;
	unsigned char m_b2 : 1;
	unsigned char m_b3 : 1;
	unsigned char m_b4 : 1;
	unsigned char m_b5 : 1;
	unsigned char m_b6 : 1;
	unsigned char m_b7 : 1;
};

union Element {
public:
    int getValue() const { return m_value; }
    void setValue(int value) { m_value = value; }

    size_t operator[](size_t index);
    bool operator<(const Element &other);

private:
	int m_value;
	Byte m_bytes[sizeof(int)];
};

class MultisetElement {
public:
    int getElement() const { return m_element.getValue(); }
    int getOccurrenceNo() const { return m_occurrenceNo; }

    void setOccurrenceNo(int occurrenceNo) { m_occurrenceNo = occurrenceNo; }

    bool operator<(const MultisetElement &other);
    size_t operator[](size_t index);

    friend void grayCodeGeneration(int, MultisetElement *, int, int);
private:
    Element m_element;
	int m_occurrenceNo;
};

void grayCodeGeneration(int n, MultisetElement *array, int depth, int occurenceNo = 1);
