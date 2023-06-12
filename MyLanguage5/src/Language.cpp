#include <fstream>
#include "Language.h"
#include"BigramFreq.h"
#include<cmath>

const std::string Language::MAGIC_STRING_T = "MP-LANGUAGE-T-1.0";
const std::string Language::MAGIC_STRING_B = "MP-LANGUAGE-B-1.0";

Language::Language() {
    _languageId = "unknown";
    _size = 0;
    _vectorBigramFreq = nullptr;
}

Language::Language(int numberBigrams) {
    _languageId = "unknown";

    if (numberBigrams < 0) {
        throw std::out_of_range("incorrect number of bigrams at constructor Language(in numberBigrams)");

    } else {
        alocate(numberBigrams);
        for (int x = 0; x < _size; x++) {
            _vectorBigramFreq[x] = BigramFreq();
        }

    }

}

Language::Language(const Language& orig) {
    alocate(orig.getSize());
    _languageId = orig.getLanguageId();
    for (int x = 0; x < _size; x++) {
        _vectorBigramFreq[x] = orig.at(x);
    }
}

Language::~Language() {
    delocate();
    _languageId = "unknown";
}

Language& Language::operator=(const Language& orig) {
    delocate();
    _size = orig.getSize();
    _languageId = orig.getLanguageId();
    alocate(_size);
    for (int x = 0; x < _size; x++) {
        _vectorBigramFreq[x] = orig.at(x);
    }
    return *this;
}

const std::string& Language::getLanguageId() const {
    return _languageId;
}

void Language::setLanguageId(const std::string& id) {
    _languageId = id;
}

const BigramFreq &Language::at(int index)const {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("index out of range in function at(int index) class: Languge");

    } else {
        return _vectorBigramFreq[index];
    }

}

BigramFreq & Language::at(int index) {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("index out of range in function at(int index) class: Languge");

    } else {
        return _vectorBigramFreq[index];
    }

}

int Language::getSize() const {
    return _size;
}

double Language::getDistance(const Language& otherLanguage)const {
    int sum = 0;
    int pos;
    for (int x = 0; x < _size; x++) {
        pos = otherLanguage.findBigram(_vectorBigramFreq[x].getBigram());
        if (pos < 0) {
            sum = sum + abs(x - _size);
        } else {
            sum = sum + abs(x - pos);
        }
    }
    double distance;
    distance = sum / (std::pow(_size, 2));
    return distance;
}

int Language::findBigram(const Bigram &bigram) const {
    int pos = -1;
    for (int x = 0; x < _size; x++) {
        if (_vectorBigramFreq[x].getBigram().getText() == bigram. getText()) {
            pos = x;
        }
    }
    return pos;
}

std::string Language::toString() const {
    std::string text;
    text = _languageId + "\n" + std::to_string(_size) + "\n";
    for (int x = 0; x < _size; x++) {
        text += _vectorBigramFreq[x].toString() + "\n";
    }
    return text;
}

void Language::sort() {

    for (int x = 0; x < _size; x++) {
        BigramFreq max = _vectorBigramFreq[x];
        int pos = x;

        for (int j = x + 1; j < _size; j++) {

            if (max.getFrequency() == _vectorBigramFreq[j].getFrequency() &&
                    max.getBigram().toString() > _vectorBigramFreq[j].getBigram().toString()) {

                max = _vectorBigramFreq[j];
                pos = j;

            }

            if (_vectorBigramFreq[j].getFrequency() > max.getFrequency()) {
                max = _vectorBigramFreq[j];
                pos = j;
            }
        }

        BigramFreq swap;
        swap = _vectorBigramFreq[x];
        _vectorBigramFreq[x] = max;
        _vectorBigramFreq[pos] = swap;

    }
}

