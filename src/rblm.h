#ifndef __RLM_H__
#define __RLM_H__

#include <ruby.h>
#include <loudmouth/loudmouth.h> 
#include <glib.h>

extern void Init_loudmouth          (void);
extern void Init_lm_connection      (VALUE lm_mLM);
extern void Init_lm_message         (VALUE lm_mLM);
extern void Init_lm_message_node    (VALUE lm_mLM);
extern void Init_lm_constants       (VALUE lm_mLM);
extern void Init_lm_ssl             (VALUE lm_mLM);
extern void Init_lm_proxy           (VALUE lm_mLM);

#endif /* __RLM_H__ */

