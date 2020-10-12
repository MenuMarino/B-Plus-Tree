#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <bits/stdc++.h>
#include <istream>
#include <cstring>
#include <cstdio>
#define BF 2

using namespace std;



struct Registro{
    int id;
    char name[30];
    int pin;
    char country[30];


    Registro() = default;

    Registro(int id_, char* name_, short pin_, char* country_){
        id = id_;
        strncpy(name, name_, 30);
        pin = pin_;
        strncpy(country, country, 30);
    }

    void print(){
        cout << id << " ";
        cout << name << " ";
        cout << pin << " ";
        cout << country << endl;
    }

};



int getFileSize(const std::string &fileName)
{
    ifstream file(fileName.c_str(), ifstream::in | ifstream::binary);

    if(!file.is_open())
    {
        return -1;
    }

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}





class Bucket{
public:
    int blockingFactor = BF;
    int size = 0;
    int overflow = -1;
    Registro records[BF];

    Bucket(){}

    bool add(Registro rec){
        if(size<blockingFactor){
            records[size] = rec;
            size++;
            return true;
        }
        return false;
    }


};

template <class T>
int hashing(T rec, short gp){
    short mask = 0;
    mask = (mask|((int)(pow(2,gp)) - 1));
    return (rec & mask);
}





template <class T>
class StaticHash {
    string indexFileName = "index.txt";
    string dataFileName = "data.txt";
    string rawDataFileName = "datosReales.txt";
    int capacity;
    int blockingFactor;




public:
    StaticHash(int space): capacity{space}, blockingFactor {BF} {}

    void saveHash(){
        remove("index.txt");
        std::ofstream outfile (indexFileName);
        fstream indexFile;
        indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
        indexFile.seekp(0, ios::beg);

        for (auto& it: hashMap) {
            //cout << hashMap.size();
            indexFile.write((char *)& it.first, sizeof(it.first));

            indexFile.write((char *)& it.second, sizeof(it.second));
            //cout << it.first << " " << it.second << endl;
        }
        indexFile.close();
    }

    void loadHash(){
        fstream indexFile;
        auto tamano = getFileSize(indexFileName) / (sizeof(int)*2);
        //cout << tamano;
        indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
        int aux, aux1;
        indexFile.seekg(0, ios::beg);
        for(int i=0; i<tamano; ++i){
            indexFile.read((char*)& aux, sizeof(int));
            indexFile.read((char*)& aux1, sizeof(int));
            hashMap.insert({aux,aux1});
            //cout << aux << " " << hashMap[aux] <<  " " << aux1 << endl ;
        }

    }

    void showData(){
        fstream rawDataFile, dataFile;
        vector<Bucket> aux;
        rawDataFile.open(dataFileName, ios::in  | ios::binary);
        int size = getFileSize(dataFileName)/sizeof(Bucket);
        Bucket bb;

        for (int i = 0; i < size; ++i) {
            rawDataFile.read((char*)&bb,sizeof(bb));
            aux.push_back(bb);
            //bb.print();
        }
        int cont =0;
        for(auto it:aux){
            for(int i=0; i<it.size; ++i){
                cont++;
                it.records[i].print();
            }
        }
        cout << cont;
    }

    void search(int id){
        int hashpos = id % capacity;

        //cout << getFileSize(dataFileName)/ sizeof(Bucket);

        if(hashMap.find(hashpos) == hashMap.end()){
            cout << "No encontrado" << endl;
        }
        else{

            Bucket auxBucket;
            auto filepos = hashMap[hashpos];
            fstream data;
            here:
            data.open(dataFileName, ios::in | ios::out | ios::binary);
            data.seekg(filepos * sizeof(auxBucket), ios::beg);
            data.read((char*)& auxBucket, sizeof(auxBucket));
            data.close();
            for(int i=0; i<auxBucket.size; ++i){
                //auxBucket.records[i].print();
                if(auxBucket.records[i].id == id){
                    auxBucket.records[i].print();
                    return;
                }
            }
            if(auxBucket.overflow != -1){
                filepos = auxBucket.overflow;
                goto here;
            }else{
                cout <<  "No encontrado" << endl;
            }

        }

    }

