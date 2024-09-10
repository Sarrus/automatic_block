#include "pico/stdlib.h"

#define RED_LED_PIN 16
#define AAT_PIN 17

#define BLOCK_CLEAR_SETTLE_TIME 100

int main(void)
{
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_put(RED_LED_PIN, true);

    gpio_init(AAT_PIN);
    gpio_set_dir(AAT_PIN, GPIO_IN);

    uint64_t blockClearedAt = 0;

    while(1)
    {
        uint64_t currentTime = to_ms_since_boot(get_absolute_time());

        if(gpio_get(AAT_PIN))
        {
            blockClearedAt = 0;
            gpio_put(RED_LED_PIN, true);
        }
        else if(blockClearedAt)
        {
            if(currentTime > blockClearedAt + BLOCK_CLEAR_SETTLE_TIME)
            {
                gpio_put(RED_LED_PIN, false);
            }
        }
        else
        {
            blockClearedAt = currentTime;
        }
    }
}
