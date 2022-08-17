#include <bike.h>

int main( void )
    {
        bike_init();
        while (1)
            {
                bike_loop();
            }
    }
