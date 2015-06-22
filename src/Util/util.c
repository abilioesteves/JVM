/*! \file 
	\brief Implementação das Funções Utilitárias para IO
	
	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "util.h"

/*!
	trata se os argumentos passados para o executavel, se esta correto
*/
static int VerificaLeitorExibidorCMDArgs(int argc, char **argv){
	FILE *fp;
    char *arq1name;
    int i;

    if (argc < LEITOREXIBIDORCMDARGCOUNT + 1 || argc > LEITOREXIBIDORCMDARGCOUNT + 2){
        return E_INVALID_NUM_ARGS; /*ERRO 1: invalido numero de argumentos*/
    }
	if ((fp=fopen(argv[1],"rb"))==NULL) {
		return E_ARGV1_FILE_NOT_EXISTENT; /*ERRO 2: argv[2] invalido: arquivo nao existente*/
	}else if (argv[2] != NULL && (strcmp(argv[2],"-tela") && strcmp(argv[2],"-arquivo"))){
		return E_OPCAO_NAO_EXISTENTE; /*ERRO 6: opcao nao existente*/
	} else {
		fclose(fp);
	}
	return E_SUCCESS;
}

/*!
	trata se os argumentos passados para o executavel, se esta correto
*/
static int VerificaJVMCMDArgs(int argc, char** argv){
	FILE *fp;
    char *arq1name;
    int i;

    if (argc < JVMCMDARGCOUNT + 1 || argc > JVMCMDARGCOUNT + 3){
        return E_INVALID_NUM_ARGS; /*ERRO 1: invalido numero de argumentos*/
    }
	if ((fp=fopen(argv[1],"rb"))==NULL) {
		return E_ARGV1_FILE_NOT_EXISTENT; /*ERRO 2: argv[2] invalido: arquivo nao existente*/
	}else{
		fclose(fp);
	}
	if (argc > JVMCMDARGCOUNT + 1) {
		if (!strcmp(argv[2],"--help")) {
			return 1;
		}else if ( argc > JVMCMDARGCOUNT + 2 && !strcmp(argv[2], "-p")) {
			if (!strcmp(argv[3], "both")) return 2;
			if (!strcmp(argv[3], "tela")) return 3;
			if (!strcmp(argv[3], "arquivo")) return 4;
		}
	}
	return E_SUCCESS;
}

// le o arquivo passado por linha de comando e retorna um array de bytes
static DADOS LeArquivo(char* arqNome) {
	// inicializacoes
	unsigned long int i=0l;
	DADOS d = initDADOS();
	uint8_t value;
	FILE *fp=fopen(arqNome,"rb");

	// leitura iterativa, byte a byte
	while(fread(&value, sizeof(uint8_t), 1, fp)!=0){
		*(d.bytes + i) = value; i++;
		d.bytes = realloc(d.bytes,(i+1)*sizeof(uint8_t));
	}
	*(d.bytes + i) = (uint8_t)'\0'; // char \0 delimitando o fim do arquivo
	d.tamanho = i;

	fclose(fp);
	return d;
}

// escreve um array de bytes em um arquivo
static int EscreveArquivo(DADOS d, char *arqName){
	// inicializacoes
	FILE *fp = fopen(arqName,"wb");

	// escrita iterativa, byte a byte
	for(unsigned long int i=0l; i < d.tamanho; i++){
		fwrite((d.bytes+i),sizeof(uint8_t),1,fp);
	}

	fclose(fp);
	return E_SUCCESS;
}

char* getBasePath(char* pathName) {
	int i = strlen(pathName), j = 0;
	for (; i >= 0; --i) {
		if (pathName[i] == '/') {
			j++;
			break;
		} else if (pathName[i] == '\\') {
			j++;
			break;
		}
	}

	int size = 0;
	if (j == strlen(pathName)) {
		size = j;
	} else {
		 size = strlen(pathName) - j + 1;
	}
	char* toReturn = (char*)malloc(size*sizeof(char));
	toReturn[size-1] = '\0';
	strncpy(toReturn, pathName, size);

	return toReturn;
}

// inicializa uma estrutura do tipo UTIL
UTIL getUTILInstance(void){
	UTIL util;
	
	util.VerificaJVMCMDArgs = VerificaJVMCMDArgs;
	util.VerificaLeitorExibidorCMDArgs = VerificaLeitorExibidorCMDArgs;
	util.LeArquivo = LeArquivo;
	util.EscreveArquivo = EscreveArquivo;

	return util;
}


















