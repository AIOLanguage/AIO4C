typedef struct AIODeclaration {
    char* methodName;
    char exactArgsList[16][256]; //16 args max
} AIO_DECLARATION;