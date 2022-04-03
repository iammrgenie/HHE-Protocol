#include <vector>
#include <iostream>
#include <string>

#include "HHE/ciphers/common_Zp/SEAL_Cipher.h"
#include "HHE/ciphers/common/utils.h"
//#include "HHE/ciphers/pasta_3/plain/pasta_3_plain.h"  // for PASTA_params

#include "HHE/ciphers/pasta_3/seal/pasta_3_seal.h"
#include "HHE/ciphers/pasta_3/plain/pasta_3_plain.h"

#include <openssl/bn.h> // 
#include <openssl/asn1.h>
#include <openssl/pem.h> // for reading certificates & keys
#include <openssl/bio.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>

static const bool USE_BATCH = true;

using namespace std;

struct Experim {
  vector<uint64_t> x_i;
  vector<uint64_t> c_i;
  vector<seal::Ciphertext> c_1;
  vector<seal::Ciphertext> c_2;
  vector<uint64_t> x_p;
};

//Generate RSA public and private key pair and store of disk
bool generate_key(string user)
{
  cout << "Generating Private and Public Keypair for " << user << "\n";
	int	ret = 0;
	RSA	*r = NULL;
	BIGNUM *bne = NULL;
	BIO	*bp_public = NULL, *bp_private = NULL;

	int	bits = 2048;
	unsigned long	e = RSA_F4;
  
  char *pub;
  char *priv;

  string pub1 = user+"_public.pem";
  string priv1 = user+"_private.pem";

  pub = &pub1[0];
  priv = &priv1[0];

	bne = BN_new();
	ret = BN_set_word(bne,e);
	if(ret != 1){
		goto free_all;
	}

	r = RSA_new();
	ret = RSA_generate_key_ex(r, bits, bne, NULL);
	if(ret != 1){
		goto free_all;
	}

	bp_public = BIO_new_file(pub, "w+");
	ret = PEM_write_bio_RSAPublicKey(bp_public, r);
	if(ret != 1){
		goto free_all;
	}

	bp_private = BIO_new_file(priv, "w+");
	ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

free_all:

	BIO_free_all(bp_public);
	BIO_free_all(bp_private);
	RSA_free(r);
	BN_free(bne);

	return (ret == 1);
}

//retrieve user private key
RSA* retrievePrivateRSA(string user) {
  RSA *rsa = NULL;

  char *priv;
  string priv1 = user+"_private.pem";
  priv = &priv1[0];

  BIO * keybio = BIO_new_file(priv, "r");
  if (keybio==NULL) {
      return 0;
  }
  rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
  return rsa;
}

//retrieve user public key
RSA* retrievePublicRSA(string user) {
  RSA *rsa = NULL;
  
  char *pub;
  string pub1 = user+"_public.pem";
  pub = &pub1[0];
  
  BIO * keybio = BIO_new_file(pub, "rt");
  if (keybio==NULL) {
      return 0;
  }

  //cout << "1a\n";
  rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);
  BIO * keyb = BIO_new(BIO_s_mem());

  RSA_print(keyb, rsa, 0);

  return rsa;
}


//Sign Message using RSA secret key
bool RSASign(RSA* rsa, const unsigned char* Msg, size_t MsgLen, unsigned char** EncMsg, size_t* MsgLenEnc) {
  EVP_MD_CTX* m_RSASignCtx = EVP_MD_CTX_create();
  EVP_PKEY* priKey  = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(priKey, rsa);
  
  if (EVP_DigestSignInit(m_RSASignCtx, NULL, EVP_sha256(), NULL, priKey) <= 0) {
      return false;
  }
  
  if (EVP_DigestSignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0) {
      return false;
  }
  
  if (EVP_DigestSignFinal(m_RSASignCtx, NULL, MsgLenEnc) <=0) {
      return false;
  }
  
  *EncMsg = (unsigned char*)malloc(*MsgLenEnc);
  
  if (EVP_DigestSignFinal(m_RSASignCtx, *EncMsg, MsgLenEnc) <= 0) {
      return false;
  }
  
  EVP_MD_CTX_free(m_RSASignCtx);
  return true;
}

bool RSAVerifySignature( RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen, const char* Msg, size_t MsgLen, bool* Authentic) {
  *Authentic = false;
  
  EVP_PKEY* pubKey  = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(pubKey, rsa);
  EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

  if (EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_sha256(), NULL, pubKey) <= 0) {
    return false;
  }

  if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
    return false;
  }

  cout << "Size of Hash = " << MsgHashLen << "\n";
  int AuthStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen);
  
  if (AuthStatus == 1) {
    *Authentic = true;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return true;
  } else if (AuthStatus == 0) {
    *Authentic = false;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return true;
  } else{
    *Authentic = false;
    EVP_MD_CTX_free(m_RSAVerifyCtx);
    return false;
  }
}

