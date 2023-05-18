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
    _frequency = new int [validChars.size()];
    _validCharacters = validChars;
    
}
BigramCounter::BigramCounter(BigramCounter orig){
     _frequency = orig._frequency;
     _validCharacters = orig._validCharacters;
     
}

BigramCounter::~BigramCounter(){
    delete [] _frequency;
    _frequency = nullptr;
}

int BigramCounter::getSize()const{
    return _validCharacters.size();
}

int BigramCounter::getNumberActiveBigrams()const{
    int bigramcounter = 0;
    for(int i =0; i<getSize();i++){
        for(int j =0; j<getSize();j++){
            if(_frequency[i][j] >0){
                bigramcounter++;
            }
        }
    }
    return bigramcounter;
    
}

bool BigramCounter::setFrequency(Bigram bigram ,int frequency){
    bool bigramOk = false;
    for(int i =0; i< _validCharacters.size() && !bigramOk){
    bigram.getText().at(0); 
    }
    
}