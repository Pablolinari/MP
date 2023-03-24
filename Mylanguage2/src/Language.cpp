#include "Language.h"

Language :: Language(){
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

std::string Language::getLanguageId(){
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

int Language::findBigram(Bigram bigram){
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
        
    }