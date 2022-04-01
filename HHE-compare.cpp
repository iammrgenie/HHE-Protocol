#include "seal/seal.h"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "examples.h"

using namespace std;
using namespace seal;

struct Experim {
    Ciphertext c_i;
    Plaintext x_p;
};

int main() {
    int cnt = 200;
    Experim Test[cnt];

    chrono::high_resolution_clock::time_point time_start, time_end;
    chrono::milliseconds time_diff;
    
    EncryptionParameters parms(scheme_type::bfv);

    size_t poly_modulus_degree = 16384;
    parms.set_poly_modulus_degree(poly_modulus_degree);

    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(65537);

    SEALContext context(parms);

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);

    Decryptor decryptor(context, secret_key);

   
    uint64_t x = 0x01c4f;
    Plaintext x_plain(uint64_to_hex_string(x));
    cout << "Express x = " + to_string(x) + " as a plaintext polynomial 0x" + x_plain.to_string() + "." << endl;

    time_start = chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; i++){
        //Ciphertext x_encrypted;
        //cout << "Encrypt x_plain to x_encrypted." << endl;
        encryptor.encrypt(x_plain, Test[i].c_i);
    }
    time_end = chrono::high_resolution_clock::now();
    time_diff = chrono::duration_cast<chrono::milliseconds>(time_end - time_start);
    cout << "Time taken for HE encryption for " << cnt << " values = " << time_diff.count() << " milliseconds" << endl;
    

    //cout << "    + size of freshly encrypted x: " << x_encrypted.size() << endl;

    //cout << "    + noise budget in freshly encrypted x: " << decryptor.invariant_noise_budget(x_encrypted) << " bits" << endl;
    
    Plaintext x_decrypted;
    cout << "Decryption of x_encrypted: ";
    time_start = chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; i++) {
        decryptor.decrypt(Test[i].c_i, Test[i].x_p);
    }

    cout << "0x" << x_decrypted.to_string() << " ...... Correct." << endl;
    time_end = chrono::high_resolution_clock::now();
    time_diff = chrono::duration_cast<chrono::milliseconds>(time_end - time_start);
    cout << "Time taken for HE decryption for " << cnt << " values = " << time_diff.count() << " milliseconds" << endl;

    
    return 0;
}