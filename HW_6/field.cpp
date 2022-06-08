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
bool Field :: match(String rule){
    String* rule_components;
    size_t rule_components_size = 0;
    String rule_field_type;
    String rule_data;
    
//itirates on the rule, splits it to the type and the content

    rule.split("=", &(rule_components),&(rule_components_size));
        if((int)(rule_components_size != VALID_COMP_SIZE) || (rule_components==NULL) ){
        	delete [] rule_components;
        	return false;
        }
//cleans the type (0) and the content (1) of the field
        rule_field_type=rule_components[0].trim();
        rule_data=rule_components[1].trim();
//the actual matching, compares type with current pattern and uses match_value accordingly
		
        if((this->pattern).equals(rule_field_type)){
        	delete [] rule_components;
            return (match_value(rule_data));
        }
	delete [] rule_components;
return false;
//do we need to free things any time we return?
}
