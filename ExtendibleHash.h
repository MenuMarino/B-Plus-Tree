#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <istream>
#include <cstring>
using namespace std;


class Record{
    unsigned id;
    char name[20];
    short pin;
    char country[35];

    Record(unsigned id_, char* name_, short pin_, char* country_){
        id = id_;
        strncpy(name, name_, 20);
        pin = pin_;
        strncpy(country, country, 35);
    }

    void print(){
        cout << id << " ";
        cout << name << " ";
        cout << pin << " ";
        cout << country << endl;
    }

};

template <class T>
class Bucket{
    short blockingFactor;
    short size = 0;
    T* records = nullptr;

    Bucket(short blockingFactor_){
        blockingFactor = blockingFactor_;
        records = new T[blockingFactor];
    }
    bool add(T rec){
        if(size<blockingFactor){
            records[size] = rec;
            size++;
            return true;
        }
        return false;
    }

};

class ExtendibleHash {
     
};