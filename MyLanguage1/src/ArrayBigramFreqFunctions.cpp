/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <string>
#include <iostream>
#include"BigramFreq.h"
#include "Bigram.h"
void readArrayBigramFreq(BigramFreq array[], int dim, int &nElements){
    
    std::cin >> nElements;
    
    if (nElements > dim){ 
        dim = nElements;
    }
        for (int x=0; x<nElements ; x++){
            std::string bi;
            int freq;
            std::cin >> bi;
            std::cin >> freq;
            BigramFreq aux;
            Bigram the_bigram(bi);
            aux.setBigram(the_bigram);   aux.setFrequency(freq);
            array[x] = aux;
            
            
        }
    
    
}

void printArrayBigramFreq(BigramFreq array[], int nElements){
    std::cout<<nElements;
    for(int x=0; x<nElements+1;x++){
       std::cout<<std::endl<<array[x].getBigram().toString()<<" "<< array[x].getFrequency();
    }
}

void swapElementsArrayBigramFreq(BigramFreq array[], int nElements, int first,int second){
    if(first < nElements && second <nElements){
        BigramFreq swap;
        
        swap = array[first];
        array[first] = array[second];
        array[second]=swap;
        
    }
    else{
        throw std::out_of_range("in swapElementsArrayBigramFreq index out of range  ");
    }
}
void toUpperArrayBigramFreq(BigramFreq array[], int nElements){
    for(int x=0; x<nElements;x++){
       Bigram bi;
       bi = array[x].getBigram();
       bi.toUpper();
      array[x].setBigram(bi);
    }
}

void sortArrayBigramFreq(BigramFreq array[], int nElements){
    
    for(int x =0; x<nElements; x++){
        BigramFreq max = array[x];
        int pos = x;
        
        for(int j = x+1; j<nElements; j++){    
            
            if(max.getFrequency() == array[j].getFrequency()&&max.getBigram().toString() > array[j].getBigram().toString()){
               
                max = array[j];
                pos = j;
                
            }
                        
            if(array[j].getFrequency()>max.getFrequency()){
                max = array[j];
                pos = j;
            }
        }
        
        swapElementsArrayBigramFreq(array, nElements, pos, x);
        
    }

}