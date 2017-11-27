#include <stdint.h>

#include <print-utils.h>
#include <handlefile.h>
#include <logging.h>
#include <port.h>
#include <bls.h>

#define BUFFER_SIZE 1024

struct keypair_t* generate_key_pair()
{
    struct keypair_t* kpair = NULL;
    kpair = (struct keypair_t*)malloc(sizeof(struct keypair_t));

    if(!kpair) {
        Log(LOG_ERROR,"Out of Memory: Unable to allocate memory to Keypair");
        return NULL;
    }

    struct public_key_t* pubkey = NULL;
    pubkey = (struct public_key_t*)malloc(sizeof(struct public_key_t));

    if(!pubkey) {
        Log(LOG_ERROR,"Out of Memory: Unable to allocate memory to Public Key");
        free(kpair);
        return NULL;
    }

    struct private_key_t* pkey = NULL;
    pkey = (struct private_key_t*)malloc(sizeof(struct private_key_t));

    if(!pkey) {
        Log(LOG_ERROR,"Out of Memory: Unable to allocate memory to Private Key");
        free(kpair);
        free(pubkey);
        return NULL;
    }

    struct pairing_s *pairing;
    pairing = (struct pairing_s*)malloc(sizeof(pairing_t));

    if(!pairing) {
        Log(LOG_ERROR,"Out of Memory: Unable to allocate memory to Pairing");
        free(pkey);
        free(kpair);
        free(pubkey);
        return NULL;
    }

    pairing_init_set_buf(pairing, a1_param, strlen(a1_param));

    pkey->pairing = pairing;
    pubkey->pairing = pairing;

    element_init_G1(pubkey->alpha,pairing);
    element_init_G1(pkey->alpha,pairing);
    element_init_G1(pubkey->g,pairing);
    element_init_G1(pkey->g,pairing);
    element_init_Zr(pkey->x,pairing);
    element_init_G1(pubkey->v,pairing);

    element_random(pubkey->alpha);
    element_set(pkey->alpha, pubkey->alpha);

    element_random(pubkey->g);
    element_set(pkey->g, pubkey->g);
    
    element_random(pkey->x);

    element_pow_zn(pubkey->v,pubkey->g,pkey->x);

    kpair->pub_key = pubkey;
    kpair->pvt_key = pkey;

    return kpair;
}

void export_pvt_key(struct private_key_t* pkey, const char* filename)
{
    FILE* file = fopen(filename,"wb");

    unsigned char* data;
    data = (unsigned char*)malloc(G1_LEN_COMPRESSED);
    
    element_to_bytes_compressed(data,pkey->alpha);
    fwrite(data,G1_LEN_COMPRESSED,1,file);
    
    element_to_bytes_compressed(data,pkey->g);
    fwrite(data,G1_LEN_COMPRESSED,1,file);
    
    element_to_bytes(data,pkey->x);
    fwrite(data,ZR_LEN,1,file);
    
    free(data);
    fflush(file);
    fclose(file);
}

struct private_key_t* import_pvt_key(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    struct private_key_t* pkey = (struct private_key_t*)malloc(sizeof(struct private_key_t));

    pkey->pairing = (struct pairing_s*)malloc(sizeof(struct pairing_s));

    pairing_init_set_buf(pkey->pairing, a1_param, strlen(a1_param));
    element_init_G1(pkey->alpha, pkey->pairing);
    element_init_G1(pkey->g, pkey->pairing);
    element_init_Zr(pkey->x, pkey->pairing);

    unsigned char* data = (unsigned char*)malloc(G1_LEN_COMPRESSED);

    fread(data,G1_LEN_COMPRESSED,1,file);
    element_from_bytes_compressed(pkey->alpha,data);
    fread(data,G1_LEN_COMPRESSED,1,file);
    element_from_bytes_compressed(pkey->g,data);
    fread(data,ZR_LEN,1,file);
    element_from_bytes(pkey->x,data);

    free(data);
    fclose(file);

    return pkey;
}

void export_public_key(struct public_key_t* pubkey, const char* filename)
{
    FILE* file = fopen(filename,"wb");

    unsigned char* data;
    data = (unsigned char*)malloc(G1_LEN_COMPRESSED);
    
    element_to_bytes_compressed(data,pubkey->alpha);
    fwrite(data,G1_LEN_COMPRESSED,1,file);
    
    element_to_bytes_compressed(data,pubkey->g);
    fwrite(data,G1_LEN_COMPRESSED,1,file);
    
    element_to_bytes_compressed(data,pubkey->v);
    fwrite(data,G1_LEN_COMPRESSED,1,file);
    
    free(data);
    fflush(file);
    fclose(file);
}

