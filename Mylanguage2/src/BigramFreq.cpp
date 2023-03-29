#include <string>
#include "BigramFreq.h"
#include "Bigram.h"

BigramFreq::BigramFreq(){
    _bigram = Bigram("__");
    _frequency =0;
}

const Bigram &BigramFreq::getBigram()const{
    return _bigram;
    
}

const int BigramFreq::getFrequency() const{
    return _frequency;
}

void BigramFreq::setBigram(Bigram bigram){
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency){
    if (frequency >0){
        _frequency = frequency;
    }
    else{
        throw std::out_of_range("in function 'setFrequency' frequency < 0");
    }
}

  std::string BigramFreq::toString()const {
    
    return   " "+std::to_string(_frequency);
}