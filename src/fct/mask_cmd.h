#ifndef __MASK_CMD_H
#define __MASK_CMD_H

#define MASK_EXPR "mask expr\n"

void mask_cmdline_init(void);

void mask_cmd_config_write(struct vty *vty);

#endif