#ifndef __ADP_CMD_H__
#define __ADP_CMD_H__

#include "vty.h"

void adp_cmdline_init(void);

void adp_cmd_config_write(struct vty *vty);

#endif /* __ADP_CMD_H__ */