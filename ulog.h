#ifndef ULOG_H_
#define ULOG_H_

#include "stdint.h"

#define ULOG_MSG_Q_MAX      20
#define ULOG_MSG_MAX_N      10
#define ULOG_MSG_MAX_LEN    20

typedef enum {
    EMPTY=0,
    INFO=1,
    WARN=2,
    ERR=3
} ulog_lev_t;

typedef struct {
    ulog_lev_t level;
    uint8_t msg;
} ulog_log_t;

extern char ulog_msg_buff[ULOG_MSG_MAX_N][ULOG_MSG_MAX_LEN];

void ulog_init();
int ulog_set_msg(uint8_t id, char* msg);
int ulog_log(uint8_t id, ulog_lev_t level);
char* ulog_print(void);

#endif /* ifndef ULOG_H_ */
