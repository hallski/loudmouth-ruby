#include "rblm.h"

VALUE lm_cProxy;

LmProxy *
rb_lm_proxy_from_ruby_object (VALUE obj)
{
	LmProxy *proxy;

	if (!rb_lm__is_kind_of (obj, lm_cProxy)) {
		rb_raise (rb_eTypeError, "not a LmProxy");
	}

	Data_Get_Struct (obj, LmProxy, proxy);

	return proxy;
}

void
proxy_free (LmProxy *proxy)
{
	lm_proxy_unref (proxy);
}

VALUE
rb_lm_proxy_to_ruby_object (LmProxy *proxy)
{
	if (proxy) {
		lm_proxy_ref (proxy);
		return Data_Wrap_Struct (lm_cProxy, NULL, 
					 proxy_free, proxy);
	} else {
		return Qnil;
	}
}
VALUE
proxy_allocate (VALUE klass)
{
	return Data_Wrap_Struct (klass, NULL, proxy_free, NULL);
}

VALUE
proxy_initialize (int argc, VALUE *argv, VALUE self)
{
	LmProxy *proxy;
	VALUE    type, server, port;
	char    *server_str = NULL;

	rb_scan_args (argc, argv, "12", &type, &server, &port);

	proxy = lm_proxy_new (FIX2INT (type));

	if (!NIL_P (server)) {
		if (!rb_respond_to (server, rb_intern ("to_s"))) {
			rb_raise (rb_eArgError, "server should respond to to_s");
		} else {
			VALUE str_val = rb_funcall (server, rb_intern ("to_s"), 0);
			lm_proxy_set_server (proxy, StringValuePtr (str_val));
		}
	}

	if (!NIL_P (port)) {
		lm_proxy_set_port (proxy, NUM2UINT (port));
	}

	DATA_PTR (self) = proxy;

	return self;
}

VALUE
proxy_get_type (VALUE self)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);

	return INT2FIX (lm_proxy_get_type (proxy));
}

VALUE
proxy_set_type (VALUE self, VALUE type)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);

	lm_proxy_set_type (proxy, FIX2INT (type));

	return Qnil;
}

VALUE
proxy_get_server (VALUE self)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);

	if (lm_proxy_get_server (proxy)) {
		return rb_str_new2 (lm_proxy_get_server (proxy));
	}

	return Qnil;
}

VALUE
proxy_set_server (VALUE self, VALUE server)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);
	VALUE    str_val;

	if (!rb_respond_to (server, rb_intern ("to_s"))) {
		rb_raise (rb_eArgError, "server should respond to to_s");
	} 

	str_val = rb_funcall (server, rb_intern ("to_s"), 0);
	lm_proxy_set_server (proxy, StringValuePtr (str_val));

	return Qnil;
}

VALUE 
proxy_get_port (VALUE self)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);

	return UINT2NUM (lm_proxy_get_port (proxy));
}

VALUE
proxy_set_port (VALUE self, VALUE port)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);

	lm_proxy_set_port (proxy, NUM2UINT (port));

	return Qnil;
}

VALUE
proxy_get_username (VALUE self)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);

	if (lm_proxy_get_username (proxy)) {
		return rb_str_new2 (lm_proxy_get_username (proxy));
	}

	return Qnil;
}

VALUE
proxy_set_username (VALUE self, VALUE username)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);
	VALUE    str_val;

	if (!rb_respond_to (username, rb_intern ("to_s"))) {
		rb_raise (rb_eArgError, "username should respond to to_s");
	} 

	str_val = rb_funcall (username, rb_intern ("to_s"), 0);
	lm_proxy_set_username (proxy, StringValuePtr (str_val));

	return Qnil;
}

VALUE
proxy_get_password (VALUE self)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);

	if (lm_proxy_get_password (proxy)) {
		return rb_str_new2 (lm_proxy_get_password (proxy));
	}

	return Qnil;
}

VALUE
proxy_set_password (VALUE self, VALUE password)
{
	LmProxy *proxy = rb_lm_proxy_from_ruby_object (self);
	VALUE    str_val;

	if (!rb_respond_to (password, rb_intern ("to_s"))) {
		rb_raise (rb_eArgError, "password should respond to to_s");
	} 

	str_val = rb_funcall (password, rb_intern ("to_s"), 0);
	lm_proxy_set_password (proxy, StringValuePtr (str_val));

	return Qnil;
}

extern void
Init_lm_proxy (VALUE lm_mLM)
{
	lm_cProxy = rb_define_class_under (lm_mLM, "Proxy", rb_cObject);

	rb_define_alloc_func (lm_cProxy, proxy_allocate);

	rb_define_method (lm_cProxy, "initialize", proxy_initialize, -1);
	rb_define_method (lm_cProxy, "type", proxy_get_type, 0);
	rb_define_method (lm_cProxy, "type=", proxy_set_type, 1);
	rb_define_method (lm_cProxy, "server", proxy_get_server, 0);
	rb_define_method (lm_cProxy, "server=", proxy_set_server, 1);
	rb_define_method (lm_cProxy, "port", proxy_get_port, 0);
	rb_define_method (lm_cProxy, "port=", proxy_set_port, 1);
	rb_define_method (lm_cProxy, "username", proxy_get_username, 0);
	rb_define_method (lm_cProxy, "username=", proxy_set_username, 1);
	rb_define_method (lm_cProxy, "password", proxy_get_password, 0);
	rb_define_method (lm_cProxy, "password=", proxy_set_password, 1);
}

