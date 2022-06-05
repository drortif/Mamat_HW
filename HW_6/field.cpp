#include <iostream>

#include "field.h"



#define VALID_FIELDS_NUM 4 /* -1? */

#define VALID_FIELD_SIZE 2 /* -1? */



// constractor implementation, only initiates

Fields :: Field (String pattern) {

    this->pattern = pattern;

}



//destructor?



//match implementation

bool Field :: match(String packet){

    String* fields_arr;

    String* current_field;

    size_t fields_arr_size = 0;

    size_t current_field_size = 0;

//checks if the packet is valid as a packet, and splits it to fields

    if(/*returns true on success?*/!(packet.split(",", &(fields_arr), /*<-legal?->*/&(fields_arr_size)))){

        return false;

    }

    if(/*covert?*/fields_arr_size != VALID_FIELDS_NUM){

        return false;

    }



//itirates on the fields

    for(int i=0, /*covert?*/i<fields_arr_size, i++){

//checks if the field is valid, splits it to the type and the content

        if(/*returns true on success?*/!((fields_arr[i]).split("=", &(current_field),current_field_size))){

            return false;

        }



        if(/*covert?*/current_field_size != VALID_FIELD_SIZE){

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
