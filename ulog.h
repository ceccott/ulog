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

void ulog_init( ulog_lev_t level );
int ulog_set_msg(uint8_t id, char* msg);
int ulog_log(uint8_t id, ulog_lev_t level);
char* ulog_print(void);

/* - - - MACROS SECTION - - - */

#define ulog_info(id)   ulog_log(id,INFO)
#define ulog_warn(id)   ulog_log(id,WARN)
#define ulog_err(id)    ulog_log(id,ERR)


/*  // EXAMPLE USAGE
 *
 *  ulog_init(INFO);
 *
 *  ulog_set_msg(0,"message 0");
 *  ulog_set_msg(1,"message 1");
 *  ulog_set_msg(2,"message 2");
 *
 *  from ISR -> ulog_log(0, INFO);
 *  from ISR -> ulog_log(1, WARN);
 *  from ISR -> ulog_err(2);
 *
 *
 *  from main loop ->
 *
 *  char* buff = NULL;
 *  do {
 *      buff = ulog_print();
 *      if (buff != NULL)
 *          UART_TX(buff);
 *  } while (buff != NULL);
 *
 */

#endif /* ifndef ULOG_H_ */
