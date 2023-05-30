/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
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
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an output file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char* argv[]) {
    char mode = 't';
    string outputfile ;
    int nfiles , outfile =0, sum = 1;
    
    if(argc == 1){
        showEnglishHelp(cout);
        return 1;
    }
    nfiles = argc -sum;
    for (int i = 1; i<argc && argv[i][0] == '-'; i++){
        nfiles = 0;
        if(strcmp(argv[i] ,"-b") == 0){
            mode = 'b';
            sum += 1;
            nfiles = argc - sum ;
        }
        else if(strcmp(argv[i],"-t") == 0){
            
            mode = 't';
            sum+=1;
            nfiles = argc - sum ;
        }
        else if(strcmp(argv[i],"-o") == 0){
            if(argc > i+1){
                outputfile = argv[i+1];
                i++;
                outfile = i;
                sum+=2;
                nfiles = argc - sum ;
            }
            else{
                showEnglishHelp(cout);
                return 1;
            }
        }
        else if(strcmp(argv[i],"-o") == 1){
            showEnglishHelp(cout);
            return 1;
        }
        else{
            showEnglishHelp(cout);
            return 1;
        }
    }

    if(nfiles < 1){
        showEnglishHelp(cout);
        return 1;
    }

    Language total , aux;

    for(int i = argc -nfiles; i< argc; i++){
        aux.load(argv[i]);
        total+=aux;
    }

    total.save(argv[outfile]);
    
    return 0;
}

