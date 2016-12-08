#include "types.c"
#include "stack.h"


int main() {
    // gotta get set up

    TypeVal * d1 = newTypeVal(Double);
    setDoubleVal(d1, 1.2864);

    printf("getDoubleVal(d1) = %lf\n", getDoubleVal(d1));

}
