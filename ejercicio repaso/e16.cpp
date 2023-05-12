#include<iostream>

using namespace std;

int compararCadenas(char *cad1, char* cad2){
    int p = 0;
    while(*(cad1+p) !='\0' || *(cad2 + p) != '\0'){
        p++;
    }
    if(*(cad1+p)!='\0'){
        return 1;
    }
    else if(*(cad2+p)!='\0'){
        return -1;
    }
}

int main(){

    char a[7] = "holaci";
    char b[3] = "ho";
    cout << compararCadenas(a,b);

    return 0;
}