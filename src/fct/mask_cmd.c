#include <string.h>
#include <stdio.h>
#include "zebra.h"
#include "version.h"
#include "getopt.h"
#include "command.h"
#include "filter.h"
#include "prefix.h"
#include "privs.h"
#include "packet.h"
#include "luna_types.h"
#include "luna_util.h"

#include "bts_cnt.h"


#include "mask.h"
#include "mask_cmd.h"

DEFUN(mask_add,
      mask_add_cmd,
      "mask add <0-63> MASK ACT",
      MASK_EXPR)
{
    berr rv;

    int index = strtoul(argv[0], NULL, 0);
	
    int mask =  strtoul(argv[1], NULL, 0);

    rule_act_t act;
    memset(&act, 0, sizeof(rule_act_t));

	if(rule_act_parse(&argv[2], argc - 2, &act))
    {

        return CMD_ERR_NO_MATCH;
    }
    
    rv =  mask_rule_add(index, mask, &act);
 
	if(rv != E_SUCCESS)
	{
		 vty_out(vty, "Failed To add Url rule %s", VTY_NEWLINE);
		 return 0;
	}
	return 0;
}

ALIAS (mask_add,
       mask_add_param_cmd,
       "mask add <0-63> MASK ACT PARAM",
       MASK_EXPR)

ALIAS (mask_add,
       mask_add_param_rate_cmd,
       "mask add <0-63> MASK ACT PARAM <1-100>",
       MASK_EXPR)

DEFUN(mask_del,
      mask_del_cmd,
      "mask del <0-63>",
      MASK_EXPR)
{


    int index = strtoul(argv[0], NULL, 0 );
    
    return mask_rule_del(index);
}


DEFUN(mask_del_all,
      mask_del_all_cmd,
      "mask del all",
      MASK_EXPR)
{
    int i;
    for(i=0; i <MAX_MASK_RULE; i++)
    {
        mask_rule_del(i);
    }
    return 0;
}



DEFUN(show_mask_all,
      show_mask_all_cmd,
      "show mask",
      MASK_EXPR)
{

    mask_rule_t *rule = NULL;
    int i;
    char act_str[LUNA_ACL_STR_SZ];

    memset(act_str, 0, LUNA_ACL_STR_SZ);
    
    vty_out(vty, "%-6s %-16s %-10s        %s%s", "ID", "CNT", "MASK", "ACTIONS", VTY_NEWLINE);
    for(i=0; i < MAX_MASK_RULE; i++)
    {
        rule = mask_rule_get(i);

		if(rule && rule->used)
		{
            rule_act_string(&rule->act, act_str);
        	vty_out(vty, "%-6d %-16ld 0x%.8x        %s%s", rule->id, 
                   (uint64_t) rule->act.cnt, rule->mask, act_str, VTY_NEWLINE);    
		}
        
    }
    return 0;
}

void mask_cmd_config_write(struct vty *vty)
{

    mask_rule_t *rule = NULL;
    int i;

    char act_str[LUNA_ACL_STR_SZ];
    memset(act_str, 0, LUNA_ACL_STR_SZ);

    for(i=0; i < MAX_MASK_RULE; i++)
    {
        rule = mask_rule_get(i);

		if(rule && rule->used)
		{
            rule_act_string(&rule->act, act_str);
        	vty_out(vty, "mask add %d 0x%x %s%s", rule->id, rule->mask, act_str, VTY_NEWLINE);    
		}
    }
    return ;
}


void mask_cmdline_init(void)
{
	install_element(CMD_NODE, &mask_add_cmd);
    install_element(CMD_NODE, &mask_add_param_cmd);
    install_element(CMD_NODE, &mask_add_param_rate_cmd);
	install_element(CMD_NODE, &mask_del_cmd);
	install_element(CMD_NODE, &mask_del_all_cmd);
    install_element(CMD_NODE, &show_mask_all_cmd);

    return ;
}




