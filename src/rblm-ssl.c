#include "rblm.h"
#include "rblm-private.h"

VALUE lm_cSSL;

LmSSL *
rb_lm_ssl_from_ruby_object (VALUE obj)
{
	LmSSL *ssl;

	if (!rb_lm__is_kind_of (obj, lm_cSSL)) {
		rb_raise (rb_eTypeError, "not a LmSSL");
	}

	Data_Get_Struct (obj, LmSSL, ssl);

	return ssl;
}

void
ssl_free (LmSSL *ssl)
{
	lm_ssl_unref (ssl);
}

VALUE
rb_lm_ssl_to_ruby_object (LmSSL *ssl)
{
	if (ssl) {
		lm_ssl_ref (ssl);
		return Data_Wrap_Struct (lm_cSSL, NULL, 
					 ssl_free, ssl);
	} else {
		return Qnil;
	}
}

VALUE
ssl_allocate (VALUE klass)
{
	return Data_Wrap_Struct (klass, NULL, ssl_free, NULL);
}

static VALUE
ssl_is_supported (VALUE self)
{
	return GBOOL2RVAL (lm_ssl_is_supported ());
}

static LmSSLResponse
ssl_func_callback (LmSSL       *ssl,
		   LmSSLStatus  status,
		   gpointer     user_data)
{
	VALUE response;

	if (!user_data) {
		return LM_SSL_RESPONSE_CONTINUE;
	}

	response = rb_funcall ((VALUE)user_data, rb_intern ("call"), 1,
			       INT2FIX (status));

	return rb_lm_ssl_response_from_ruby_object (response);
}

static VALUE
ssl_initialize (int argc, VALUE *argv, VALUE self)
{
	LmSSL    *ssl;
	VALUE     fingerprint;
	VALUE     func;
	char     *fingerprint_str = NULL;
	gpointer  func_ptr = NULL;

	rb_scan_args (argc, argv, "01&", &fingerprint, &func);

	if (!NIL_P (func)) {
		func_ptr = (gpointer) func;
	}

	if (!NIL_P (fingerprint)) {
		VALUE str_val;

		if (!rb_respond_to (fingerprint, rb_intern ("to_s"))) {
			rb_raise (rb_eArgError, 
				  "fingerprint should respond to to_s");
		}

		str_val = rb_funcall (fingerprint, rb_intern ("to_s"), 0);
		fingerprint_str = StringValuePtr (str_val);
	}

	ssl = lm_ssl_new (fingerprint_str, ssl_func_callback,
			  func_ptr, NULL);

	DATA_PTR (self) = ssl;

	return self;
}

static VALUE
ssl_get_fingerprint (VALUE self)
{
	LmSSL *ssl = rb_lm_ssl_from_ruby_object (self);

	if (lm_ssl_get_fingerprint (ssl)) {
		return rb_str_new2 (lm_ssl_get_fingerprint (ssl));
	}

	return Qnil;
}

static VALUE
ssl_get_use_starttls (VALUE self)
{
	LmSSL *ssl = rb_lm_ssl_from_ruby_object (self);

	return GBOOL2RVAL (lm_ssl_get_use_starttls (ssl));
}

static VALUE
ssl_set_use_starttls (VALUE self, VALUE use)
{
	LmSSL *ssl = rb_lm_ssl_from_ruby_object (self);

	lm_ssl_use_starttls (ssl,
			     RVAL2GBOOL (use),
			     lm_ssl_get_require_starttls (ssl));

	return Qnil;
}

static VALUE
ssl_get_require_starttls (VALUE self)
{
	LmSSL *ssl = rb_lm_ssl_from_ruby_object (self);

	return GBOOL2RVAL (lm_ssl_get_require_starttls (ssl));
}

static VALUE
ssl_set_require_starttls (VALUE self, VALUE require)
{
	LmSSL *ssl = rb_lm_ssl_from_ruby_object (self);

	lm_ssl_use_starttls (ssl,
			     lm_ssl_get_use_starttls (ssl),
			     RVAL2GBOOL (require));

	return Qnil;
}

extern void
Init_lm_ssl (VALUE lm_mLM)
{
	lm_cSSL = rb_define_class_under (lm_mLM, "SSL", rb_cObject);

	rb_define_alloc_func (lm_cSSL, ssl_allocate);

	rb_define_singleton_method (lm_cSSL, "supported?", 
				    ssl_is_supported, 0);

	rb_define_method (lm_cSSL, "initialize", ssl_initialize, -1);
	rb_define_method (lm_cSSL, "fingerprint", ssl_get_fingerprint, 0);
	rb_define_method (lm_cSSL, "use_starttls", ssl_get_use_starttls, 0);
	rb_define_method (lm_cSSL, "use_starttls=", ssl_set_use_starttls, 1);
	rb_define_method (lm_cSSL, "require_starttls", ssl_get_require_starttls, 0);
	rb_define_method (lm_cSSL, "require_starttls=", ssl_set_require_starttls, 1);
}

