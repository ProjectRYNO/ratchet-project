#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_startup);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_shutdown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_set_default_options);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_create);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_destroy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_send_to);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_vsend_to);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_send_echo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_receive);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_receive_from);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_receive_echo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_local_ip);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_broadcast_ip);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_host_by_name);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_display_state);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_metrics);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_interface_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_local_port);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_is_connected);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_host_by_name_nb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_generate_lookup_query);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_resend_lookup_query);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_check_for_query_response);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_process_response_header);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_skip_query_section);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_process_rr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_isdigit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_new_channel_id);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_release_channel_id);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_is_valid_channel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_init);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_add_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_metric_update_single);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_linkaddress_setnull);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_linkaddress_isnull);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_linkaddress_isequal);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_linkaddress_tostr);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_linkaddress_toext);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_linkaddress_toint);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_echo_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_echo_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_echo_shutdown);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_comm/src/rt_comm", rt_comm_get_dns_servers);
