// increment, decrement, dereference
#include <iostream>
using namespace std;

class INT
{
    friend ostream& operator<<(ostream& os, const INT& i);
public:
    INT(int i) : m_i(i) {};

    // increment and then fetch
    INT& operator++()
    {
        ++(this->m_i);
        return *this;
    }

    // fetch and then increment
    const INT operator++(int)
    {
        INT temp = *this;
        ++(*this);
        return temp;
    }

    // decrement and then fetch
    INT& operator--()
    {
        --(this->m_i);
        return *this;
    }

    // fetch and then increment
    const INT operator--(int)
    {
        INT temp = *this;
        --(*this);
        return temp;
    }

    int& operator*() const
    {
        return (int&)m_i;
        // 以上转换操作告诉编译器，你确实要将const int 转化为non-const lvalue
        // 如果不明白的转型，有些编译器，会warning，有些会error
    }

private:
    int m_i;
};

ostream& operator<<(ostream& os, const INT& i)
{
    os << '[' << i.m_i << ']' << endl;
    return os;
}

int main()
{
    INT I(5);
    cout << I++;       // [5]; 
    cout << ++I;       // [7];
    cout << I--;       // [7];
    cout << --I;       // [5];
    cout << *I;        // 5;
}