void Language::save(const char fileName[], char mode) const {
    std::ofstream outputStream;
    if (mode == 't') {
        outputStream.open(fileName, std::ios_base::binary);

        if (outputStream) {
            
            outputStream << MAGIC_STRING_T << std::endl;
            outputStream << toString();
            outputStream.close();
        }
        else {
            throw std::ios_base::failure("the file is closed in save text");
        }
    } else if (mode == 'b') {

        outputStream.open(fileName, std::ios_base::binary);
        if (outputStream) {
            outputStream << MAGIC_STRING_B << std::endl;
            outputStream << _languageId << std::endl;
            outputStream << _size << std::endl;
            for (int i = 0; i < _size; i++) {
                _vectorBigramFreq[i].serialize(outputStream);
            }
            if (!outputStream) {
                throw std::ios_base::failure("the file is closed  in save binari");
            }
            outputStream.close();
        } 
        else {
            throw std::ios_base::failure("the file is closed in save ");
        }


    }
}

void Language::load(const char fileName[]) {
    delocate();
    std::ifstream inputStream;
    std::string magicCad;
    int frequency;
    std::string bigram;
    inputStream.open(fileName, std::ios_base::binary);
    inputStream >>magicCad;
    if (inputStream && magicCad == MAGIC_STRING_T) {
        inputStream >>_languageId;
        inputStream >> _size;

        if (_size < 0) {
            throw std::out_of_range("not valid size ");
        }
        _vectorBigramFreq = new BigramFreq[_size];
        for (int x = 0; x < _size; x++) {
            inputStream>>bigram;
            inputStream>>frequency;
            _vectorBigramFreq[x].setBigram(bigram);
            _vectorBigramFreq[x].setFrequency(frequency);
        }
        inputStream.close();
    }
    else if (magicCad == MAGIC_STRING_B && inputStream) {

        inputStream >>_languageId;
        inputStream >> _size;
        inputStream.get();
        alocate(_size);
        for (int i = 0; i < _size; i++) {
            _vectorBigramFreq[i].deserialize(inputStream);
        }
        inputStream.close();
    } 
    else {
        throw std::out_of_range("the file is closed in load");
    }
}

void Language::append(const BigramFreq &bigramFreq) {
    int bigram_pos = findBigram(bigramFreq.getBigram());
    if (bigram_pos >= 0) {
        int new_frequency = bigramFreq.getFrequency() + _vectorBigramFreq[bigram_pos].getFrequency();
        _vectorBigramFreq[bigram_pos].setFrequency(new_frequency);
    } else if (bigram_pos == -1) {
        BigramFreq *aux;
        aux = new BigramFreq[_size + 1];
        for (int x = 0; x < _size; x++) {
            aux[x] = _vectorBigramFreq[x];
        }
        delete [] _vectorBigramFreq;

        aux[_size] = bigramFreq;
        _vectorBigramFreq = aux;
        _size++;
    } else {
        throw std::out_of_range("There is no space for more bigrams . at function append ");
    }

}

BigramFreq Language::operator[](int index) const {
    return at(index);
}

BigramFreq & Language::operator[](int index) {
    return at(index);
}

Language & Language::operator+=(const Language & language) {
    for (int i = 0; i < language.getSize(); i++) {
        append(language[i]);
    }
    return *this;
}

void Language::alocate(int n) {
    if (n>0){
    _vectorBigramFreq = new BigramFreq [n];
    _size = n;
    }
    else if (n==0){
        _vectorBigramFreq = nullptr;
        _size =0;
    }
}

void Language::delocate() {
    delete [] _vectorBigramFreq;
    _vectorBigramFreq = nullptr;
    _size = 0;
}

std::istream &operator>>(std::istream& is, Language &language) {
    std::string magicstring, languageid, bigram;
    int size , freq ,cont = 0;
    is >> languageid;
    is >> size;
    language.setLanguageId(languageid);
    while (is && (cont < size)) {
        is >> bigram;
        is >> freq;
        BigramFreq bigramFreq;
        bigramFreq.setBigram(Bigram(bigram));
        bigramFreq.setFrequency(freq);
        language.append(bigramFreq);
        cont ++;
    }
    
    return is;
}

std::ostream &operator<<(std::ostream &os, const Language& language){
    os << language.toString();
    return os;
}