struct public_key_t* import_public_key(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    struct public_key_t* pubkey = (struct public_key_t*)malloc(sizeof(struct public_key_t));
    // int length[1];

    pubkey->pairing = (struct pairing_s*)malloc(sizeof(struct pairing_s));

    pairing_init_set_buf(pubkey->pairing, a1_param, strlen(a1_param));
    element_init_G1(pubkey->alpha, pubkey->pairing);
    element_init_G1(pubkey->g, pubkey->pairing);
    element_init_G1(pubkey->v, pubkey->pairing);

    // fread(length,4,1,file);

    // printf("%d\n",length[0]);
    // printf("%x\n",length[0]);

    unsigned char* data = (unsigned char*)malloc(G1_LEN_COMPRESSED);

    fread(data,G1_LEN_COMPRESSED,1,file);
    element_from_bytes_compressed(pubkey->alpha,data);
    fread(data,G1_LEN_COMPRESSED,1,file);
    element_from_bytes_compressed(pubkey->g,data);
    fread(data,G1_LEN_COMPRESSED,1,file);
    element_from_bytes_compressed(pubkey->v,data);

    free(data);
    fclose(file);

    return pubkey;
}

static void write_tag(struct tag_t* tag, FILE* file)
{
    unsigned char* data = (unsigned char*)malloc(G1_LEN_COMPRESSED);
    element_to_bytes_compressed(data,tag->sigma);
    fwrite(data,1,G1_LEN_COMPRESSED,file);
    fwrite(&(tag->index),sizeof(uint32_t),1,file);
    free(data);
}

static struct tag_t* read_tag(FILE* file)
{
    unsigned char* data = (unsigned char*)malloc(G1_LEN_COMPRESSED);
    struct tag_t* tag = (struct tag_t*)malloc(sizeof(struct tag_t));

    pairing_init_set_buf(tag->pairing,a1_param,strlen(a1_param));
    fread(data,1,G1_LEN_COMPRESSED,file);
    element_init_G1(tag->sigma,tag->pairing);
    element_from_bytes_compressed(tag->sigma,data);
    fread(&(tag->index),sizeof(uint32_t),1,file);

    return tag;
}

void export_file(struct file_t* file_struct, const char* filename)
{
    FILE* file = fopen(filename, "wb");
    
    fwrite(&(file_struct->nr_blocks),sizeof(unsigned long long),1,file);
    for(uint64_t i=0;i<file_struct->nr_blocks;i++) {
        struct file_piece_t* fpiece = file_struct->pieces+i;
        fwrite(&(fpiece->blk_size),sizeof(unsigned long long),1,file);
        write_tag(fpiece->tag,file);
        fwrite(&(fpiece->parity),2,6,file);
        fwrite(fpiece->data,1,fpiece->blk_size,file);
    }

    fclose(file);
}

struct file_t* import_file(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    struct file_t* file_struct = (struct file_t*)malloc(sizeof(struct file_t));

    fread(&(file_struct->nr_blocks),sizeof(unsigned long long),1,file);
    file_struct->pieces = (struct file_piece_t*)
                malloc(sizeof(struct file_piece_t)*(file_struct->nr_blocks));

    for(uint64_t i=0;i<file_struct->nr_blocks;i++) {
        struct file_piece_t* fpiece = file_struct->pieces+i;
        fread(&(fpiece->blk_size),sizeof(unsigned long long),1,file);
        fpiece->tag = read_tag(file);
        fread(&(fpiece->parity),2,6,file);
        fpiece->data = (unsigned char*)malloc(fpiece->blk_size);
        fread(fpiece->data,1,fpiece->blk_size,file);
    }

    fclose(file);
}

void free_public_key(struct public_key_t* pubkey)
{
    free(pubkey->pairing);
    // element_free(pubkey->alpha);
    // element_free(pubkey->v);
    // element_free(pubkey->g);
    // free(pubkey);
}

void free_private_key(struct private_key_t* pkey)
{
    free(pkey->pairing);
    // element_free(pkey->alpha);
    // element_free(pkey->x);
    // element_free(pkey->g);
}

void free_keypair(struct keypair_t* kpair)
{
    free_private_key(kpair->pvt_key);
    // free_public_key(kpair->pub_key);
    // element_free(kpair->pub_key->alpha);
    // element_free(kpair->pub_key->g);
    // element_free(kpair->pub_key->v);
    free(kpair->pvt_key);
    free(kpair->pub_key);
}