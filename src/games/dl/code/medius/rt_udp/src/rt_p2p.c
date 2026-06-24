#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", NetUsePeerToPeer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_resolve_interface);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_create);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_destroy);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_current_address_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_address);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_my_address);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_my_peer_index);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_host_index);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_virtual_port);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_buffer_stats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_buffer_stats);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_send_aggregation);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_host);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_incoming_peer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_connect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_disconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_tick);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_list);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_receive_broadcasts);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_to);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_max_peers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_max_peers);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_overlay_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_join_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_quit_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_quit_all_overlays);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_ignore_peer_in_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_overlay_peer_count);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_is_peer_in_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_pack_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_unpack_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_udp_event_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_udp_data_cb);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_peer_info);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_connect_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_connected_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_timeout_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_closed_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_reset_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_handle_error_event);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_by_address);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_by_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_my_peer_status);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_find_free_peer_index);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_fill_new_peer_struct);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_internal_message);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_new_peer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_coordinate_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_connect_complete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_broadcast_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_connection_detached);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_broadcast_disconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_local_broadcast_test);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_overlay_type);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_join_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_join_response);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_quit_overlay);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_ignore_update);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_grid_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_complete_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_local_broadcast_tests);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_isend);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_isend_list);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_my_broadcast_flag);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_generic_disconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_determine_new_host);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_connection_detached_to_host);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_broadcast_disconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_notify_peers_disconnect_forwarding);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_notify_peers_disconnect);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_save_backlog_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_find_backlog_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_timeout_backlog_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_generate_grid_fill_empties);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_generate_grid_add_peer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_generate_grid);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_peer_grid_edges);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_update_grid);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_token_msg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_token_list_msg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_token_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", FUN_01ebc970);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_timebase_query);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_timebase_data);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_game_session_key);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_get_latency_info);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_host_invactivity_timeout_session);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_host_inactivity_timeout_connection);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_set_peer_update_bit);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_new_peer_info);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_send_peer_updates);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_reset_peer_info);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/rt_udp/src/rt_p2p", rt_p2p_process_peer_host_query);
