/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */
#include <iostream>
#include <string>
#include <cstring>
#include "BigramFreq.h"
#include "Language.h"
#include "BigramCounter.h"

using namespace std;


/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {
 int files = argc-2,txt= 1 ,firstbgr=2; //numero de idiomas languages a comparar , posicion del primer lanaguage
    
    //compruebo que todos los parametros de la función sean correctos , 
    //en caso de que falte alguno termina la ejecución del programa.
    
    if(argc < 3){
        showEnglishHelp(std::cout);
        return 1;
    }
    
    if(files <1){
        showEnglishHelp(std::cerr);
        return 1;
    }

    Language *array_language;
    array_language = new Language [files];
    BigramCounter matrix;
    matrix.calculateFrequencies(argv[txt]);
    Language language_aux(matrix.toLanguage());
    language_aux.sort();
    int aux=0;
    for (int x  = firstbgr ; x<argc; x++){
        
        array_language[aux].load(argv[x]);
        array_language[aux].sort();
        aux++;
    }

    int pos = 0;
    double min = language_aux.getDistance(array_language[0]);
    
    for(int j = 0; j<files ; j++){
       
        if(language_aux.getDistance(array_language[j]) < min){
            min = language_aux.getDistance(array_language[j]);
            pos = j;
        }
    }
    

    language_aux.setLanguageId(array_language[pos].getLanguageId());
    std::cout << "Final decision: language "<<language_aux.getLanguageId() <<" with a distance of "<< min<<std::endl;
    
    

    delete [] array_language;
    
}

