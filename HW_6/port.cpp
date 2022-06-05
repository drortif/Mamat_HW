#include <iostream>

#include "port.h"



#define MIN_PORT 0

#define MAX_PORT 65535

#define VALID_NUM_OF_BOUNDS 2



//constructor implementation, only initiats.

port::port(String field_type) : Field(field_type), min_port(MIN_PORT), max_port(MAX_PORT);



//destractor?



//set_value implementation

bool Port::set_value(String ports_range){

    String* bounds;

    size_t bounds_size=0;

    int lower_bound=0;

    int upper_bound=0;



//splits range to upper and lower bounds

    if(!(ports_range.split("-", &(bounds),&(bounds_size)))){

        return false;

    }

    if(bounds_size != VALID_NUM_OF_BOUNDS){

        return false;

    }



    lower_bound=(bounds[0].trim());

    upper_bound=(bounds[1].trim());



//check if bounds value is valid

    if((lower_bound < 0) || (upper_bound > MAX_PORT) || (upper_bound < lower_bound)){

        return false;

    }



//set the value to the boundries

    min_port=lower_bound;

    max_port=upper_bound;

    return true;

}



//match_value implementation

bool Port::match_value(String port) const {

    int port_num=0;



//makes an integer out of port

    port=port.trim();

    port_num=port.to_integer();



//return true if in range

    return ((port_num>=min_port) && (port_num<=max_port));

}
