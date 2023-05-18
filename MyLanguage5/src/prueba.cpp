#include <iostream>
#include <string>

using namespace std;

int main(){
    
    const string hola = "abcdefghijklmopqrst";
    if(hola.find('v') == string::npos){
        cout << "vale";
    }
   

    return 0;
}