

#ifndef PORT_H

#define PORT_H

#include "field.h"

 

class Port : public Field {

private:

//range of valid ports according to the rule(s?)

    int min_port;

    int max_port;

public:

 

//constructor, field_type will be the "pattern" in "Field"

    Port(String field_type);

    ~Port();

//set value, ports_range is the rule for ports

    bool set_value(String ports_range);

    bool match_value(String port) const;

};

 

#endif
