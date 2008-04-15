#include "rblm.h"
#include "rblm-private.h"

/* How to handle type, sub_type and root node*/

VALUE lm_cMessage;

LmMessage *
rb_lm_message_from_ruby_object (VALUE obj)
{
	LmMessage *m;

	if (!rb_lm__is_kind_of (obj, lm_cMessage)) {
		rb_raise (rb_eTypeError, "not a LmMessage");
	}

	Data_Get_Struct (obj, LmMessage, m);

	return m;
}

void
msg_free (LmMessage *m)
{
	lm_message_unref (m);
}

VALUE
rb_lm_message_to_ruby_object (LmMessage *m)
{
	if (m) {
		lm_message_ref (m);
		return Data_Wrap_Struct (lm_cMessage, NULL,
					 msg_free, m);
	} else {
		return Qnil;
	}
}

VALUE
msg_allocate (VALUE klass)
{
	return Data_Wrap_Struct (klass, NULL, msg_free, NULL);
}

VALUE
msg_initialize (int argc, VALUE *argv, VALUE self)
{
	LmMessage  *m;
	VALUE       to, type, sub_type;
	char       *to_str = NULL;

	rb_scan_args (argc, argv, "21", &to, &type, &sub_type);

	/* To can be nil */
	if (!NIL_P (to)) {
		if (!rb_respond_to (to, rb_intern ("to_s"))) {
			rb_raise (rb_eArgError, "to should respond to to_s");
		} else {
			VALUE str_val = rb_funcall (to, rb_intern ("to_s"), 0);
			to_str = StringValuePtr (str_val);
		}
	} 

	if (NIL_P (sub_type)) {
		/* Without sub_type */
		m = lm_message_new (to_str, FIX2INT (type));
	} else {
		m = lm_message_new_with_sub_type (to_str,
						  FIX2INT (type),
						  FIX2INT (sub_type));
	}

	DATA_PTR (self) = m;

	return self;
}

VALUE
msg_get_type (VALUE self)
{
	LmMessage *m = rb_lm_message_from_ruby_object (self);

	return INT2FIX (lm_message_get_type (m));
}

VALUE
msg_get_sub_type (VALUE self)
{
	LmMessage *m = rb_lm_message_from_ruby_object (self);

	return INT2FIX (lm_message_get_sub_type (m));
}

VALUE
msg_get_root_node (VALUE self)
{
	LmMessage *m = rb_lm_message_from_ruby_object (self);

	return LMMESSAGENODE2RVAL (m->node);
}

extern void 
Init_lm_message (VALUE lm_mLM)
{
	lm_cMessage = rb_define_class_under (lm_mLM, "Message", rb_cObject);

	rb_define_alloc_func (lm_cMessage, msg_allocate);
	
	rb_define_method (lm_cMessage, "initialize", msg_initialize, -1);
	rb_define_method (lm_cMessage, "type", msg_get_type, 0);
	rb_define_method (lm_cMessage, "sub_type", msg_get_sub_type, 0);
	rb_define_method (lm_cMessage, "root_node", msg_get_root_node, 0);

	rb_define_alias (lm_cMessage, "node", "root_node");
}

