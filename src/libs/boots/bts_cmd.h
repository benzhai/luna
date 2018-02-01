#ifndef __BTS_CMD_H__
#define __BTS_CMD_H__

#include "vty.h"

void bts_cmdline_init(void);
void bts_cmd_config_write(struct vty *vty);
void bts_stat_log(void);

#endif /* end of __BTS_CMD_H__ */
