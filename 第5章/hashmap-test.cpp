#include <iostream>
#include <hash_map>
#include <cstring>
using namespace std;

struct eqstr
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1,s2) == 0;
    }
};

int main()
{
    hash_map<const char*, int, hash<const char*>, eqstr> days;

    days["january"] = 31;
    days["february"] = 28;
    days["march"] = 31;
    days["april"] = 30;
    days["may"] = 31;
    days["june"] = 30;
    days["july"] = 31;
    days["august"] = 31;
    days["september"] = 30;
    days["october"] = 31;
    days["november"] = 30;
    days["december"] = 31;

    cout << "september -> " << days["september"] << endl;           // 30
    cout << "june -> " << days["june"] << endl;                     // 30
    cout << "february -> " << days["february"] << endl;             // 28
    cout << "december -> " << days["december"] << endl;             // 31

    hash_map<const char*, int, hash<const char*>, eqstr>::iterator ite1 = days.begin();
    hash_map<const char*, int, hash<const char*>, eqstr>::iterator ite2 = days.end();
    for(; ite1 != ite2; ++ite1)
    {
        cout << ite1->first << " ";    // september june july may january february december march april november october august 
    }
    cout << endl;

}