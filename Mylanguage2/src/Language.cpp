#include <fstream>
#include "Language.h"
#include"BigramFreq.h"

const std::string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";

Language::Language(){
    _languageId = "unknown";
    _size = 0;
            
}

Language::Language(int numberBigrams){
    _languageId = "unknown";
    
    if(numberBigrams > DIM_VECTOR_BIGRAM_FREQ || numberBigrams <0){
        throw std::out_of_range("incorrect number of bigrams at constructor Language(in numberBigrams)");
        
    }
    else {
        _size = numberBigrams;
        
        for(int x = 0; x<_size; x++){
            _vectorBigramFreq[x] = BigramFreq();
        }
        
    }
    
}

std::string Language::getLanguageId() const{
    return  _languageId;
}

void Language::setLanguageId(std::string id){
    _languageId = id;
}

const BigramFreq Language::at(int index)const {
    if(index <0 || index > _size){
        throw std::out_of_range("index out of range in function at(int index) class: Languge");
        
    }
    else {
        return _vectorBigramFreq[index];
    }
    
}

BigramFreq & Language::at(int index){
    if(index <0 || index > _size){
        throw std::out_of_range("index out of range in function at(int index) class: Languge");
        
    }
    else {
        return _vectorBigramFreq[index];
    }
    
}

const int Language::getSize() const{
    return _size;
}

int Language::findBigram(Bigram bigram) const {
    int x = 0;
    while((bigram.getText() != _vectorBigramFreq[x].getBigram().getText()) && (x<_size)){
        x++;
    }
    if(x =_size){
        return -1;
    }
    else{
        return x;
    }
}

    const std::string Language ::toString(){
        std::string text;
        text+=std::to_string(_size) + "\n";
        for(int x=0; x<_size; x++){
            text+= _vectorBigramFreq[x].toString() + "\n";
        }
        return text;
    }
    
    void Language::sort(){
        
        for(int x =0; x<_size; x++){
        BigramFreq max= _vectorBigramFreq[x];
        int pos = x;
        
        for(int j = x+1; j<_size; j++){    
            
            if(max.getFrequency() == _vectorBigramFreq[j].getFrequency()&&
                    max.getBigram().toString() > _vectorBigramFreq[j].getBigram().toString()){
               
                max = _vectorBigramFreq[j];
                pos = j;
                
            }
                        
            if(_vectorBigramFreq[j].getFrequency()>max.getFrequency()){
                max = _vectorBigramFreq[j];
                pos = j;
            }
        }
        
        BigramFreq swap;
        swap =_vectorBigramFreq[x];
        _vectorBigramFreq[x] = max;
        _vectorBigramFreq[pos] = swap;
        
    }
    }
     
    void Language::save(const char fileName[]) const{
        std::ofstream outputStream;
        
        outputStream.open(fileName);
        if(outputStream){
            outputStream << MAGIC_STRING_T;
            outputStream << _languageId;
            outputStream << _size;
            for(int j = 0 ; j < _size; j++){
                outputStream<<_vectorBigramFreq[j].toString();
            }
            
            outputStream.close();
        }
        
            
        
    }
     void Language::load(const char fileName[]){
        std::ifstream inputStream;
        std:: string magicCad ;
        int frequency ;
        std::string bigram;
        inputStream.open(fileName);
        if(inputStream){
            inputStream >>magicCad;
            inputStream >>_languageId;
            inputStream >> _size;
            if(magicCad != MAGIC_STRING_T){
                throw std::out_of_range("in function load Magic strings are not the same  ");
            }
            if(_size > DIM_VECTOR_BIGRAM_FREQ){
                throw std::out_of_range("there are more bigrams than size for them in load function ");
            }
            for(int x = 0; x<_size; x++){
                inputStream>>bigram;
                inputStream>>frequency;
                _vectorBigramFreq[x].setBigram(bigram);
                _vectorBigramFreq[x].setFrequency(frequency);
                
            }
            
            inputStream.close();
        }
        else{
            
        }
    }

    void Language::append(BigramFreq bigramFreq){
        int bigram_pos = findBigram(bigramFreq.getBigram());
        if(bigram_pos>=0){
            int new_frequency = bigramFreq.getFrequency() + _vectorBigramFreq[bigram_pos].getFrequency();
            _vectorBigramFreq[bigram_pos].setFrequency(new_frequency);
        }
        else if(_size < DIM_VECTOR_BIGRAM_FREQ){
            _vectorBigramFreq[_size] = bigramFreq;
            _size++;
        }
        else{
            throw std::out_of_range("There is no space for more bigrams . at function append ");
        }

    }
   

    void Language::join(Language language){
        
            for(int j = 0; j<  language.getSize(); j++){
                append(language.at(j));
            }
        
    }
    