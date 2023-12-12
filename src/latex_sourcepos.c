
#include <Rinternals.h>
#include <stdlib.h>
#include "latex_sourcepos.h"

cmark_node* latex_sourcepos(cmark_node *root) {

  cmark_event_type ev_type;
  cmark_iter *iter = cmark_iter_new(root);

  while ((ev_type = cmark_iter_next(iter)) != CMARK_EVENT_DONE) {

    cmark_node *cur = cmark_iter_get_node(iter);

    if (cmark_node_get_type(cur) == CMARK_NODE_TEXT) {

      const char * literal = cmark_node_get_literal(cur);

      Rprintf("Text node: %s\n", literal);
    }
  }

  cmark_iter_free(iter);

  return root;
}