    void buildHash(){
        fstream rawDataFile, dataFile;
        vector<Registro> aux;
        rawDataFile.open(rawDataFileName, ios::in  | ios::binary);
        int size = getFileSize("datosReales.txt")/sizeof(Registro);
        Registro bb;

        for (int i = 0; i < size; ++i) {
            rawDataFile.read((char*)&bb,sizeof(bb));
            aux.push_back(bb);
            //bb.print();
        }

        rawDataFile.close();
        Bucket auxBucket;
        int hashpos;

//        for(int  i=0; i<aux.size(); i++){
//            aux[i].print();
//        }

        for(int  i=0; i<aux.size(); i++){
           // aux[i].print();
            auto tamanobuckefile = getFileSize(dataFileName)/ sizeof(Bucket); //cantidad de buckets almacenados

            hashpos = aux[i].id % capacity;
           // cout << hashpos << endl;

            if(hashMap.find(hashpos) == hashMap.end()){

            //CASO 1: No existe la entrada, se debe crear un nuevo bucket en el dataFile.
                hashMap.insert({hashpos, tamanobuckefile});//inserto el id hasheado como key y la posición de inserción del nuevo bucket como value
               // cout << tamanobuckefile << endl;
                Bucket newBucket;
                newBucket.add(aux[i]);
               // newBucket.add(aux[i]);
                dataFile.open(dataFileName, ios::in | ios::out | ios::binary);
                dataFile.seekp(0, ios::end);
                dataFile.write((char*)& newBucket, sizeof(newBucket));

                dataFile.close();
            }else{

                auto datafilepos = hashMap[hashpos]; //chapo la posicion logica del bucket q corresponde al registro q quiero insertar
                dataFile.open(dataFileName, ios::in | ios::out | ios::binary); //leo el bucket correspondiente
                dataFile.seekg(datafilepos * sizeof(Bucket), ios::beg);
                dataFile.read((char*)& auxBucket, sizeof(auxBucket));

//                for(auto it: auxBucket.records){
//                    it.print();
//                }

                if(auxBucket.size < blockingFactor){

                    //CASO 2 no hay overflow, se lee el bucket, se agrega el registro y se mete de nuevo en el file
                    auxBucket.add(aux[i]);
                    dataFile.seekp(datafilepos * sizeof(Bucket), ios::beg);
                    dataFile.write((char*)& auxBucket, sizeof(auxBucket));
                    //cout << "a" << endl;

                }else{
                    //CASO 3 hay overflow, abro el bucket correspondiente, pongo en el campo overflow la posicion de insercion del nuevo bucket de overflow
                    //y lo appendeo al final del archivo
                    here1:

                    int pos1 = (int)dataFile.tellg() - sizeof(Bucket);
                    if(auxBucket.overflow == -1 && auxBucket.size == BF){

                        auxBucket.overflow = tamanobuckefile;
                        dataFile.seekp(pos1, ios::beg);
                        dataFile.write((char*)& auxBucket, sizeof(auxBucket));

                        dataFile.seekp(0, ios::end);
                        Bucket newBucket;
                        newBucket.add(aux[i]);
                        dataFile.write((char*)& newBucket, sizeof(newBucket));
                        dataFile.close();
                        continue;
                    }
                    else if(auxBucket.overflow != -1 && auxBucket.size == BF){
                        dataFile.seekg(auxBucket.overflow * sizeof(Bucket), ios::beg);
                        dataFile.read((char*)& auxBucket, sizeof(auxBucket));

                        goto here1;
                    }


                    dataFile.seekp(pos1, ios::beg);
                    auxBucket.add(aux[i]);
                    dataFile.write((char*)& auxBucket, sizeof(auxBucket));
                    
                    dataFile.close();

                }

            }


        }


        
        saveHash();

    }


    unordered_map<int, int> hashMap;
};