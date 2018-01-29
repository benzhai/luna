/**************************************************************
* Copyright (C) 2014-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-10-11 18:09
* @Author: SamLiu - shan3275@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef __ADT_CMD_H__
#define __ADT_CMD_H__

#include "vty.h"

void adt_cmdline_init(void);

void adt_cmd_config_write(struct vty *vty);

#endif /* __ADT_CMD_H__ */
