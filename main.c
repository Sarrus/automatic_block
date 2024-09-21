#include "pico/stdlib.h"

#define BLOCK_CLEAR_SETTLE_TIME 1000
#define BLOCK_COUNT 4

// Colours represent the signal at the entry to the block
struct {
    uint circuitPin;
    uint redPin;
    uint yellowPin;
    uint greenPin;
    uint secondYellowPin;
    uint64_t blockClearedAt;
    bool occupied;
} blocks[BLOCK_COUNT] =
{
    [0].circuitPin = 19,
    [0].redPin = 15,
    [0].yellowPin = 14,
    [0].greenPin = 13,
    [0].secondYellowPin = 12,
    [0].blockClearedAt = 0,
    [0].occupied = true,

    [1].circuitPin = 18,
    [1].redPin = 11,
    [1].yellowPin = 10,
    [1].greenPin = 9,
    [1].secondYellowPin = 8,
    [1].blockClearedAt = 0,
    [1].occupied = true,

    [2].circuitPin = 17,
    [2].redPin = 7,
    [2].yellowPin = 6,
    [2].greenPin = 5,
    [2].secondYellowPin = 4,
    [2].blockClearedAt = 0,
    [2].occupied = true,

    [3].circuitPin = 16,
    [3].redPin = 3,
    [3].yellowPin = 2,
    [3].greenPin = 1,
    [3].secondYellowPin = 0,
    [3].blockClearedAt = 0,
    [3].occupied = true,
};

void setRed(int blockId)
{
    gpio_put(blocks[blockId].redPin, true);
    gpio_put(blocks[blockId].yellowPin, false);
    gpio_put(blocks[blockId].greenPin, false);
    gpio_put(blocks[blockId].secondYellowPin, false);
}

void setYellow(int blockId)
{
    gpio_put(blocks[blockId].redPin, false);
    gpio_put(blocks[blockId].yellowPin, true);
    gpio_put(blocks[blockId].greenPin, false);
    gpio_put(blocks[blockId].secondYellowPin, false);
}

void setDoubleYellow(int blockId)
{
    gpio_put(blocks[blockId].redPin, false);
    gpio_put(blocks[blockId].yellowPin, true);
    gpio_put(blocks[blockId].greenPin, false);
    gpio_put(blocks[blockId].secondYellowPin, true   );
}

void setGreen(int blockId)
{
    gpio_put(blocks[blockId].redPin, false);
    gpio_put(blocks[blockId].yellowPin, false);
    gpio_put(blocks[blockId].greenPin, true);
    gpio_put(blocks[blockId].secondYellowPin, false);
}

int main(void)
{
    for(int i = 0; i < BLOCK_COUNT; i++)
    {
        gpio_init(blocks[i].circuitPin);
        gpio_init(blocks[i].redPin);
        gpio_init(blocks[i].yellowPin);
        gpio_init(blocks[i].greenPin);
        gpio_init(blocks[i].secondYellowPin);

        gpio_set_dir(blocks[i].circuitPin, GPIO_IN);
        gpio_pull_up(blocks[i].circuitPin);

        gpio_set_dir(blocks[i].redPin, GPIO_OUT);
        gpio_set_dir(blocks[i].yellowPin, GPIO_OUT);
        gpio_set_dir(blocks[i].greenPin, GPIO_OUT);
        gpio_set_dir(blocks[i].secondYellowPin, GPIO_OUT);
    }

    while(1)
    {
        uint64_t currentTime = to_ms_since_boot(get_absolute_time());

        for(int i = 0; i < BLOCK_COUNT; i++)
        {
            if(!gpio_get(blocks[i].circuitPin))
            {
                blocks[i].blockClearedAt = 0;
                blocks[i].occupied = true;
            }
            else if(blocks[i].blockClearedAt)
            {
                if(currentTime > blocks[i].blockClearedAt + BLOCK_CLEAR_SETTLE_TIME)
                {
                    blocks[i].occupied = false;
                }
            }
            else
            {
                blocks[i].blockClearedAt = currentTime;
            }
        }

        for(int i = 0; i < BLOCK_COUNT; i++)
        {
            if(blocks[i].occupied)
            {
                setRed(i);
            }
            else
            {
                if(i > 0 && blocks[i-1].occupied)
                {
                    setYellow(i);
                }
                else if(i > 1 && blocks[i-2].occupied)
                {
                    setDoubleYellow(i);
                }
                else
                {
                    setGreen(i);
                }
            }
        }
    }
}
