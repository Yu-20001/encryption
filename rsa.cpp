#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<math.h>
#include<cctype>
#include<algorithm>
#include<iomanip>
using namespace std;


int gcd(int a, int b){
    int n = 1;
    int tmp,ans;
    if( a < b ){
        tmp = a;
    }
    else{
        tmp = b;
    }
    for(int i = tmp ; i > 0 ; i--){
        if(a % i == 0 & b % i == 0){
            ans = i;
            break;
        }
    }
    return ans;
}

vector<double>gen_key(){
    /*
    srand(time(NULL));
    vector<int>prime={2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int p_index = rand() % 10;
    int p = prime[p_index];
    cout<<p<<endl;
    prime.erase(prime.begin()+p_index);
    int q_index = rand() % 9;
    int q = prime[q_index];
    cout<<q<<endl;
    */
    double p = 2;
    double q = 13;
    
    double N = p*q;
    double phi = (p-1)*(q-1);
    double e, d;
    double count = 2;
    // e rule:
    // 1. less than phi
    // 2. coprime with phi and N
    while(gcd(count, phi) != 1 || gcd(count, N) != 1){
        count++;
    }
    e = count;
    // we try to find d
    // d rule:
    // (e*d) mod(phi) == 1;
    double d1=1/e;
    d=fmod(d1,phi);
    /*
    vector<double>d_possible;
    for(int i = 1; i < 100; i++){
        if( abs( fmod( (i*e) , phi) - 1 ) < 0.1){
            d_possible.push_back(i);
        }
    }
    if(d_possible.size() == 1 ){
        d = d_possible.at(0);
    }
    else{
        d = d_possible.at(1);
    }
    */
    //double d1 = 1/e;
    //d = fmod(d1, phi);
    //d = d_possible.at(d_possible.size()-1);
    vector<double> key;
    key.push_back(p);
    key.push_back(q);
    key.push_back(e);
    key.push_back(d);
    key.push_back(phi);
    key.push_back(N);
    return key;
}
vector<double>encrypting(string str, vector<double> key){
    vector<double> encrypted;
    for(int i = 0 ; i < str.size(); i++){
        encrypted.push_back(int(str[i])-64);
    }
    for(int i = 0 ; i < encrypted.size(); i++){
        encrypted[i] = fmod(pow(encrypted[i], key[2]), key[5]);
    }
    return encrypted;
}
vector<double>decrypting(vector<double>en, vector<double> key){
    vector<double> decrypted;
    for(int i = 0 ; i < en.size(); i++){
        
        decrypted.push_back(fmod(pow(en.at(i), key[3]), key[5]));
    }
    return decrypted;
}

int main(){
    vector<double> key = gen_key();
    vector<double> public_key, private_key;
    public_key.push_back(key.at(2));
    public_key.push_back(key.at(5));
    private_key.push_back(key.at(3));
    private_key.push_back(key.at(5));
    //show keys
    printf("public key: (%f,%f)\n",public_key.at(0),public_key.at(1));
    printf("private key: (%f,%f)\n",private_key.at(0),private_key.at(1));
    
    string input = "ABC";
    string output="";
    //transform(input.begin(), input.end(), input.begin(), ::toupper);
    vector<double>encrypted = encrypting(input, key);
    vector<double> decrypted = decrypting(encrypted, key);
    //transform(output.begin(), output.end(), output.begin(), ::tolower);
    cout<<"original message: "<<endl;
    for(int i = 0 ; i < input.size(); i++){
        cout<<input[i];
    }
    cout<<endl;
    cout<<"encrypted message: "<<endl;
    for(int i = 0 ; i < encrypted.size(); i++){
        cout << encrypted[i]<<" ";
    }
    cout<<endl;
    cout<<"decrypted message: "<<endl;
    for(int i = 0 ; i < decrypted.size(); i++){
        cout <<setprecision(30)<<decrypted[i] <<" "; 
    }
}
