#ifndef IP_H

#define IP_H

#include "field.h"

 

#define MIN_IP 0

#define MAX_IP 0xFFFFFFFF



class IP : public Field {

private:

//range of valid ip adressess according to the rule(s?)

    unsigned int min_ip;

    unsigned int max_ip;

public:

//constructor, field_type will be the "pattern" in "Field"

    IP(String field_type);

//destructor

    ~IP();

//set value, mask is the rule for ip addresses

    bool set_value(String mask);

//match value

    bool match_value(String ip_address) const;

}

#endif
