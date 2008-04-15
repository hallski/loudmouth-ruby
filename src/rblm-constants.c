#include "rblm.h"

VALUE lm_mMessageType;
VALUE lm_mMessageSubType;
VALUE lm_mDisconnectReason;
VALUE lm_mConnectionState;
VALUE lm_mProxyType;
VALUE lm_mCertificateStatus;
VALUE lm_mSSLStatus;
VALUE lm_mSSLResponse;

LmConnectionState
rb_lm_connection_state_from_ruby_object (VALUE obj)
{
	LmConnectionState state;

	state = FIX2INT (obj);
	if (state < LM_CONNECTION_STATE_CLOSED ||
	    state > LM_CONNECTION_STATE_AUTHENTICATED) {
		rb_raise (rb_eArgError,
			  "invalid LmConnectionState: %d (expected %d <= LmConnectionState <= %d)",
			  state, LM_CONNECTION_STATE_CLOSED, 
			  LM_CONNECTION_STATE_AUTHENTICATED);
	}

	return state;
}

LmDisconnectReason
rb_lm_disconnect_reason_from_ruby_object (VALUE obj)
{
	LmDisconnectReason reason;

	reason = FIX2INT (obj);
	if (reason < LM_DISCONNECT_REASON_OK ||
	    reason > LM_DISCONNECT_REASON_UNKNOWN) {
		rb_raise (rb_eArgError,
			  "invalid LmDisconnectReason: %d (expected %d <= LmDisconnectReason <= %d)",
			  reason, 
			  LM_DISCONNECT_REASON_OK, 
			  LM_DISCONNECT_REASON_UNKNOWN);
	}

	return reason;
}

LmMessageType
rb_lm_message_type_from_ruby_object (VALUE obj)
{
	LmMessageType type;

	type = FIX2INT (obj);
	if (type < LM_MESSAGE_TYPE_MESSAGE ||
	    type > LM_MESSAGE_TYPE_IQ) {
		rb_raise (rb_eArgError,
			  "invalid LmMessageType: %d (expected %d <= LmMessageType <= %d)",
			  type, LM_MESSAGE_TYPE_MESSAGE,
			  LM_MESSAGE_TYPE_IQ);
	}

	return type;
}

LmMessageSubType
rb_lm_message_sub_type_from_ruby_object (VALUE obj)
{
	LmMessageSubType type;

	type = FIX2INT (obj);
	if (type < LM_MESSAGE_SUB_TYPE_AVAILABLE ||
	    type > LM_MESSAGE_SUB_TYPE_ERROR) {
		rb_raise (rb_eArgError,
			  "invalid LmMessageSubType: %d (expected %d <= LmMessageSubType <= %d)",
			  type, LM_MESSAGE_SUB_TYPE_AVAILABLE,
			  LM_MESSAGE_SUB_TYPE_ERROR);
	}

	return type;
}

LmProxyType
rb_lm_proxy_type_from_ruby_object (VALUE obj)
{
	LmProxyType type;

	type = FIX2INT (obj);
	if (type < LM_PROXY_TYPE_NONE || type > LM_PROXY_TYPE_HTTP) {
		rb_raise (rb_eArgError,
			  "invalid LmProxyType: %d (expected %d <= LmProxyType <= %d)",
			  type, LM_PROXY_TYPE_NONE, LM_PROXY_TYPE_HTTP);
	}

	return type;
}

LmCertificateStatus
rb_lm_certificate_status_from_ruby_object (VALUE obj)
{
	LmCertificateStatus status;

	status = FIX2INT (obj);
	if (status < LM_CERT_INVALID || status > LM_CERT_REVOKED) {
		rb_raise (rb_eArgError,
			  "invalid LmCertificateStatus: %d (expected %d <= LmCertificateStatus <= %d)",
			  status, LM_CERT_INVALID, LM_CERT_REVOKED);
	}

	return status;
}

