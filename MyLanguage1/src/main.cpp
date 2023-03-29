/*
 * Metodolog�a de la Programaci�n: Language1
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andr�s Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 7 de febrero de 2023, 14:02
 */


/**
 * This program reads from the stardard input, an integer n (number of elements) 
 * and a list of n pairs bigram-frequency. The pairs are stored in an array, 
 * and then it is sorted in decreasing order of frequency. After that, 
 * all the bigrams are changed to uppercase. The sorted array is finally shown 
 * in the stardard output. 
 * Running example:
 * > language1 < data/miniquijotebigrams.txt 
 */
#include <iostream>
#include <ArrayBigramFreqFunctions.h>
int main(int argc, char* argv[]) {
   const  int DIM = 1000;
    
    BigramFreq array[DIM];
    int nElements;
    
    readArrayBigramFreq(array,DIM, nElements);
    sortArrayBigramFreq(array,nElements);
    toUpperArrayBigramFreq(array,nElements);
    printArrayBigramFreq(array,nElements);
    

    return 0;
}

