/*! \file
	\brief Definicoes dos campos, funcoes e inicializadores de estruturas do tipo MethodInfo de um arquivo .class

	Autores: 
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#ifndef MODULE_METHOD_INFO
	#define MODULE_METHOD_INFO
	#include "../../../Common/common.h"

	typedef struct _method_info {
		uint16_t access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		struct _attribute_info* attributes;
	};

	typedef struct _method {
		struct _method_info* method;
		int (*addField)(struct _method*, CONSTANT_POOL*,int, DADOS*);
	} METHOD_POOL;
	
	METHOD_POOL* initMETHOD_POOL();


#endif