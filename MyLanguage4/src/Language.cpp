#include <fstream>
#include "Language.h"
#include"BigramFreq.h"
#include<cmath>

const std::string Language::MAGIC_STRING_T = "MP-LANGUAGE-T-1.0";

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
        _size = numberBigrams;
        _vectorBigramFreq = new BigramFreq[_size];
        for (int x = 0; x < _size; x++) {
            _vectorBigramFreq[x] = BigramFreq();
        }

    }

}

Language::Language(const Language& orig) {
    _size = orig.getSize();
    _languageId = orig.getLanguageId();
    _vectorBigramFreq = new BigramFreq[_size];
    for (int x = 0; x < _size; x++) {
        _vectorBigramFreq[x] = orig.at(x);
    }
}

Language::~Language() {
    delete[] _vectorBigramFreq;
    _vectorBigramFreq = nullptr;
    _size = 0;
    _languageId = "unknown";
}

Language& Language::operator=(const Language& orig) {
    _size = orig.getSize();
    _languageId = orig.getLanguageId();
    _vectorBigramFreq = new BigramFreq[_size];
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

void Language::save(const char fileName[]) const {
    std::ofstream outputStream;

    outputStream.open(fileName);

    if (outputStream) {
        outputStream << MAGIC_STRING_T << std::endl;
        outputStream << toString();

        if (!outputStream) {
            throw std::ios_base::failure("the file is closed ");
        }

        outputStream.close();
    } else {
        throw std::ios_base::failure("the file is closed ");
    }
}

void Language::load(const char fileName[]) {
    std::ifstream inputStream;
    std::string magicCad;
    int frequency;
    std::string bigram;
    inputStream.open(fileName);
    if (inputStream) {
        inputStream >>magicCad;
        inputStream >>_languageId;
        inputStream >> _size;
        if (magicCad != MAGIC_STRING_T) {
            throw std::invalid_argument("in function load Magic strings are not the same  ");
        }
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
        if (!inputStream) {
            throw std::ios_base::failure("the file is closed ");
        }

        inputStream.close();
    } else {
        throw std::out_of_range("the file is closed ");
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

void Language::join(const Language &language) {

    for (int j = 0; j < language.getSize(); j++) {
        append(language.at(j));
    }

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

void Language::allocate(int n) {
    _vectorBigramFreq = new BigramFreq[n];
    _size = n;

}

void Language::dellocate() {
    delete [] _vectorBigramFreq;
    _vectorBigramFreq = nullptr;
    _size = 0;

}

void Language::reallocate(int n ) {
    BigramFreq *aux;
    aux = new BigramFreq[n];
    for (int x = 0; x < _size; x++) {
        aux[x] = _vectorBigramFreq[x];
    }
    delete [] _vectorBigramFreq;
    _vectorBigramFreq = aux;
    _size = n;
}

