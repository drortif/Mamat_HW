#include <iostream>
#include "input.h"
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"



#define VALID_RULE_COMP 2


int main(int argc, char **argv){
	if(check_args(argc,argv)) {
		return 0;
	} 

    String rule(argv[1]);
    String* rule_components;
    String rule_field_type;
    String rule_data;
    size_t rule_components_size=0;
//breaking the rule to its parts
    rule.split("=", &rule_components, &(rule_components_size));

    	if ((rule_components_size!=VALID_RULE_COMP) || (rule_components==NULL)) {
    	delete [] rule_components;
		return 0;
	}
	
    rule_field_type=(rule_components[0]).trim();
    rule_data=(rule_components[1]).trim();
	if ((rule_field_type).equals("dst-port") || (rule_field_type).equals("src-port")){
        Port rule_port(rule_field_type);
        rule_port.set_value(rule_data);
        parse_input(rule_port);
    }

    	if ((rule_field_type).equals("dst-ip") || (rule_field_type).equals("src-ip")){
        IP rule_ip(rule_field_type);
        rule_ip.set_value(rule_data);
        parse_input(rule_ip);
        }
        delete [] rule_components;
        return 0;
}
