#include <stdio.h>
#include "ulog.h"
#include "string.h"

#define MAIN_TEST

// main msg buffer
char ulog_msg_buff[ULOG_MSG_MAX_N][ULOG_MSG_MAX_LEN] = {};
char* ulog_msg_lev[4] = {"","INFO:","WARN:","ERR:"};
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
    if (level >= print_level) { // filter by level

    ulog_msg_q[ q_tail++ ].msg = id;

    if (q_tail == ULOG_MSG_Q_MAX) { // queue is full
       return -1;
    }

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

#ifdef MAIN_TEST

int main(int argc, char *argv[])
{
    ulog_init(ERR);

    ulog_set_msg(0,"message 0");
    ulog_set_msg(1,"message 1");
    ulog_set_msg(2,"message 2");

    ulog_log(0,INFO);
    ulog_log(0,WARN);
    ulog_log(1,ERR);

    char* buff = NULL;
    do {
        buff = ulog_print();

        if (buff != NULL)
            printf("%s\n", buff);

    } while (buff != NULL);

    return 0;
}

#endif
