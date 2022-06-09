#include <iostream>
#include "field.h"

#define UNVALID_FIELDS_NUM 0
#define VALID_COMP_SIZE 2

// constractor implementation, only initiates
Field :: Field (String pattern) {
    this->pattern = pattern;
}

//destructor?

Field :: ~Field(){}

//match implementation
bool Field :: match(String packet){
    String* packet_components;
    size_t packet_components_size = 0;
    String rule_field_type;
    String rule_data;
    
//itirates on the rule, splits it to the type and the content


    packet.split("=, ", &(packet_components),&(packet_components_size));
    String *trimmed_packet = new String[(int)(packet_components_size)];
    for(int i=0; i<(int)(packet_components_size);i+=2){
    	trimmed_packet[i]=packet_components[i].trim();
    	if(trimmed_packet[i].equals(pattern)){
    		trimmed_packet[i+1] = packet_components[i+1].trim();
    		bool is_match = match_value(trimmed_packet[i+1]);
    		delete[] trimmed_packet;
    		delete[] packet_components;
    		return is_match;
    	}
    }
    
        //if((int)(rule_components_size != VALID_COMP_SIZE) || (rule_components==NULL) ){
        	//delete [] rule_components;
        	//return false;
        //}
        
//cleans the type (0) and the content (1) of the field
		
        //rule_field_type=rule_components[0].trim();
        //rule_data=rule_components[1].trim();
//the actual matching, compares type with current pattern and uses match_value accordingly
		
        //if((this->pattern).equals(rule_field_type)){
        	//delete [] rule_components;
            //return (match_value(rule_data));
        //}
	delete [] packet_components;
	delete[] trimmed_packet;
return false;
//do we need to free things any time we return?
}
