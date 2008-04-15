
#ifndef __RBLM_PRIVATE_H__
#define __RBLM_PRIVATE_H__

#include <glib.h>
#include <ruby.h>
#include <loudmouth/loudmouth.h>

#define GBOOL2RVAL(x) (x == TRUE ? Qtrue : Qfalse)
#define RVAL2GBOOL(x) RTEST(x)

#define LMMESSAGENODE2RVAL(x) (rb_lm_message_node_to_ruby_object(x))
#define LMSSL2RVAL(x) (rb_lm_ssl_to_ruby_object(x))
#define LMPROXY2RVAL(x) (rb_lm_proxy_to_ruby_object(x))
#define LMMESSAGE2RVAL(x) (rb_lm_message_to_ruby_object(x))

gboolean            rb_lm__is_kind_of (VALUE object, VALUE klass);

VALUE               rb_lm_message_to_ruby_object      (LmMessage     *m);
VALUE               rb_lm_message_node_to_ruby_object (LmMessageNode *node);
VALUE               rb_lm_ssl_to_ruby_object          (LmSSL         *ssl);
VALUE               rb_lm_proxy_to_ruby_object        (LmProxy       *proxy);

LmConnection *      rb_lm_connection_from_ruby_object         (VALUE obj);
LmMessage *         rb_lm_message_from_ruby_object            (VALUE obj);
LmMessageNode *     rb_lm_message_node_from_ruby_object       (VALUE obj);
LmSSL *             rb_lm_ssl_from_ruby_object                (VALUE obj);
LmProxy *           rb_lm_proxy_from_ruby_object              (VALUE obj);

LmConnectionState   rb_lm_connection_state_from_ruby_object   (VALUE obj);
LmDisconnectReason  rb_lm_disconnect_reason_from_ruby_object  (VALUE obj);
LmMessageType       rb_lm_message_type_from_ruby_object       (VALUE obj);
LmMessageSubType    rb_lm_message_sub_type_from_ruby_object   (VALUE obj);
LmProxyType         rb_lm_proxy_type_from_ruby_object         (VALUE obj);
LmCertificateStatus rb_lm_certificate_status_from_ruby_object (VALUE obj);
LmSSLStatus         rb_lm_ssl_status_from_ruby_object         (VALUE obj);
LmSSLResponse       rb_lm_ssl_response_from_ruby_object       (VALUE obj);

#endif /* __RBLM_PRIVATE_H__ */