LmSSLStatus 
rb_lm_ssl_status_from_ruby_object (VALUE obj)
{
	LmSSLStatus status;

	status = FIX2INT (obj);
	if (status < LM_SSL_STATUS_NO_CERT_FOUND || 
	    status > LM_SSL_STATUS_GENERIC_ERROR) {
		rb_raise (rb_eArgError, 
			  "invalid LmSSLStatus: %d (expected %d <= LmSSLStatus <= %d)",
			  status, LM_SSL_STATUS_NO_CERT_FOUND, 
			  LM_SSL_STATUS_GENERIC_ERROR);
	}

	return status;
}

LmSSLResponse
rb_lm_ssl_response_from_ruby_object (VALUE obj)
{
	LmSSLResponse response;
	
	response = FIX2INT (obj);
	if (response < LM_SSL_RESPONSE_CONTINUE || 
	    response > LM_SSL_RESPONSE_STOP) {
		rb_raise (rb_eArgError,
			  "invalid LmSSLResponse: %d (expected %d <= LmSSLResponse <= %d)",
			  response,
			  LM_SSL_RESPONSE_CONTINUE, LM_SSL_RESPONSE_STOP);
	}

	return response;
}

void 
Init_lm_constants (VALUE lm_mLM)
{
	/* LmMessageType */
	lm_mMessageType = rb_define_module_under (lm_mLM, "MessageType");

	rb_define_const (lm_mMessageType, "MESSAGE",
			 INT2FIX (LM_MESSAGE_TYPE_MESSAGE));
	rb_define_const (lm_mMessageType, "PRESENCE",
			 INT2FIX (LM_MESSAGE_TYPE_PRESENCE));
	rb_define_const (lm_mMessageType, "IQ",
			 INT2FIX (LM_MESSAGE_TYPE_IQ));

	/* LmMessageSubType */
	lm_mMessageSubType = rb_define_module_under (lm_mLM, "MessageSubType");

	rb_define_const (lm_mMessageSubType, "AVAILABLE",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_AVAILABLE));
	rb_define_const (lm_mMessageSubType, "NORMAL",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_NORMAL));
	rb_define_const (lm_mMessageSubType, "CHAT",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_CHAT));
	rb_define_const (lm_mMessageSubType, "GROUPCHAT",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_GROUPCHAT));
	rb_define_const (lm_mMessageSubType, "HEADLINE",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_HEADLINE));
	rb_define_const (lm_mMessageSubType, "UNAVAILABLE",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_UNAVAILABLE));
	rb_define_const (lm_mMessageSubType, "PROBE",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_PROBE));
	rb_define_const (lm_mMessageSubType, "SUBSCRIBE",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_SUBSCRIBE));
	rb_define_const (lm_mMessageSubType, "UNSUBSCRIBE",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_UNSUBSCRIBE));
	rb_define_const (lm_mMessageSubType, "SUBSCRIBED",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_SUBSCRIBED));
	rb_define_const (lm_mMessageSubType, "UNSUBSCRIBED",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_UNSUBSCRIBED));
	rb_define_const (lm_mMessageSubType, "GET",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_GET));
	rb_define_const (lm_mMessageSubType, "SET",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_SET));
	rb_define_const (lm_mMessageSubType, "RESULT",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_RESULT));
	rb_define_const (lm_mMessageSubType, "ERROR",
			 INT2FIX (LM_MESSAGE_SUB_TYPE_ERROR));

	/* LmDisconnectReason */
	lm_mDisconnectReason = rb_define_module_under (lm_mLM, "DisconnectReason");

	rb_define_const (lm_mDisconnectReason, "OK",
			 INT2FIX (LM_DISCONNECT_REASON_OK));
	rb_define_const (lm_mDisconnectReason, "PING_TIME_OUT",
			 INT2FIX (LM_DISCONNECT_REASON_PING_TIME_OUT));
	rb_define_const (lm_mDisconnectReason, "HUP",
			 INT2FIX (LM_DISCONNECT_REASON_HUP));
	rb_define_const (lm_mDisconnectReason, "ERROR",
			 INT2FIX (LM_DISCONNECT_REASON_ERROR));
	rb_define_const (lm_mDisconnectReason, "RESOURCE_CONFLICT",
			 INT2FIX (LM_DISCONNECT_REASON_RESOURCE_CONFLICT));
	rb_define_const (lm_mDisconnectReason, "INVALID_XML",
			 INT2FIX (LM_DISCONNECT_REASON_INVALID_XML));
	rb_define_const (lm_mDisconnectReason, "UNKNOWN",
			 INT2FIX (LM_DISCONNECT_REASON_UNKNOWN));

	/* LmConnectionState */
	lm_mConnectionState = rb_define_module_under (lm_mLM, "ConnectionState");
	rb_define_const (lm_mConnectionState, "CLOSED",
			 INT2FIX (LM_CONNECTION_STATE_CLOSED));
	rb_define_const (lm_mConnectionState, "OPENING",
			 INT2FIX (LM_CONNECTION_STATE_OPENING));
	rb_define_const (lm_mConnectionState, "OPEN",
			 INT2FIX (LM_CONNECTION_STATE_OPEN));
	rb_define_const (lm_mConnectionState, "AUTHENTICATING",
			 INT2FIX (LM_CONNECTION_STATE_AUTHENTICATING));
	rb_define_const (lm_mConnectionState, "AUTHENTICATED",
			 INT2FIX (LM_CONNECTION_STATE_AUTHENTICATED));

	/* LmProxyType */
	lm_mProxyType = rb_define_module_under (lm_mLM, "ProxyType");

	rb_define_const (lm_mProxyType, "NONE",
			 INT2FIX (LM_PROXY_TYPE_NONE));
	rb_define_const (lm_mProxyType, "HTTP",
			 INT2FIX (LM_PROXY_TYPE_HTTP));

	/* LmCertificateStatus */
	lm_mCertificateStatus = rb_define_module_under (lm_mLM, 
							"CertificateStatus");
	rb_define_const (lm_mCertificateStatus, "INVALID",
			 INT2FIX (LM_CERT_INVALID));
	rb_define_const (lm_mCertificateStatus, "ISSUER_NOT_FOUND",
			 INT2FIX (LM_CERT_ISSUER_NOT_FOUND));
	rb_define_const (lm_mCertificateStatus, "REVOKED",
			 INT2FIX (LM_CERT_REVOKED));

	/* LmSSLStatus */
	lm_mSSLStatus = rb_define_module_under (lm_mLM, "SSLStatus");

	rb_define_const (lm_mSSLStatus, "NO_CERT_FOUND",
			 INT2FIX (LM_SSL_STATUS_NO_CERT_FOUND));
	rb_define_const (lm_mSSLStatus, "UNTRUSTED_CERT",
			 INT2FIX (LM_SSL_STATUS_UNTRUSTED_CERT));
	rb_define_const (lm_mSSLStatus, "CERT_EXPIRED",
			 INT2FIX (LM_SSL_STATUS_CERT_EXPIRED));
	rb_define_const (lm_mSSLStatus, "CERT_NOT_ACTIVATED",
			 INT2FIX (LM_SSL_STATUS_CERT_NOT_ACTIVATED));
	rb_define_const (lm_mSSLStatus, "CERT_HOSTNAME_MISMATCH",
			 INT2FIX (LM_SSL_STATUS_CERT_HOSTNAME_MISMATCH));
	rb_define_const (lm_mSSLStatus, "CERT_FINGERPRINT_MISMATCH",
			 INT2FIX (LM_SSL_STATUS_CERT_FINGERPRINT_MISMATCH));
	rb_define_const (lm_mSSLStatus, "GENERIC_ERROR",
			 INT2FIX (LM_SSL_STATUS_GENERIC_ERROR));

	/* LmSSLResponse */
	lm_mSSLResponse = rb_define_module_under (lm_mLM, "SSLResponse");

	rb_define_const (lm_mSSLResponse, "CONTINUE",
			 INT2FIX (LM_SSL_RESPONSE_CONTINUE));
	rb_define_const (lm_mSSLResponse, "STOP",
			 INT2FIX (LM_SSL_RESPONSE_STOP));
}
