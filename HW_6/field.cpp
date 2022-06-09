#include <iostream>
#include "field.h"

const int FIELD_SIZE = 2;

// constructor implementation, only initiates
Field :: Field (String pattern) {
    this->pattern = pattern;
}

//destructor?

Field :: ~Field(){}

//match implementation
bool Field :: match(String packet){
    String* packet_components;
    size_t packet_components_size = 0;
    
//iterates on the rule, splits it to the type and the content


    packet.split("=, ", &(packet_components),&(packet_components_size));
    String *trimmed_packet = new String[(int)(packet_components_size)];
    for(int i=0; i<(int)(packet_components_size);i+=FIELD_SIZE){
    	trimmed_packet[i]=packet_components[i].trim();
    	if(trimmed_packet[i].equals(pattern)){
    		trimmed_packet[i+1] = packet_components[i+1].trim();
    		bool is_match = match_value(trimmed_packet[i+1]);
    		delete[] trimmed_packet;
    		delete[] packet_components;
    		return is_match;
    	}
    }
    
	delete [] packet_components;
	delete[] trimmed_packet;
return false;
}
