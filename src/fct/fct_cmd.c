#include "net_cmd.h"
#include "url_cmd.h"
#include "mask_cmd.h"

/*
 * fct module cmdline register and init 
 *
 * */
void fct_cmdline_init(void)
{
    net_cmdline_init();
    url_cmdline_init();
    mask_cmdline_init();

    return ;
}

void fct_cmd_config_write(struct vty *vty)
{
    net_cmd_config_write(vty);
    url_cmd_config_write(vty);
    mask_cmd_config_write(vty);
}

/* End of file */
