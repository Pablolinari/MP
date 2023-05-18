/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <string>
#include <cstring>
#include <functional>
#include <ostream>
#include "Bigram.h"

using namespace std;
Bigram::Bigram(const std::string& text){
    if(text.size()==2){
        _text[0] = text.at(0);
        _text[1] = text.at(1);
        _text[2] = '\0';
        
        
        
    }
    else{
        _text[0] = '_';
        _text[1] = '_';
        _text[2] = '\0';
    }
}

Bigram::Bigram(char first, char second){
    
    _text[0] = first;
    _text[1] = second;
    _text[2]='\0';
}
Bigram::Bigram(const char text[]){
    if(strlen(text) == 2){
        _text[0] = text[0];
        _text[1] = text[1];
        _text[2] = '\0';
    }
    else{
        _text[0] = '_';
        _text[1] = '_';
        _text[2] = '\0';
    }
}

std::string Bigram::getText()const{
    return _text;
}

 std::string Bigram::toString() const{
     return _text;
 }
 
 const char& Bigram::at(int index) const{
     if(index==1 || index ==0){
         return _text[index];
     }
     else{
         throw std::out_of_range("const char& Bigram::at(int index) const // invalid index");
     }
     
 }
 
  char& Bigram::at(int index){
     if(index==1 || index ==0){
         return _text[index];
     }
     else{
         throw std::out_of_range("const char& Bigram::at(int index) const // invalid index");
     }
     
 }
 
 bool isValidCharacter(char character , const std::string &validCharacters){
     bool is_valid = false;
     for(int x=0; x< validCharacters.size()-1; x++){
         if(character == validCharacters.at(x)){
             is_valid = true;
         }
     }
     return is_valid;
     
     
 }
 
 void Bigram::toUpper(){
     _text[0]=toupper(_text[0]);
     _text[1]=toupper(_text[1]);
     
 }
 
 std::ostream operator<<(std::ostream & os , const Bigram & bigram){
     os << bigram.toString();
     return os;
 }
 std::istream operator>>(std::istream & is , Bigram & bigram){
     std::string text;
     is >> text;
     if(text.size() == 2){
         bigram.at(0) = text[0];
         bigram.at(1) = text[1];
     }
     else{
         bigram.at(0) = '_';
         bigram.at(1)='_';
     }
     return is; 
 }