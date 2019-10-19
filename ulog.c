#include <stdio.h>
#include "ulog.h"
#include "string.h"

// main msg buffer
char ulog_msg_buff[ULOG_MSG_MAX_N][ULOG_MSG_MAX_LEN] = {};
volatile ulog_log_t ulog_msg_q[ULOG_MSG_Q_MAX] = {};
ulog_lev_t print_level = INFO;

volatile uint8_t q_head;
volatile uint8_t q_tail;

void ulog_init(ulog_lev_t level)
{
    print_level = level;

    // init queue
    q_head = 0;
    q_tail = 0;

}

int ulog_set_msg(uint8_t id, char* msg)
{
    uint8_t len = strlen(msg);

    if(len > ULOG_MSG_MAX_LEN)
        return -1;

    if(id >= ULOG_MSG_MAX_N)
        return -1;

    strcpy(ulog_msg_buff[id], msg);

    return 0;
}

int ulog_log(uint8_t id, ulog_lev_t level)
{
    ulog_msg_q[ q_tail++ ].msg = id;

    if (q_tail == ULOG_MSG_Q_MAX) { // queue is full
       return -1;
    }

    return 0;
}

char* ulog_print(void)
{
    if (q_head == q_tail) { // if queue is empty
       return NULL;
       if (q_tail == ULOG_MSG_Q_MAX) //if end buffer
           q_tail = q_head = 0;      //reset queue buffer

    }

    return ulog_msg_buff[ ulog_msg_q[  q_head++ ].msg ];
}

