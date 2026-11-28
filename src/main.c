#include "kernel/stdtypes.h"
#include "kernel.h"

int main() {

    u32 result = kernel();
    if(result){
        // some kernel error
    }

    return 0;
}
