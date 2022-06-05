#include <iostream>

#include "ip.h"



#define MIN_IP 0

#define MAX_IP 0xFFFFFFFF

#define VALID_MASK_SIZE 2 /* -1? */

#define WORD_SIZE 32

#define VALID_IP_COMP_SIZE 4

#define DIGIT 10

#define RIGHT_MOST_COMPONENT 3



//constructor implementation, only initiats.

IP::IP(String field_type) : Field(field_type), min_ip(MIN_IP), max_ip(MAX_IP);



//destructor implementation?



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

    if(!(mask.split("/", &(mask_components), &(mask_components_size)))){

        return false;

    }



    if(mask_components_size!=VALID_MASK_SIZE){

        return false;

    }



//cleans mask and splits it to two convinient variebles:

//num_of_bits_mask is an integers, the num of bits of the mask from the right

//ip_mask_components is the ip part of the mask broken to four parts

    mask_components[0]=mask_components[0].trim();

    num_of_bits_mask=(mask_components[1].trim()).to_integer();

//checks that the bits part of the rule is valid

    if((num_of_bits_mask<0) || (num_of_bits_mask>WORD_SIZE)){

        return false;

    }

//splits ip part and checks if valid

    if(!(ip_mask_components.split(".", &(mask_components[0]), &ip_mask_components_size))){

        return false;

    }

    if(ip_mask_components_size!=VALID_IP_COMP_SIZE){

        return false;

    }



//makes a big ip integer out of ip_mask_components

    for(int i=0, i<ip_mask_components_size, i++){

    /*math?*/    ip_mask=ip_mask+(DIGIT^(VALID_IP_COMP_SIZE*(RIGHT_MOST_COMPONENT-i))*ip_mask_components[i]);

    }



//makes a bits-mask

    bits_mask = bits_mask >> (WORD_SIZE-num_of_bits_mask);



//sets range

    min_ip = ip_mask & (!(bits_mask));

    max_ip = min_ip|bits_mask;



    return true;

}



//match_value implementation

bool IP :: match_value(String ip_address) const{

    String* ip_components;

    size_t ip_components_size=0;

    unsigned int ip_value=0;



//makes a big ip integer out of ip_adress, and checks if valid

    if(!(ip_address.split(".", &(ip_components),&(ip_components_size)))){

        return false

    }

    if(ip_components != VALID_IP_COMP_SIZE){

        return false;

    }

    for(int i=0, i<ip_components_size, i++){

    /*math?*/    ip_value=ip_value+(DIGIT^(VALID_IP_COMP_SIZE*(RIGHT_MOST_COMPONENT-i))*ip_components[i]);

    }



//returns true if in range

    return ((ip_value >= min_ip) && (ip_value<=max_ip));



}
