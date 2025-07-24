#include "felix_base.h"
#include "mbedtls/aes.h"

#define BLOCK_SIZE 16

// test for AES - ECB mode encryption
void TestECB(int argc, char *argv){
    // 准备明文数据
    unsigned char plaintext[] = "Test AES ECB encryption.";
    // 获取明文的长度
    size_t plaintext_len = sizeof(plaintext) - 1;
    // 计算填充后的长度
    size_t padded_len = ((plaintext_len / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    // 计算填充的大小
    size_t padding_size = padded_len - plaintext_len;
    // 设置缓冲区
    unsigned char padded_plaintext[128] = {0};
    // 填充明文
    memcpy(padded_plaintext, plaintext, plaintext_len);
    // 填充数据
    for (size_t i = 0; i < padding_size; i++) {
        // 如果缺N个字节，就填充N个字节，每一个字节都是N
        padded_plaintext[plaintext_len + i] = padding_size;
    }
    // 打印填充后的明文
    printf("Padded plaintext: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02x ", padded_plaintext[i]);
    }
    printf("\n");

    // AES-128需要16字节的密钥
    unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                             0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    // 初始化加密上下文
    mbedtls_aes_context aes_ctx;
    mbedtls_aes_init(&aes_ctx);

    // 设置加密秘钥
    mbedtls_aes_setkey_enc(&aes_ctx, key, 128);
    // 密文数据
    unsigned char encrypted_data[128] = {0};
    // 加密数据
    for (size_t i = 0; i < padded_len; i += BLOCK_SIZE) {
        mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_ENCRYPT,
                              padded_plaintext + i, encrypted_data + i);
    }
    // 打印加密后的数据
    printf("Encrypted data: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02x ", encrypted_data[i]);
    }
    printf("\n");
    // 释放加密上下文
    mbedtls_aes_free(&aes_ctx);


    // 解密数据
    mbedtls_aes_init(&aes_ctx);
    // 设置解密秘钥
    mbedtls_aes_setkey_dec(&aes_ctx, key, 128);
    // 解密数据
    unsigned char decrypted_data[128] = {0};
    for (size_t i = 0; i < padded_len; i += BLOCK_SIZE) {
        mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_DECRYPT,
                              encrypted_data + i, decrypted_data + i);
    }
    // 打印解密后的数据
    printf("Decrypted data: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02x ", decrypted_data[i]);
    }
    printf("\n");
    // 去除填充
    size_t unpadded_len = padded_len - decrypted_data[padded_len - 1];
    printf("Unpadded decrypted data: ");
    for (size_t i = 0; i < unpadded_len; i++) {
        printf("%c", decrypted_data[i]);
    }
    printf("\n");
    // 释放解密上下文
    mbedtls_aes_free(&aes_ctx);
}

void TestCBC(int argc, char *argv) {
    unsigned char plaintext[] = "Test AES CBC encryption.";
    size_t plaintext_len = sizeof(plaintext) - 1;
    size_t padded_len = ((plaintext_len / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    size_t padding_size = padded_len - plaintext_len;
    // 设置缓冲区
    unsigned char *padded_plaintext = malloc(padded_len);
    if (padded_plaintext == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    memcpy(padded_plaintext, plaintext, plaintext_len);
    for (size_t i = 0; i < padding_size; i++) {
        padded_plaintext[plaintext_len + i] = padding_size;
    }
    printf("Padded plaintext: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02x ", padded_plaintext[i]);
    }
    printf("\n");

    // 设置CBC模式的key
    unsigned char key[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    // 设置CBC模式的IV
    unsigned char iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char ivEncrypt[BLOCK_SIZE];
    unsigned char ivDecrypt[BLOCK_SIZE];
    memcpy(ivEncrypt, iv, BLOCK_SIZE);
    memcpy(ivDecrypt, iv, BLOCK_SIZE);

    mbedtls_aes_context aes_ctx;
    mbedtls_aes_init(&aes_ctx);

    unsigned char *encryptText = malloc(padded_len);
    mbedtls_aes_setkey_enc(&aes_ctx, key, 128);
    mbedtls_aes_crypt_cbc(&aes_ctx, MBEDTLS_AES_ENCRYPT,
                              padded_len, ivEncrypt, padded_plaintext, encryptText);
    printf("Encrypted data: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02x ", encryptText[i]);
    }
    printf("\n");

    mbedtls_aes_setkey_dec(&aes_ctx, key, 128);
    mbedtls_aes_crypt_cbc(&aes_ctx, MBEDTLS_AES_DECRYPT,
                              padded_len, ivDecrypt, encryptText, padded_plaintext);
    printf("Decrypted data: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02x ", padded_plaintext[i]);
    }
    printf("\n");
    size_t unpadded_len = padded_len - padded_plaintext[padded_len - 1];
    printf("Unpadded decrypted data: ");
    for (size_t i = 0; i < unpadded_len; i++) {
        printf("%c", padded_plaintext[i]);
    }
    printf("\n");

    free(padded_plaintext);
    free(encryptText);
    mbedtls_aes_free(&aes_ctx);
}

int main(int argc, char *argv[]) {
    TestCBC(argc, argv[0]);
    return 0;
}