/*
o89 * ldmsd_request.h
 *
 *  Created on: Jun 24, 2016
 *      Author: nichamon
 */

#ifndef LDMS_SRC_LDMSD_LDMSD_REQUEST_H_
#define LDMS_SRC_LDMSD_LDMSD_REQUEST_H_

enum ldmsd_request {
	LDMSD_CLI_REQ = 0x1,
	LDMSD_EXAMPLE_REQ,
	LDMSD_PRDCR_ADD_REQ = 0x100,
	LDMSD_PRDCR_DEL_REQ,
	LDMSD_PRDCR_START_REQ,
	LDMSD_PRDCR_STOP_REQ,
	LDMSD_PRDCR_STATUS_REQ,
	LDMSD_PRDCR_START_REGEX_REQ,
	LDMSD_PRDCR_STOP_REGEX_REQ,
	LDMSD_PRDCR_SET_REQ,
	LDMSD_STRGP_ADD_REQ = 0x200,
	LDMSD_STRGP_DEL_REQ,
	LDMSD_STRGP_START_REQ,
	LDMSD_STRGP_STOP_REQ,
	LDMSD_STRGP_STATUS_REQ,
	LDMSD_STRGP_PRDCR_ADD_REQ,
	LDMSD_STRGP_PRDCR_DEL_REQ,
	LDMSD_STRGP_METRIC_ADD_REQ,
	LDMSD_STRGP_METRIC_DEL_REQ,
	LDMSD_UPDTR_ADD_REQ = 0x300,
	LDMSD_UPDTR_DEL_REQ,
	LDMSD_UPDTR_START_REQ,
	LDMSD_UPDTR_STOP_REQ,
	LDMSD_UPDTR_STATUS_REQ,
	LDMSD_UPDTR_PRDCR_ADD_REQ,
	LDMSD_UPDTR_PRDCR_DEL_REQ,
	LDMSD_UPDTR_MATCH_ADD_REQ,
	LDMSD_UPDTR_MATCH_DEL_REQ,
	LDMSD_SMPLR_ADD_REQ = 0X400,
	LDMSD_SMPLR_DEL_REQ,
	LDMSD_SMPLR_START_REQ,
	LDMSD_SMPLR_STOP_REQ,
	LDMSD_PLUGN_ADD_REQ = 0x500,
	LDMSD_PLUGN_DEL_REQ,
	LDMSD_PLUGN_START_REQ,
	LDMSD_PLUGN_STOP_REQ,
	LDMSD_PLUGN_STATUS_REQ,
	LDMSD_PLUGN_LOAD_REQ,
	LDMSD_PLUGN_TERM_REQ,
	LDMSD_PLUGN_CONFIG_REQ,
};

enum ldmsd_request_attr {
	/* Common attribute */
	LDMSD_ATTR_NAME = 1,
	LDMSD_ATTR_INTERVAL,
	LDMSD_ATTR_OFFSET,
	LDMSD_ATTR_REGEX,
	LDMSD_ATTR_TYPE,
	LDMSD_ATTR_PRODUCER,
	LDMSD_ATTR_INSTANCE,
	LDMSD_ATTR_XPRT,
	LDMSD_ATTR_HOST,
	LDMSD_ATTR_PORT,
	LDMSD_ATTR_MATCH,
	LDMSD_ATTR_PLUGIN,
	LDMSD_ATTR_CONTAINER,
	LDMSD_ATTR_SCHEMA,
	LDMSD_ATTR_METRIC,
};

#endif /* LDMS_SRC_LDMSD_LDMSD_REQUEST_H_ */
