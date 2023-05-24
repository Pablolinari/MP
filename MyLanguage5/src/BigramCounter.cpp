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


/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

BigramCounter::BigramCounter(std::string validChars = DEFAULT_VALID_CHARACTERS){
    _frequency = new int *[validChars.size()];
    for(int i = 0; i < validChars.size();i++){
        _frequency[i] = new int [validChars.size()];
    }
    _validCharacters = validChars;
    
}
BigramCounter::BigramCounter(const BigramCounter & orig){
     _frequency = orig._frequency;
     _validCharacters = orig._validCharacters;
     
}

BigramCounter::~BigramCounter(){
    for(int i = 0 ; i<_validCharacters.size();i++){
        delete [] _frequency[i];
        _frequency[i] = nullptr;
    }
    delete [] _frequency;
    _frequency = nullptr;
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

void BigramCounter::increaseFrequency(const Bigram & bigram ,int frequency =0){
    int i,j;
    i = getFil(bigram);
    j = getCol(bigram);
    
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

}

BigramCounter & BigramCounter::operator+=(const BigramCounter & rhs){
    for(int i = 0; i< rhs.getSize(); i++){
        for(int j = 0; j<rhs.getSize();j++){
            _frequency[i][j] = rhs(i,j) + _frequency[i][j];
        }
    }
}

void calculateFrequencies(char* fileName){

}

int & BigramCounter::operator()(int row, int column)const{
    return  _frequency[row][column];
}
int & BigramCounter::operator()(int row, int column){
    return  _frequency[row][column];
}
int BigramCounter::getCol (const Bigram & bi){
    return _validCharacters.find(bi.toString().at(1));
}
int BigramCounter::getFil (const Bigram & bi){
    return _validCharacters.find(bi.toString().at(0));
}