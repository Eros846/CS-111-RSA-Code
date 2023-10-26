/* Code by;
Sarik Karki 862380409
Joseph Thach 862351359
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;




vector<int> findDivisors(int publicKeyN ) {
    vector<int> divisors;
    for (int i = 1; i <= sqrt(publicKeyN); i++) {
        if(publicKeyN % i == 0){
            divisors.push_back(i);
            if(publicKeyN / i  != i) {
                    divisors.push_back(publicKeyN/i);
            }
        }
    
}
  return divisors;   

}

int extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int findDecryptedNumbers(int number, int d, int publicKeyM){
    int frontNumber  = 1;
    int squaredNumber;
    int cypherNum;

    while (d>1){
        squaredNumber = number*number;
        
        if(d%2 != 0 ){
            frontNumber = (frontNumber * number) % publicKeyM;
        }
        number = squaredNumber%publicKeyM;
        d = d/2; 
    }
    cypherNum = (frontNumber*number) % publicKeyM;
    return cypherNum;
}


void printDecryptedText( int decryptedStack[],  int sizeOfStack){
    for(int i = 0; i< sizeOfStack ; i++ ){
        //a blank is 31, quotation marks: 32, a coma: 33, a period: 34, an apostrophe: 35. Then he uses RSA to encode each number separately.
        if(decryptedStack[i] == 31){
            cout << " ";
        }
        else if(decryptedStack[i] == 32){
            cout << "\"";
        }
        else if(decryptedStack[i] == 33){
            cout << ",";
        }
        else if(decryptedStack[i] == 34){
            cout << ".";
        }
        else if(decryptedStack[i] == 35){
            cout << "\'";
        }
        else {
            cout << char(decryptedStack[i]+60);
        }
    }
}



int main() {

    // Intializing variables
    int e, n, m, p, q, d, totientFunction, cypherText , decryptedText;

    // Taking public key input from user
    cin >> e >> n;
    cin >> m;


    // Intializing stacks and vector
    int cStack[m], decryptedStack[m];
    vector<int> divisorsList;

    // Taking encrypted text from user and storing in a stack 
    for (int i = 0; i < m; i++) {
        cin >> cypherText;
        cStack[i] =  cypherText;
    } 
    divisorsList = findDivisors(n);
    
    // Checking if user entered a valid public key
     if (divisorsList.size() != 4 ) {
        cout << "Public key is not valid!";
        return 0;
     }

    // Decoding p and q from public key 
    p = divisorsList[2];
    q = divisorsList[3];

    if (p == 0 || q == 0) {
        cout << "Public key is not valid!";
        return 0;
    }
    else if (p == q) {
         cout << "Public key is not valid!";
        return 0;
    }

    // Calculating totientFunction
    int x, y;
    totientFunction = (p-1)*(q-1);
    if (extendedGCD(e, totientFunction, x ,y) != 1) { 
        cout << "Public key is not valid!";
        return 0;
    }

    // Decrypting text into it's cypher text form 
    x = 0, y =0;
    d = extendedGCD(e, totientFunction, x, y);
    d= x;
    if(d < 0){
        d= d + totientFunction;
    }
    if (d == 0){
        cout << "Public key is not valid!";
        return 0;
    
    }
    
    
    
    for (int i = 0; i< m; i++) {
        decryptedText = findDecryptedNumbers(cStack[i], d, n);
        decryptedStack[i] = decryptedText;
    }

    // Printing p, q and totient function and d 
    cout << p << " " << q << " " << totientFunction << " " << d <<endl;
    
    // Printing cypher text 
    for(int i = 0; i< m; i++ ) {
        cout << decryptedStack[i] << " ";
    }
    cout << endl;
    
    // Printing decrypted text
    printDecryptedText(decryptedStack, m);


    return 0;
}


/*
    Test Case 1. Input:
    23 55
    13
    43 15 51 13 17 43 36 30 14 10 11 23 30

    Output:
    5 11 40 7
    32 5 6 7 8 32 31 35 9 10 11 12 35
    "ABCD" ’EFGH’
*/

/*
    Test Case 2. Input:
    5 55
    13
    32 45 21 32 43 32 1 10 34 10 11 12 10

    Output:
    Public key is not valid!
*/

