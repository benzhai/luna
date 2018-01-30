#ifndef __ITF_CMD_H__
#define __ITF_CMD_H__

#include "vty.h"

void itf_cmd_config_write(struct vty *vty);

/*
 * vsr module cmdline register and init 
 *
 * */
void itf_cmdline_init(void);


#endif /* __ITF_CMD_H__ */
