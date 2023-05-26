#include <string>
#include "BigramFreq.h"
#include "Bigram.h"
BigramFreq::BigramFreq()
{
    _bigram = Bigram("__");
    _frequency = 0;
}

const Bigram &BigramFreq::getBigram() const
{
    return _bigram;
}

int BigramFreq::getFrequency() const
{
    return _frequency;
}

void BigramFreq::setBigram(const Bigram &bigram)
{
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency)
{
    if (frequency > 0)
    {
        _frequency = frequency;
    }
    else
    {
        throw std::out_of_range("in function 'setFrequency' frequency < 0");
    }
}

std::string BigramFreq::toString() const
{

    return _bigram.toString() + " " + std::to_string(_frequency);
}


std::ostream &operator<<(std::ostream &os, const BigramFreq & bigramFreq){
    os << bigramFreq.toString();
    return os;
}

std::istream &operator>>(std::istream &is, BigramFreq &bigramFreq){
    std::string bigram;
    int freq;
    is>>bigram; is >> freq;

    bigramFreq.setBigram(bigram); bigramFreq.setFrequency(freq);

    return is;
}

bool operator>(const BigramFreq &bigramFreq1, const  BigramFreq &bigramFreq2){
    bool mayor = false;
    if(bigramFreq1.getFrequency() < bigramFreq2.getFrequency()){
        mayor = true;
    }
    else if(bigramFreq1.getFrequency() == bigramFreq2.getFrequency()&& bigramFreq1.getBigram().toString()< bigramFreq2.getBigram().toString()){
        mayor = true;
    }
    return mayor;
}

bool operator<(const BigramFreq &bigramFreq1, const  BigramFreq &bigramFreq2){
    bool mayor = false;
    if(bigramFreq1.getFrequency() > bigramFreq2.getFrequency()){
        mayor = true;
    }
    else if(bigramFreq1.getFrequency() == bigramFreq2.getFrequency()&& bigramFreq1.getBigram().toString()> bigramFreq2.getBigram().toString()){
        mayor = true;
    }
    return mayor;
}

bool operator==(const BigramFreq &bigramFreq1, const  BigramFreq &bigramFreq2){
    bool equal = false;
    if(bigramFreq1.toString() == bigramFreq2.toString()){
        equal = true;
    }
    return equal;
}

bool operator!=(const BigramFreq &bigramFreq1, const  BigramFreq &bigramFreq2){
    bool equal = false;
    if(bigramFreq1.toString() != bigramFreq2.toString()){
        equal = true;
    }
    return equal;
}

bool operator<=(const BigramFreq&bigramFreq1, const BigramFreq &bigramFreq2){
    bool eval = false;
    if(bigramFreq1 == bigramFreq2 || bigramFreq1 < bigramFreq2){
        eval = true;
    }
    return eval;
}
bool operator>=(const BigramFreq&bigramFreq1, const BigramFreq &bigramFreq2){
    bool eval = false;
    if(bigramFreq1 == bigramFreq2 || bigramFreq1 > bigramFreq2){
        eval = true;
    }
    return eval;
}
