#include <iostream>
#include "field.h"

#define VALID_FIELDS_NUM 4
#define VALID_FIELD_SIZE 2

// constractor implementation, only initiates
Field :: Field (String pattern) {
    this->pattern = pattern;
}

//destructor?

Field :: ~Field(){}

//match implementation
bool Field :: match(String packet){
    String* fields_arr;
    String* current_field;
    size_t fields_arr_size = 0;
    size_t current_field_size = 0;
//splits the packet to fields and checks if it's configuration is valid
    packet.split(",", &(fields_arr), &(fields_arr_size));
    if(/*covert?*/(fields_arr_size != VALID_FIELDS_NUM)  || (fields_arr==NULL) ){
        return false;
        delete [] fields_arr;
        delete fields_arr;
    }

//itirates on the fields
    for(size_t i=0;i<fields_arr_size;i++){
//checks if the field is valid, splits it to the type and the content
    (fields_arr[i]).split("=", &(current_field),&(current_field_size));
        if(/*covert?*/(current_field_size != VALID_FIELD_SIZE) || (current_field==NULL) ){
        	delete [] current_field;
        	delete current_field;
        	return false;
        }
//cleans the type (0) and the content (1) of the field
        current_field[0]=current_field[0].trim();
        current_field[1]=current_field[1].trim();
//the actual matching, compares type with current pattern and uses match_value accordingly
		
        if((this->pattern).equals(current_field[0])){
            return (match_value(current_field[1]));
        }
    }
return false;
//do we need to free things any time we return?
}
