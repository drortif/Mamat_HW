#include <iostream>
#include "port.h"

const int MIN_PORT= 0;
const int MAX_PORT= 65535;
const int VALID_NUM_OF_BOUNDS= 2;

//constructor implementation, only initiats. and destructor
Port::Port(String field_type) : Field(field_type),
 min_port(MIN_PORT), max_port(MAX_PORT){}

Port::~Port(){}

//set_value implementation
bool Port::set_value(String ports_range){
    String* bounds;
    size_t bounds_size=0;
    int lower_bound=0;
    int upper_bound=0;

//splits range to upper and lower bounds
    ports_range.split("-", &(bounds),&(bounds_size));
    if((bounds_size != VALID_NUM_OF_BOUNDS) || (bounds==NULL)){
    	delete [] bounds;
        return false;
    }

    lower_bound=((bounds[0].trim()).to_integer());
    upper_bound=((bounds[1].trim()).to_integer());

//check if bounds value is valid
    if((lower_bound < 0) || (upper_bound > MAX_PORT)
     || (upper_bound < lower_bound)){
    	delete [] bounds;
        return false;
    }

//set the value to the boundries
    min_port=lower_bound;
    max_port=upper_bound;
    delete [] bounds;
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
