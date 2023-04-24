/*
 * Metodología de la Programación: Language3
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 7 de febrero de 2023, 14:02
 */
#include<iostream>
#include <fstream>
#include<ostream>
#include <string>
#include<cstring>
#include"Language.h"


/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(std::ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << std::endl;
    outputStream << "language3 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << std::endl;
}

int MinMaxDistance(int size , Language array[], char operation , const Language & aux){
    int pos ;
    int minmax = aux.getDistance(array[0]);
     
     for(int x = 0; x< size ; x++ ){
        if(operation == 'n'){
            if(aux.getDistance(array[x]) < minmax){
                pos = x;
                minmax = aux.getDistance(array[x]); 
            }
        }
        else{
            if(aux.getDistance(array[x]) > minmax){
                pos = x;
                minmax = aux.getDistance(array[x]);
            }
        }
        
    }
    
    return pos;
}

/**
 * This program reads an undefined number of Language objects from the set of 
 * files passed as parameters to main(). All the Languages object, except the 
 * first one, must be stored in a dynamic array of Language objects. Then, 
 * for each Language in the dynamic array, this program prints to the 
 * standard output the name of the file of that Language and the distance from 
 * the first Language to the current Language. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Language with the minimum|maximum dipijistance to the Language 
 * of the first file and its language identifier.
 * 
 * At least, two Language files are required to run this program.
 * Running example:
 * > language3 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>] 
 */
int main(int argc, char* argv[]) {
    int ncompare,first; //numero de idiomas languages a comparar , posicion del primer lanaguage
    char operation ='n';
    std::string phrase1, phrase2 ;
    
    //compruebo que todos los parametros de la función sean correctos , 
    //en caso de que falte alguno termina la ejecución del programa.
    
    if(argc < 3){
        showEnglishHelp(std::cout);
        return 1;
    }
    if(argv[1][0] == '-'){
        if(strcmp(argv[1],"-t") == 0){
            
            if(strcmp(argv[2],"min") ){
                operation = 'n';
               
            }
            else if (strcmp(argv[2],"max") == 0){
                operation = 'x';

            }
            else{
                showEnglishHelp(std::cout);
                return 1;
            }
        }
        else{
            showEnglishHelp(std::cout);
            return 1;
        }
        ncompare = argc -4;
        first = 4;
    }
    else{
       ncompare = argc -2;
       first = 2;
    }
    if(ncompare <=1){
        showEnglishHelp(std::cerr);
        return 1;
    }

    Language *array_language;
    array_language = new Language [ncompare];

    Language language_aux;
    language_aux.load(argv[first-1]);
    
    for (int x  = 0 ; x<ncompare; x++){
        array_language[x].load(argv[x+first-1]);
        array_language[x].sort();
                std::cout << "Distance to " <<argv[x+first]<<": " << language_aux.getDistance(array_language[x])<<std::endl;
    }


    int maxmin = MinMaxDistance(ncompare,array_language,operation,language_aux);
   
    if(operation == 'n'){
        std::cout << "Nearest language file: "<< argv[maxmin + first-1]<<std::endl;
        std::cout <<"Identifier of the nearest language: "  << array_language[maxmin].getLanguageId() << std::endl;

    }
    if(operation == 'x'){
        std::cout << "Farthest language file: "<< argv[maxmin + first-1]<<std::endl;
        std::cout <<"Identifier of the farthest language: " << array_language[maxmin].getLanguageId() << std::endl;
    }
    delete [] array_language;
          
    return 0;
}
