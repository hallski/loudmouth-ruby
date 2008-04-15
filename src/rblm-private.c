#include "rblm-private.h"

gboolean
rb_lm__is_kind_of (VALUE object, VALUE klass)
{
	return RVAL2GBOOL (rb_obj_is_kind_of (object, klass));
}

