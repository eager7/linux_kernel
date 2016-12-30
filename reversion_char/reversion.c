/****************************************************************************
 *
 * MODULE:             utils.h
 *
 * COMPONENT:          Utils interface
 *
 * REVISION:           $Revision:  1.0$
 *
 * DATED:              $Date: 2016-12-06 15:13:17 +0100 (Fri, 12 Dec 2016 $
 *
 * AUTHOR:             PCT
 *
 ****************************************************************************
 *
 * Copyright panchangtao@gmail.com 2016. All rights reserved
 *
 ***************************************************************************/
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define print(x,ARGS...) printk(KERN_DEBUG x,##ARGS)
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Changtao.Pan");
MODULE_DESCRIPTION("This Module used to reversion a str");



/****************************************************************************/
/***        Local    Functions                                            ***/
/****************************************************************************/
static int __init reversion_init(void)
{
    print("init reversion module");
	return 0;
}

static void reversion_exit(void)
{
	print("exit reversion module");
}

module_init(reversion_init);
module_exit(reversion_exit);