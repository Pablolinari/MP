/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */
#include <iostream>
#include <string>
#include <cstring>
#include "BigramFreq.h"
#include "Language.h"
#include "BigramCounter.h"
/** 
 * @file LEARN.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */
using namespace std;
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << endl;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char *argv[]) {  
    char mode = 't';
    string languageId = "unknown";
    string outputfile = "output.bgr";
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
        else if (strcmp(argv[i],"-l") == 0){
            if(argc > i+1){
                languageId = argv[i+1];
                i++;
                sum+=2;
                nfiles = argc - sum ;
            }
            else{
                showEnglishHelp(cout);
                return 1;
            }
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
        else{
            showEnglishHelp(cout);
            return 1;
        }
    }

    if(nfiles < 1){
        showEnglishHelp(cout);
        return 1;
    }
            
   ///////////////////////////////////////////////////////////////////////////////////////////////

    Bigram bigram;
    BigramFreq bigramfreq;
    BigramCounter matrix , matrixb; 
    Language language;
    language.setLanguageId(languageId);
    for(int i = argc-nfiles ; i<argc; i++){
        matrixb.calculateFrequencies(argv[i]);
        matrix+=matrixb;
    }
    language = matrix.toLanguage();
    language.sort();
    
    if(outfile > 0){
        language.save(argv[outfile] ,mode);
    }
    else{
      
        language.save(outputfile.c_str(),mode);
   }
    
        
    return 0;
}

