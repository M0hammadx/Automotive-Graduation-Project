/** incomplete Dcm configuration code file used as a test to PDUR module */

#include "Dcm.h"

/*
 * DSL configurations
 */
const Dcm_DslType Dsl = {
		.DslProtocol = NULL,
};

/*
 * DCM configurations
 */
const Dcm_ConfigType DCM_Config = {
		.Dsl = &Dsl
};
