#include <iostream>
#include <math.h>
#include "ip.h"

const int MIN_IP = 0;
const int MAX_IP =  0xFFFFFFFF;
const int VALID_MASK_SIZE =  2; 
const int WORD_SIZE =  32;
const int VALID_IP_COMP_SIZE =  4;
const int COMP_SIZE = 8;


//constructor implementation, only initiats.
IP::IP(String field_type) : Field(field_type),
 min_ip(MIN_IP), max_ip(MAX_IP){};

//destructor implementation?

IP::~IP(){}

//set_value implementation
bool IP::set_value(String mask){
    String* mask_components;
    String* ip_mask_components;
    size_t mask_components_size=0;
    size_t ip_mask_components_size=0;
    unsigned int ip_mask=0;
    int num_of_bits_mask=0;
    unsigned int bits_mask=MAX_IP;

//checks if the rule (mask) is valid
    mask.split("/", &(mask_components), &(mask_components_size));
    if((mask_components_size!=VALID_MASK_SIZE) || (mask_components==NULL)){
    	delete [] mask_components;
        return false;
    }

//cleans mask and splits it to two convinient variebles:
//num_of_bits_mask is an integers, the num of bits of the mask from the right
//ip_mask_components is the ip part of the mask broken to four parts
	mask_components[0]=mask_components[0].trim();
	num_of_bits_mask=(mask_components[1].trim()).to_integer();
//checks that the bits part of the rule is valid
    if((num_of_bits_mask<0) || (num_of_bits_mask>WORD_SIZE)){
       	delete [] mask_components;
        return false;
    }
//splits ip part and checks if valid
    (mask_components[0]).split(".",
     &(ip_mask_components), &(ip_mask_components_size));
    if((ip_mask_components_size!=VALID_IP_COMP_SIZE)
     || (ip_mask_components==NULL)){
    	delete [] mask_components;
    	delete [] ip_mask_components;
        return false;
    }

//makes a big ip integer out of ip_mask_components
	for(int i=0;i<VALID_IP_COMP_SIZE;i++){
		ip_mask += (unsigned int)(ip_mask_components[i].to_integer() 
		<< (COMP_SIZE*(VALID_IP_COMP_SIZE-1-i)));
	}

//makes a bits-mask
    bits_mask = bits_mask >> (WORD_SIZE-num_of_bits_mask);
    bits_mask = bits_mask << (WORD_SIZE-num_of_bits_mask);

//sets range
    min_ip = ip_mask & bits_mask;
    max_ip = ((min_ip)|(~bits_mask));

	delete [] mask_components;
   	delete [] ip_mask_components;
    return true;
}


//match_value implementation
bool IP :: match_value(String ip_address) const{
    String* ip_components;
	size_t ip_components_size=0;
    unsigned int ip_value=0;

//makes a big ip integer out of ip_adress, and checks if valid
    ip_address.split(".", &(ip_components),&(ip_components_size));
    if((ip_components_size != VALID_IP_COMP_SIZE) && (ip_components==NULL)){
    	delete [] ip_components;
        return false;
    }
    
    for(int i=0;i<VALID_IP_COMP_SIZE;i++){
		ip_value =ip_value+(ip_components[i].to_integer() 
		<< (COMP_SIZE*(VALID_IP_COMP_SIZE-1-i)));
	}

//returns true if in range
	delete [] ip_components;
    return ((ip_value >= min_ip) && (ip_value<=max_ip));

}
