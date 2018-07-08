#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_52_00_12/packages;C:/ti/ccsv7/ccs_base;C:/Users/Mohab/workspace_v7_new/ECUS_RTOS_UNDER_DEVELOP/.config
override XDCROOT = C:/ti/xdctools_3_50_02_20_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_52_00_12/packages;C:/ti/ccsv7/ccs_base;C:/Users/Mohab/workspace_v7_new/ECUS_RTOS_UNDER_DEVELOP/.config;C:/ti/xdctools_3_50_02_20_core/packages;..
HOSTOS = Windows
endif
