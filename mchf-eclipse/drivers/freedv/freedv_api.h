/*---------------------------------------------------------------------------*\

  FILE........: freedv_api.h
  AUTHOR......: David Rowe
  DATE CREATED: August 2014

  Library of API functions that implement FreeDV "modes", useful for
  embedding FreeDV in other programs.  Please see the documentation
  for each function in freedv_api.c, and the sample freedv_tx.c and
  freedv_rx.c programs.

\*---------------------------------------------------------------------------*/

/*
  Copyright (C) 2014 David Rowe

  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1, as
  published by the Free Software Foundation.  This program is
  distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifdef __cplusplus
  extern "C" {
#endif

#ifndef __FREEDV__

// This declares a single-precision (float) complex number
#include <sys/types.h>
#include "comp.h"

#define FREEDV_MODE_1600        0
#define FREEDV_MODE_700         1
#define FREEDV_MODE_700B        2
#define FREEDV_MODE_2400A       3
#define FREEDV_MODE_2400B       4
#define FREEDV_MODE_800XA       5

struct freedv;

/* Called when text message char is decoded */
typedef void (*freedv_callback_rx)(void *, char);
/* Called when new text message char is needed */
typedef char (*freedv_callback_tx)(void *);
typedef void (*freedv_calback_error_pattern)
       (void *error_pattern_callback_state, short error_pattern[], int sz_error_pattern);

/* Protocol bits are packed MSB-first */
/* Called when a frame containing protocol data is decoded */
typedef void (*freedv_callback_protorx)(void *, char *);
/* Called when a frame containing protocol data is to be sent */
typedef void (*freedv_callback_prototx)(void *, char *);

/* Data packet callbacks */
/* Called when a packet has been received */
typedef void (*freedv_callback_datarx)(void *, unsigned char *packet, size_t size);
/* Called when a new packet can be send */
typedef void (*freedv_callback_datatx)(void *, unsigned char *packet, size_t *size);


// FreeDV API functions:
// open, close
struct freedv *freedv_open(int mode);
void freedv_close   (struct freedv *freedv);
// Transmit
void freedv_tx      (struct freedv *freedv, short mod_out[], short speech_in[]);
void freedv_comptx  (struct freedv *freedv, COMP  mod_out[], short speech_in[]);
void freedv_codectx (struct freedv *f, short mod_out[], unsigned char *packed_codec_bits);
void freedv_datatx  (struct freedv *f, short mod_out[]);
int  freedv_data_ntxframes (struct freedv *freedv);
// Receive
int freedv_nin      (struct freedv *freedv);
int freedv_rx       (struct freedv *freedv, short speech_out[], short demod_in[]);
int freedv_floatrx  (struct freedv *freedv, short speech_out[], float demod_in[]);
int freedv_comprx   (struct freedv *freedv, short speech_out[], COMP  demod_in[]);
int freedv_codecrx  (struct freedv *freedv, unsigned char *packed_codec_bits, short demod_in[]);
// Set parameters
void freedv_set_callback_txt            (struct freedv *freedv, freedv_callback_rx rx, freedv_callback_tx tx, void *callback_state);
void freedv_set_callback_protocol       (struct freedv *freedv, freedv_callback_protorx rx, freedv_callback_prototx tx, void *callback_state);
void freedv_set_callback_data         (struct freedv *freedv, freedv_callback_datarx datarx, freedv_callback_datatx datatx, void *callback_state);
void freedv_set_test_frames			    (struct freedv *freedv, int test_frames);
void freedv_set_smooth_symbols		    (struct freedv *freedv, int smooth_symbols);
void freedv_set_squelch_en			    (struct freedv *freedv, int squelch_en);
void freedv_set_snr_squelch_thresh	    (struct freedv *freedv, float snr_squelch_thresh);
void freedv_set_clip	                (struct freedv *freedv, int val);
void freedv_set_total_bit_errors    	(struct freedv *freedv, int val);
void freedv_set_total_bits              (struct freedv *freedv, int val);
void freedv_set_callback_error_pattern  (struct freedv *freedv, freedv_calback_error_pattern cb, void *state);
void freedv_set_varicode_code_num       (struct freedv *freedv, int val);
void freedv_set_data_header             (struct freedv *freedv, unsigned char *header);
int freedv_set_alt_modem_samp_rate      (struct freedv *freedv, int samp_rate);

// Get parameters
struct MODEM_STATS;
int freedv_get_version(void);
int freedv_get_mode                 (struct freedv *freedv);
void freedv_get_modem_stats         (struct freedv *freedv, int *sync, float *snr_est);
void freedv_get_modem_extended_stats(struct freedv *freedv, struct MODEM_STATS *stats);
int freedv_get_test_frames			(struct freedv *freedv);
int freedv_get_n_speech_samples		(struct freedv *freedv);
int freedv_get_modem_sample_rate	(struct freedv *freedv);
int freedv_get_n_max_modem_samples	(struct freedv *freedv);
int freedv_get_n_nom_modem_samples	(struct freedv *freedv);
int freedv_get_total_bits			(struct freedv *freedv);
int freedv_get_total_bit_errors		(struct freedv *freedv);
int freedv_get_sync		            (struct freedv *freedv);
struct FSK * freedv_get_fsk(struct freedv *f);
struct CODEC2 *freedv_get_codec2	(struct freedv *freedv);
int freedv_get_n_codec_bits             (struct freedv *freedv);
int freedv_get_sz_error_pattern     (struct freedv *freedv);
int freedv_get_protocol_bits        (struct freedv *freedv);
#endif

#ifdef __cplusplus
}
#endif