void Base64Encode( const unsigned char* buffer, size_t length, char** base64Text) {
  BIO *bio, *b64;
  BUF_MEM *bufferPtr;

  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);

  BIO_write(bio, buffer, length);
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bufferPtr);
  BIO_set_close(bio, BIO_NOCLOSE);
  BIO_free_all(bio);

  *base64Text=(*bufferPtr).data;
}

size_t calcDecodeLength(const char* b64input) {
  size_t len = strlen(b64input), padding = 0;

  if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
    padding = 2;
  else if (b64input[len-1] == '=') //last char is =
    padding = 1;
  return (len*3)/4 - padding;
}

void Base64Decode(const char* b64message, unsigned char** buffer, size_t* length) {
  BIO *bio, *b64;

  int decodeLen = calcDecodeLength(b64message);
  *buffer = (unsigned char*)malloc(decodeLen + 1);
  (*buffer)[decodeLen] = '\0';

  bio = BIO_new_mem_buf(b64message, -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  *length = BIO_read(bio, *buffer, strlen(b64message));
  BIO_free_all(bio);
}


char* signMessage(string user, string msg) {
  //retrieve user private RSA key from file
  cout << "Message Signing Process .... User: " << user << "\n";
  
  RSA* privateRSA = retrievePrivateRSA(user);

  unsigned char* encMessage;
  char* base64Text;
  size_t encMessageLength;
  
  //sign message and store in encMessage
  RSASign(privateRSA, (unsigned char*)msg.c_str(), msg.length(), &encMessage, &encMessageLength);
  
  //encode to base64 for printing
  Base64Encode(encMessage, encMessageLength, &base64Text);
  
  free(encMessage);
  return base64Text;
}


unsigned char * encryptMessage(string user, string msg, int inlen) {
  cout << "Encryption Process .... \n";

  RSA* pubRSA = retrievePublicRSA(user);

  unsigned char *ciphertext;
  ciphertext = (unsigned char*)malloc(256);

  inlen = RSA_public_encrypt(msg.length(), (unsigned char *)msg.c_str(), ciphertext, pubRSA, RSA_PKCS1_PADDING);

  RSA_free(pubRSA);
  return ciphertext;
}

unsigned char * decryptMessage(string user, unsigned char * ciphertext, int inlen, int outlen) {
  cout << "Decryption Process .... \n";

  RSA* privRSA = retrievePrivateRSA(user);

  unsigned char *plaintext;
  plaintext = (unsigned char*)malloc(256);

  outlen = RSA_private_decrypt(inlen, ciphertext, plaintext, privRSA, RSA_PKCS1_PADDING);

  RSA_free(privRSA);
  return plaintext;
}


bool verifySignature(string user, string msg, char* signatureBase64) {
  //retrieve user public RSA key from file
  cout << "Message Verification Process .... User: " << user << "\n";
  
  RSA* publicRSA = retrievePublicRSA(user);
  
  unsigned char* encMessage;
  size_t encMessageLength;
  bool authentic;
  
  Base64Decode(signatureBase64, &encMessage, &encMessageLength);

  bool result = RSAVerifySignature(publicRSA, encMessage, encMessageLength, msg.c_str(), msg.length(), &authentic);
  return result & authentic;
}


int main(){
  chrono::high_resolution_clock::time_point time_start, time_end, user_start, user_end, extra1, extra2, eval1, eval2;
  chrono::milliseconds time_diff, user_diff, extra_diff, eval_diff;
  chrono::nanoseconds time_1, user_1, extra_1;

  int cnt = 1;
  int inlen, outlen;
  RSA *rpub, *rpriv;
  Experim Test[cnt];

  string user1 = "User";
  string user2 = "CSP";
  string user3 = "Analyst";

  string m1 = "25122022";
  string m2 = "03042022";
  string m3 = "SQUARED";
  string m4 = "17061992";

  unsigned char c1[256];
  unsigned char c2[256];
  unsigned char p1[256];
  unsigned char p2[256];

  generate_key(user2);
  generate_key(user1);
  generate_key(user3);

	vector<uint64_t> in_key = {0x07a30, 0x0cfe2, 0x03bbb, 0x06ab7, 0x0de0b, 0x0c36c, 0x01c39, 0x019e0,
                                    0x0e09c, 0x04441, 0x0c560, 0x00fd4, 0x0c611, 0x0a3fd, 0x0d408, 0x01b17,
                                    0x0fa02, 0x054ea, 0x0afeb, 0x0193b, 0x0b6fa, 0x09e80, 0x0e253, 0x03f49,
                                    0x0c8a5, 0x0c6a4, 0x0badf, 0x0bcfc, 0x0ecbd, 0x06ccd, 0x04f10, 0x0f1d6,
                                    0x07da9, 0x079bd, 0x08e84, 0x0b774, 0x07435, 0x09206, 0x086d4, 0x070d4,
                                    0x04383, 0x05d65, 0x0b015, 0x058fe, 0x0f0d1, 0x0c700, 0x0dc40, 0x02cea,
                                    0x096db, 0x06c84, 0x008ef, 0x02abc, 0x03fdf, 0x0ddaf, 0x028c7, 0x0ded4,
                                    0x0bb88, 0x020cd, 0x075c3, 0x0caf7, 0x0a8ff, 0x0eadd, 0x01c02, 0x083b1,
                                    0x0a439, 0x0e2db, 0x09baa, 0x02c09, 0x0b5ba, 0x0c7f5, 0x0161c, 0x0e94d,
                                    0x0bf6f, 0x070f1, 0x0f574, 0x0784b, 0x08cdb, 0x08529, 0x027c9, 0x010bc,
                                    0x079ca, 0x01ff1, 0x0219a, 0x00130, 0x0ff77, 0x012fb, 0x03ca6, 0x0d27d,
                                    0x05747, 0x0fa91, 0x00766, 0x04f27, 0x00254, 0x06e8d, 0x0e071, 0x0804e,
                                    0x08b0e, 0x08e59, 0x04cd8, 0x0485f, 0x0bde0, 0x03082, 0x01225, 0x01b5f,
                                    0x0a83e, 0x0794a, 0x05104, 0x09c19, 0x0fdcf, 0x036fe, 0x01e41, 0x00038,
                                    0x086e8, 0x07046, 0x02c07, 0x04953, 0x07869, 0x0e9c1, 0x0af86, 0x0503a,
                                    0x00f31, 0x0535c, 0x0c2cb, 0x073b9, 0x028e3, 0x03c2b, 0x0cb90, 0x00c33,
                                    0x08fe7, 0x068d3, 0x09a8c, 0x008e0, 0x09fe8, 0x0f107, 0x038ec, 0x0b014,
                                    0x007eb, 0x06335, 0x0afcc, 0x0d55c, 0x0a816, 0x0fa07, 0x05864, 0x0dc8f,
                                    0x07720, 0x0deef, 0x095db, 0x07cbe, 0x0834e, 0x09adc, 0x0bab8, 0x0f8f7,
                                    0x0b21a, 0x0ca98, 0x01a6c, 0x07e4a, 0x04545, 0x078a7, 0x0ba53, 0x00040,
                                    0x09bc5, 0x0bc7a, 0x0401c, 0x00c30, 0x00000, 0x0318d, 0x02e95, 0x065ed,
                                    0x03749, 0x090b3, 0x01e23, 0x0be04, 0x0b612, 0x08c0c, 0x06ea3, 0x08489,
                                    0x0a52c, 0x0aded, 0x0fd13, 0x0bd31, 0x0c225, 0x032f5, 0x06aac, 0x0a504,
                                    0x0d07e, 0x0bb32, 0x08174, 0x0bd8b, 0x03454, 0x04075, 0x06803, 0x03df5,
                                    0x091a0, 0x0d481, 0x09f04, 0x05c54, 0x0d54f, 0x00344, 0x09ffc, 0x00262,
                                    0x01fbf, 0x0461c, 0x01985, 0x05896, 0x0fedf, 0x097ce, 0x0b38d, 0x0492f,
                                    0x03764, 0x041ad, 0x02849, 0x0f927, 0x09268, 0x0bafd, 0x05727, 0x033bc,
                                    0x03249, 0x08921, 0x022da, 0x0b2dc, 0x0e42d, 0x055fa, 0x0a654, 0x073f0,
                                    0x08df1, 0x08149, 0x00d1b, 0x0ac47, 0x0f304, 0x03634, 0x0168b, 0x00c59,
                                    0x09f7d, 0x0596c, 0x0d164, 0x0dc49, 0x038ff, 0x0a495, 0x07d5a, 0x02d4,
                                    0x06c6c, 0x0ea76, 0x09af5, 0x0bea6, 0x08eea, 0x0fbb6, 0x09e45, 0x0e9db,
                                    0x0d106, 0x0e7fd, 0x04ddf, 0x08bb8, 0x0a3a4, 0x03bcd, 0x036d9, 0x05acf
                                };

    //Set the Homorphic Parameters
  	uint64_t plain_mod = 65537;
  	uint64_t mod_degree = 16384;
  	int seclevel = 128;

    if (seclevel != 128) throw runtime_error("Security Level not supported");
    seal::sec_level_type sec = seal::sec_level_type::tc128;

    seal::EncryptionParameters parms(seal::scheme_type::bfv);
    parms.set_poly_modulus_degree(mod_degree);
    
    if (mod_degree == 65536) {
        sec = seal::sec_level_type::none;
        parms.set_coeff_modulus(
            {0xffffffffffc0001, 0xfffffffff840001, 0xfffffffff6a0001,
             0xfffffffff5a0001, 0xfffffffff2a0001, 0xfffffffff240001,
             0xffffffffefe0001, 0xffffffffeca0001, 0xffffffffe9e0001,
             0xffffffffe7c0001, 0xffffffffe740001, 0xffffffffe520001,
             0xffffffffe4c0001, 0xffffffffe440001, 0xffffffffe400001,
             0xffffffffdda0001, 0xffffffffdd20001, 0xffffffffdbc0001,
             0xffffffffdb60001, 0xffffffffd8a0001, 0xffffffffd840001,
             0xffffffffd6e0001, 0xffffffffd680001, 0xffffffffd2a0001,
             0xffffffffd000001, 0xffffffffcf00001, 0xffffffffcea0001,
             0xffffffffcdc0001, 0xffffffffcc40001});  // 1740 bits
    } else {
    parms.set_coeff_modulus(seal::CoeffModulus::BFVDefault(mod_degree));
    }
    parms.set_plain_modulus(plain_mod);
    auto context = make_shared<seal::SEALContext>(parms, true, sec);


    extra1 = chrono::high_resolution_clock::now();
    //Initiate the Class for HHE using PASTA_SEAL and set all parameters for HE
    PASTA_3::PASTA_SEAL M1(in_key, context);

    //Initiate the Class for Encryption and Decryption using PASTA Symmetric Key for Encryption and Decryption
    PASTA_3::PASTA EN(in_key, plain_mod);

    extra2 = chrono::high_resolution_clock::now();
    extra_diff = chrono::duration_cast<chrono::milliseconds>(extra2 - extra1);
    cout << "Time taken to generate HE Keys = " << extra_diff.count() << " milliseconds" << endl;
    
    time_start = chrono::high_resolution_clock::now();
    rpub = retrievePublicRSA(user2);
    inlen = RSA_public_encrypt(m1.length(), (unsigned char *)m1.c_str(), c1, rpub, RSA_PKCS1_PADDING);

    char * s1 = signMessage(user1, m1);
    time_end = chrono::high_resolution_clock::now();
    time_1 = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start);
    cout << "Time taken to generate M1 = " << time_1.count() << " nanoseconds" << endl;

    time_start = chrono::high_resolution_clock::now();
    bool r1 = verifySignature(user1, m1, s1);
    rpriv = retrievePrivateRSA(user2);
    outlen = RSA_private_decrypt(inlen, c1, p1, rpriv, RSA_PKCS1_PADDING);
    time_end = chrono::high_resolution_clock::now();
    time_1 = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start);
    cout << "Time taken to verify and decrypt M1 = " << time_1.count() << " nanoseconds" << endl;

    //Print the necessary parameters to screen
    M1.print_parameters();

    //compute the HE encryption of the secret key and measure performance
    M1.activate_bsgs(false);
    M1.add_gk_indices();
    M1.create_gk();

    //Encrypt the secret key with HE
    cout << "\nUsing HE to encrypt the generated key ...\n" << flush;
    time_start = chrono::high_resolution_clock::now();
    user_start = chrono::high_resolution_clock::now();
    M1.encrypt_key(USE_BATCH);
    time_end = chrono::high_resolution_clock::now();
    time_diff = chrono::duration_cast<chrono::milliseconds>(time_end - time_start);
    cout << "Time taken to encrypt the Symmetric Key = " << time_diff.count() << " milliseconds" << endl;

    //Set dummy plaintext and test encryption and decryption
    vector<uint64_t> x_1 = {0x01c4f, 0x0e3e4, 0x08fe2, 0x0d7db, 0x05594, 0x05c72, 0x0962a, 0x02c3c};
    vector<uint64_t> x_2 = {0x0b3dd, 0x07975, 0x0928b, 0x01024, 0x0632e, 0x07702, 0x05ca1, 0x08e2d};

    //Encrypt plaintext with the set key
    time_start = chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; i++){
      Test[i].c_i = EN.encrypt(x_1);
    }
    time_end = chrono::high_resolution_clock::now();
    user_end = chrono::high_resolution_clock::now();
    time_diff = chrono::duration_cast<chrono::milliseconds>(time_end - time_start);
    user_diff = chrono::duration_cast<chrono::milliseconds>(user_end - user_start);
    cout << "Time taken for symmetric encryption with PASTA for: " << cnt << " values = " << time_diff.count() << " milliseconds" << endl;
    cout << "Execution at User Side: " << cnt << " values = " << user_diff.count() << " milliseconds" << endl;

    //HHE Decomposition using the Symmetric Ciphertext and the HE encrypted key
    cout << "\nDecomposing C' and C ...\n" << flush;
    time_start = chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; i++){
      Test[i].c_1 = M1.HE_decrypt(Test[i].c_i, USE_BATCH);
    }
    time_end = chrono::high_resolution_clock::now();
    time_diff = chrono::duration_cast<chrono::milliseconds>(time_end - time_start);
    cout << "Time taken to Decompose C' and C for " << cnt << " values = " << time_diff.count() << " milliseconds" << endl;

    time_start = chrono::high_resolution_clock::now();
    char * s2 = signMessage(user2, m2);
    time_end = chrono::high_resolution_clock::now();
    time_1 = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start);
    cout << "Time taken to generate M2 = " << time_1.count() << " nanoseconds" << endl;

    time_start = chrono::high_resolution_clock::now();
    bool r2 = verifySignature(user2, m2, s2);
    time_end = chrono::high_resolution_clock::now();
    time_1 = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start);
    cout << "Time taken to verify M2 = " << time_1.count() << " nanoseconds" << endl;

    //HE Evaluation with Evaluation Key
    cout << "Evaluating using Square operation .... \n" << flush;
    eval1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; i++){
      M1.square(Test[i].c_2, Test[i].c_1);
      cout << "Squaring Complete \n";
    }
    eval2 = chrono::high_resolution_clock::now();
    eval_diff = chrono::duration_cast<chrono::milliseconds>(eval2 - eval1);
    cout << "Time taken to Evaluate the Square of C for " << cnt << " values = " << eval_diff.count() << " milliseconds" << endl;


    //Decrypt the Decomposed Ciphertext by the Analyst
    cout << "\nDecryption of Final Message using SK ...\n" << flush;
    time_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; i++){
      Test[i].x_p = M1.decrypt_result(Test[i].c_1, USE_BATCH);
      //utils::print_vector("Decrypted Decomposed Message: ", Test[i].x_p, cerr);
    }
    
    time_end = chrono::high_resolution_clock::now();
    time_diff = chrono::duration_cast<chrono::milliseconds>(time_end - time_start);
    cout << "Decryption Time for " << cnt << " values = " << time_diff.count() << " milliseconds" << endl;

    time_start = chrono::high_resolution_clock::now();
    rpub = retrievePublicRSA(user2);
    inlen = RSA_public_encrypt(m3.length(), (unsigned char *)m3.c_str(), c2, rpub, RSA_PKCS1_PADDING);

    char * s3 = signMessage(user3, m3);
    time_end = chrono::high_resolution_clock::now();
    time_1 = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start);
    cout << "Time taken to generate M3 = " << time_1.count() << " nanoseconds" << endl;

    time_start = chrono::high_resolution_clock::now();
    bool r3 = verifySignature(user3, m3, s3);
    rpriv = retrievePrivateRSA(user2);
    outlen = RSA_private_decrypt(inlen, c2, p2, rpriv, RSA_PKCS1_PADDING);
    time_end = chrono::high_resolution_clock::now();
    time_1 = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start);
    cout << "Time taken to verify and decrypt M3 = " << time_1.count() << " nanoseconds" << endl;

    time_start = chrono::high_resolution_clock::now();
    char * s4 = signMessage(user2, m4);
    time_end = chrono::high_resolution_clock::now();
    time_1 = chrono::duration_cast<chrono::nanoseconds>(time_end - time_start);
    cout << "Time taken to generate M4 = " << time_1.count() << " nanoseconds" << endl;


    return 0;
}