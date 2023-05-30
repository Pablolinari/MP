/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 12 February 2023, 11:00
 */

#include "BigramCounter.h"
#include <iostream>
#include <fstream>


/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

BigramCounter::BigramCounter(std::string validChars ){
    alocate(validChars.size());
    _validCharacters = validChars;
    clean(_validCharacters.size());
    
}
BigramCounter::BigramCounter(const BigramCounter & orig){
     _frequency = orig._frequency;
     _validCharacters = orig._validCharacters;
     
}

BigramCounter::~BigramCounter(){
    delocate();
    _validCharacters = "";
}

int BigramCounter::getSize()const{
    return _validCharacters.size();
}

int BigramCounter::getNumberActiveBigrams()const{
    int active =0;
   for(int i = 0 ; i< _validCharacters.size(); i++){
        for(int j = 0; j< _validCharacters.size();j++){
            if(_frequency[i][j] > 0){
                active++;
            }
        }
   }
   return active;
}

bool BigramCounter::setFrequency(const Bigram &bigram ,int frequency){
    int i ,j;
    bool exist =false;
    i =_validCharacters.find(bigram.toString().at(0));
    j =_validCharacters.find(bigram.toString().at(1));

    if(i!= std::string::npos && j != std::string::npos){
        _frequency[i][j] = frequency;
        exist = true;
    }
    return exist;
}

void BigramCounter::increaseFrequency(const Bigram & bigram ,int frequency){
    int i,j;
    i =_validCharacters.find(bigram.toString().at(0));
    j =_validCharacters.find(bigram.toString().at(1));
    
    if(i!= std::string::npos && j != std::string::npos){
        if(frequency == 0){
            _frequency[i][j]++;
        }
        else{
            _frequency[i][j] = _frequency[i][j] + frequency;
        }
    }
    else{
        throw std::invalid_argument("theg iven bigram is not valid");
    }
}
BigramCounter & BigramCounter::operator=(const BigramCounter & orig){
    int **aux;
    aux = new int *[getSize()];
    for(int i = 0 ; i< getSize(); i++){
        aux[i] = new int[getSize()];
    }

    for(int i = 0; i< orig.getSize(); i++){
        for(int j = 0; j<orig.getSize();j++){
            aux[i][j] = orig(i,j);
        }
    }
    for(int i = 0 ; i<_validCharacters.size();i++){
        delete [] _frequency[i];
        _frequency[i] = nullptr;
    }
    delete [] _frequency;
    _frequency = aux;
    return *this;

}

BigramCounter & BigramCounter::operator+=(const BigramCounter & rhs){
    for(int i = 0; i< rhs.getSize(); i++){
        for(int j = 0; j<rhs.getSize();j++){
            _frequency[i][j] = rhs(i,j) + _frequency[i][j];
        }
    }
    return *this;
}

void BigramCounter::calculateFrequencies(char* fileName){
    std::ifstream read;
    clean(getSize());
    read.open(fileName);
    while (read){
        std::string line; 
        getline(read,line);
        int i, j;
        
        for(int i = 1; i< line.size();i++){
            if(isValidCharacter(tolower(line.at(i-1)),_validCharacters) && isValidCharacter(tolower(line.at(i)),_validCharacters)){
                increaseFrequency(Bigram(tolower(line.at(i-1)),tolower(line.at(i))));
            }
        }
    }
    read.close();
    
}
Language BigramCounter::toLanguage(){
    Language language;
    BigramFreq bigram;
    
    for(int i = 0; i<getSize(); i++){
        for(int j = 0; j< getSize(); j++){
            if(_frequency[i][j] > 0){
                bigram.setFrequency(_frequency[i][j]);
                bigram.setBigram(Bigram(_validCharacters.at(i) , _validCharacters.at(j)));
                language.append(bigram);
            }
        }
    }
    return language;
}
void BigramCounter::alocate(int n){
    _frequency = new int* [n];
    for(int i = 0 ; i < n ; i++){
        _frequency[i] = new int [n];
    }
    
}
void BigramCounter::delocate(){
    for(int i = 0; i < _validCharacters.size(); i++){
        delete [] _frequency[i];
        _frequency[i]= nullptr;
    }
    delete [] _frequency;
    _frequency = nullptr;
}

const int & BigramCounter::operator()(int row, int column)const{
    return  _frequency[row][column];
}
int & BigramCounter::operator()(int row, int column){
    return  _frequency[row][column];
}

void BigramCounter::clean(int s){
    for(int i = 0 ; i< s; i++){
        for(int j = 0; j< s; j++){
            _frequency[i][j] = 0;
        }
    }
}