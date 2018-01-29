#include "adt_cmd.h"
#include "adp_cmd.h"

/*
 * acl module cmdline register and init 
 *
 * */
void acl_cmdline_init(void)
{
    adt_cmdline_init();
    adp_cmdline_init();

    return ;
}

void acl_cmd_config_write(struct vty *vty)
{
    adt_cmd_config_write(vty);
    adp_cmd_config_write(vty);

    return ;
}

/* End of file */
