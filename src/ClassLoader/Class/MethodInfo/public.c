#include "methodinfo.h"
#include "private.c"

static int addMethod(FIELD_POOL* this, CONSTANT_POOL* cp, int ordem, DADOS* d) {
	
	this->fields[ordem].access_flags = getAccessFlags(d);
	this->fields[ordem].name_index = getNameIndex(d);
	this->fields[ordem].descriptor_index = getDescriptorIndex(d);
	this->fields[ordem].attributes_count = getAttributesCount(d);

	ATTRIBUTE_POOL* field_attributes = initATTRIBUTE_POOL(this->fields[ordem].attributes_count);
	for(int i =0; i<this->fields[ordem].attributes_count; i++){
		field_attributes->addAttribute(field_attributes, cp, i, d);
	}
	this->fields[ordem].attributes = field_attributes->attributes;

	return E_SUCCESS; 
}



METHOD_POOL* initMETHOD_POOL(int *count) {
	METHOD_POOL* toReturn = (METHOD_POOL*)malloc(sizeof(METHOD_POOL));

	toReturn->method = (struct _method_info*)malloc((*count - 1)*sizeof(struct _method_info));
	toReturn->addMethod = addMethod;

	return toReturn;
}