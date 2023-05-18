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

 int BigramFreq::getFrequency() const{
    return _frequency;
}

void BigramFreq::setBigram(const Bigram &  bigram){
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
    
    return   _bigram.toString() + " " +std::to_string(_frequency);
}

  std::ostream operator<<(std::ostream os, const BigramFreq & bigramFreq){
      
  }
  bool operator>(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
      bool lower  = false;
      if(bigramFreq1.getFrequency() < bigramFreq2.getFrequency()){
          lower = true;
      }
      else if(bigramFreq1.getFrequency() == bigramFreq2.getFrequency()){
          if(bigramFreq1.getBigram().toString() < bigramFreq2.getBigram().toString()){
              lower  = true;
          }
      }
      return lower;
  }
  
  bool  operator<(const BigramFreq & bigramFreq1 , const BigramFreq & bigramFreq1){
        bool higher  = false;
      if(bigramFreq1.getFrequency() > bigramFreq2.getFrequency()){
          lower = true;
      }
      else if(bigramFreq1.getFrequency() == bigramFreq2.getFrequency()){
          if(bigramFreq1.getBigram().toString() < bigramFreq2.getBigram().toString()){
              higher  = true;
          }
      }
      return higher;
 
  }
  
  bool operator==(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
      bool same = false;
      if(bigramFreq1.getFrequency() == bigramFreq2.getFrequency() && 
              bigramFreq1.getBigram().toString() == bigramFreq2.getBigram().toString()){
          same = true; 
                  
          
      }
      return same ;
  }
  bool operator!=(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
      bool no_same = false;
      if(bigramFreq1.getFrequency() != bigramFreq2.getFrequency() && 
              bigramFreq1.getBigram().toString() != bigramFreq2.getBigram().toString()){
          no_same = true; 
                  
          
      }
      return no_same ;
  }
  
  bool operator<=(const BigramFreq & bigramFreq1 , const BigramFreq & bigramFreq2)
  bool lowerthan = false;
      if(bigramFreq1.getFrequency() <= bigramFreq2.getFrequency() && 
              bigramFreq1.getBigram().toString() <= bigramFreq2.getBigram().toString()){
          lowerthan = true;
      }
  return lowerthan;
  }
  
  bool operator>=(const BigramFreq & bigramFreq1 , const BigramFreq & bigramFreq2)
  bool biggerthan = false;
      if(bigramFreq1.getFrequency() >= bigramFreq2.getFrequency() && 
              bigramFreq1.getBigram().toString() >= bigramFreq2.getBigram().toString()){
          biggerthan = true;
      }
  return biggerthan;
  }