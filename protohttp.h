/*-
 * SSLsplit - transparent SSL/TLS interception
 * https://www.roe.ch/SSLsplit
 *
 * Copyright (c) 2009-2018, Daniel Roethlisberger <daniel@roe.ch>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PROTOHTTP_H
#define PROTOHTTP_H

#include "pxyconn.h"
#include "pxythrmgr.h"

#include <event2/buffer.h>

typedef struct protohttp_ctx protohttp_ctx_t;

struct protohttp_ctx {
	unsigned int seen_req_header : 1; /* 0 until request header complete */
	unsigned int seen_resp_header : 1;  /* 0 until response hdr complete */
	unsigned int sent_http_conn_close : 1;   /* 0 until Conn: close sent */
	unsigned int ocsp_denied : 1;                /* 1 if OCSP was denied */
	unsigned int seen_req_header_on_entry : 1;   /* save seen_req_header */
	unsigned int seen_resp_header_on_entry : 1;  /* save seen_resp_header */

	/* log strings from HTTP request */
	char *http_method;
	char *http_uri;
	char *http_host;
	char *http_content_type;

	/* log strings from HTTP response */
	char *http_status_code;
	char *http_status_text;
	char *http_content_length;
};

int protohttp_setup(pxy_conn_ctx_t *);
int protohttps_setup(pxy_conn_ctx_t *);
void protohttp_free(pxy_conn_ctx_t *);

void protohttp_filter_request_header(struct evbuffer *, struct evbuffer *, pxy_conn_ctx_t *, int);
void protohttp_filter_response_header(struct evbuffer *, struct evbuffer *, pxy_conn_ctx_t *);

#endif /* !PROTOHTTP_H */

/* vim: set noet ft=c: */
