
#include <Rinternals.h>
#include <stdlib.h>
#include "latex_sourcepos.h"
#include "node.h"

cmark_node* latex_sourcepos(cmark_node *root) {

  cmark_event_type ev_type;
  cmark_iter *iter = cmark_iter_new(root);

  // Only insert one macro per line
  int lastline = -1;

  while ((ev_type = cmark_iter_next(iter)) != CMARK_EVENT_DONE) {

    cmark_node *cur = cmark_iter_get_node(iter);

    cmark_node_type type = cmark_node_get_type(cur);

    // Insert sourcepos before some nodes

    if ((type == CMARK_NODE_TEXT ||
         type == CMARK_NODE_CODE ||
         type == CMARK_NODE_CODE_BLOCK ||
         type == CMARK_NODE_HTML_BLOCK ||
         type == CMARK_NODE_HTML_INLINE) &&
        lastline != cur->start_line) {

      lastline = cur->start_line;
      cmark_node *sourcepos = cmark_node_new(CMARK_NODE_CUSTOM_INLINE);

      char buffer[100];
      snprintf(buffer, 100, "\\datapos{%d}",
                 cur->start_line);

      cmark_node_set_on_enter(sourcepos, buffer);
      cmark_node_insert_before(cur, sourcepos);
    }
  }

  cmark_iter_free(iter);

  return root;
}
