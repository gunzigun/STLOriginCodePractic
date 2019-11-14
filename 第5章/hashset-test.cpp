#include <iostream>
#include <hash_set>
#include <cstring>
using namespace std;

struct eqstr
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2);
    }
};

void lookup(const hash_set<const char*, hash<const char*>, eqstr>& Set, const char* word)
{
    hash_set<const char*, hash<const char*>, eqstr>::const_iterator it = Set.find(word);
    cout << " " << word << ": " << (it != Set.end() ? "present" : "not present") << endl;
}

int main()
{
    hash_set<const char*, hash<const char*>, eqstr> Set;
    Set.insert("kiwi");
    Set.insert("plum");
    Set.insert("apple");
    Set.insert("mango");
    Set.insert("apricot");
    Set.insert("banana");

    lookup(Set, "mango");               // mango:present
    lookup(Set, "apple");               // apple:present
    lookup(Set, "durian");              // durian:not present

    hash_set<const char*, hash<const char*>, eqstr>::iterator ite1 = Set.begin();
    hash_set<const char*, hash<const char*>, eqstr>::iterator ite2 = Set.end();
    for(; ite1 != ite2; ++ite1)
    {
        cout << *ite1 << " ";              // banana plum mango apple kiwi apricot
    }
    cout << endl;

    hash_set<int> Set1;             // 底层hashtable缺省大小为100，实际大小为193
    Set1.insert(59);
    Set1.insert(63);
    Set1.insert(108);
    Set1.insert(2);
    Set1.insert(53);
    Set1.insert(55);
    hash_set<int>::iterator ite_int1 = Set1.begin();
    hash_set<int>::iterator ite_int2 = Set1.end();
    for(; ite_int1 != ite_int2; ++ite_int1)
    {
        cout << *ite_int1 << " ";              // 2 53 55 59 63 108
    }
    cout << endl;

    hash_set<int> Set2;             // 底层hashtable缺省大小为100，实际大小为193
    Set2.insert(3);
    Set2.insert(196);
    Set2.insert(1);
    Set2.insert(389);
    Set2.insert(194);
    Set2.insert(387);
    hash_set<int>::iterator ite_int_1 = Set2.begin();
    hash_set<int>::iterator ite_int_2 = Set2.end();
    for(; ite_int_1 != ite_int_2; ++ite_int_1)
    {
        cout << *ite_int_1 << " ";              // 387 194 1 389 196 3
    }
    cout << endl;
}
