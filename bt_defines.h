#ifndef BT_DEFINES
#define BT_DEFINES


/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2004-2010  Marcel Holtmann <marcel@holtmann.org>
 *
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/*
  Message sequence chart of streaming sequence for A2DP transport

  Audio daemon			User
                on snd_pcm_open
                <--BT_GET_CAPABILITIES_REQ

  BT_GET_CAPABILITIES_RSP-->

                on snd_pcm_hw_params
                <--BT_SETCONFIGURATION_REQ

  BT_SET_CONFIGURATION_RSP-->

                on snd_pcm_prepare
                <--BT_START_STREAM_REQ

  <Moves to streaming state>
  BT_START_STREAM_RSP-->

  BT_NEW_STREAM_IND -->

                <  streams data >
                ..........

                on snd_pcm_drop/snd_pcm_drain

                <--BT_STOP_STREAM_REQ

  <Moves to open state>
  BT_STOP_STREAM_RSP-->

                on IPC close or appl crash
  <Moves to idle>

 */


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define BT_SUGGESTED_BUFFER_SIZE   512
#define BT_IPC_SOCKET_NAME "\0/org/bluez/audio"

/* Generic message header definition, except for RESPONSE messages */
typedef struct {
    uint8_t type;
    uint8_t name;
    uint16_t length;
} __attribute__ ((packed)) bt_audio_msg_header_t;

typedef struct {
    bt_audio_msg_header_t h;
    uint8_t posix_errno;
} __attribute__ ((packed)) bt_audio_error_t;

/* Message types */
#define BT_REQUEST			0
#define BT_RESPONSE			1
#define BT_INDICATION			2
#define BT_ERROR			3

/* Messages names */
#define BT_GET_CAPABILITIES		0
#define BT_OPEN				1
#define BT_SET_CONFIGURATION		2
#define BT_NEW_STREAM			3
#define BT_START_STREAM			4
#define BT_STOP_STREAM			5
#define BT_CLOSE			6
#define BT_CONTROL			7
#define BT_DELAY_REPORT			8

#define BT_CAPABILITIES_TRANSPORT_A2DP	0
#define BT_CAPABILITIES_TRANSPORT_SCO	1
#define BT_CAPABILITIES_TRANSPORT_ANY	2

#define BT_CAPABILITIES_ACCESS_MODE_READ	1
#define BT_CAPABILITIES_ACCESS_MODE_WRITE	2
#define BT_CAPABILITIES_ACCESS_MODE_READWRITE	3

#define BT_FLAG_AUTOCONNECT	1

struct bt_get_capabilities_req {
    bt_audio_msg_header_t	h;
    char			source[18];	/* Address of the local Device */
    char			destination[18];/* Address of the remote Device */
    char			object[128];	/* DBus object path */
    uint8_t			transport;	/* Requested transport */
    uint8_t			flags;		/* Requested flags */
    uint8_t			seid;		/* Requested capability configuration */
} __attribute__ ((packed));

/**
 * SBC Codec parameters as per A2DP profile 1.0 § 4.3
 */

/* A2DP seid are 6 bytes long so HSP/HFP are assigned to 7-8 bits */
#define BT_A2DP_SEID_RANGE			(1 << 6) - 1

#define BT_A2DP_SBC_SOURCE			0x00
#define BT_A2DP_SBC_SINK			0x01
#define BT_A2DP_MPEG12_SOURCE			0x02
#define BT_A2DP_MPEG12_SINK			0x03
#define BT_A2DP_MPEG24_SOURCE			0x04
#define BT_A2DP_MPEG24_SINK			0x05
#define BT_A2DP_ATRAC_SOURCE			0x06
#define BT_A2DP_ATRAC_SINK			0x07
#define BT_A2DP_UNKNOWN_SOURCE			0x08
#define BT_A2DP_UNKNOWN_SINK			0x09

#define BT_SBC_SAMPLING_FREQ_16000		(1 << 3)
#define BT_SBC_SAMPLING_FREQ_32000		(1 << 2)
#define BT_SBC_SAMPLING_FREQ_44100		(1 << 1)
#define BT_SBC_SAMPLING_FREQ_48000		1

#define BT_A2DP_CHANNEL_MODE_MONO		(1 << 3)
#define BT_A2DP_CHANNEL_MODE_DUAL_CHANNEL	(1 << 2)
#define BT_A2DP_CHANNEL_MODE_STEREO		(1 << 1)
#define BT_A2DP_CHANNEL_MODE_JOINT_STEREO	1

#define BT_A2DP_BLOCK_LENGTH_4			(1 << 3)
#define BT_A2DP_BLOCK_LENGTH_8			(1 << 2)
#define BT_A2DP_BLOCK_LENGTH_12			(1 << 1)
#define BT_A2DP_BLOCK_LENGTH_16			1

#define BT_A2DP_SUBBANDS_4			(1 << 1)
#define BT_A2DP_SUBBANDS_8			1

#define BT_A2DP_ALLOCATION_SNR			(1 << 1)
#define BT_A2DP_ALLOCATION_LOUDNESS		1

#define BT_MPEG_SAMPLING_FREQ_16000		(1 << 5)
#define BT_MPEG_SAMPLING_FREQ_22050		(1 << 4)
#define BT_MPEG_SAMPLING_FREQ_24000		(1 << 3)
#define BT_MPEG_SAMPLING_FREQ_32000		(1 << 2)
#define BT_MPEG_SAMPLING_FREQ_44100		(1 << 1)
#define BT_MPEG_SAMPLING_FREQ_48000		1

#define BT_MPEG_LAYER_1				(1 << 2)
#define BT_MPEG_LAYER_2				(1 << 1)
#define BT_MPEG_LAYER_3				1

#define BT_HFP_CODEC_PCM			0x00

#define BT_PCM_FLAG_NREC			0x01
#define BT_PCM_FLAG_PCM_ROUTING			0x02

#define BT_WRITE_LOCK				(1 << 1)
#define BT_READ_LOCK				1


#define MAX_BITPOOL 64
#define MIN_BITPOOL 2



typedef struct {
    uint8_t channel_mode:4;
    uint8_t frequency:4;
    uint8_t allocation_method:2;
    uint8_t subbands:2;
    uint8_t block_length:4;
    uint8_t min_bitpool;
    uint8_t max_bitpool;
} __attribute__ ((packed)) a2dp_sbc_t;


#ifdef __cplusplus
}
#endif

#endif // BT_DEFINES

