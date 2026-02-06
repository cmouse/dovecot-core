/* Copyright (c) 2025 Dovecot authors, see the included COPYING file */

#include "lib.h"
#include "mail-storage.h"
#include "mail-namespace.h"
#include "mail-storage-private.h"

/* Mocks for test-imap-metadata.c and test-imap-msgpart.c */

struct mailbox *mailbox_alloc(struct mailbox_list *list ATTR_UNUSED, const char *name ATTR_UNUSED, enum mailbox_flags flags ATTR_UNUSED) { return NULL; }
int mailbox_open(struct mailbox *box ATTR_UNUSED) { return 0; }
void mailbox_free(struct mailbox **box) { *box = NULL; }
struct mailbox_transaction_context *mailbox_transaction_begin(struct mailbox *box ATTR_UNUSED, enum mailbox_transaction_flags flags ATTR_UNUSED, const char *context ATTR_UNUSED) { return NULL; }
int mailbox_transaction_commit(struct mailbox_transaction_context **t) { *t = NULL; return 0; }
void mailbox_transaction_rollback(struct mailbox_transaction_context **t) { *t = NULL; }
int mailbox_attribute_set(struct mailbox_transaction_context *t ATTR_UNUSED, enum mail_attribute_type type ATTR_UNUSED, const char *key ATTR_UNUSED, const struct mail_attribute_value *value ATTR_UNUSED) { return 0; }
int mailbox_attribute_unset(struct mailbox_transaction_context *t ATTR_UNUSED, enum mail_attribute_type type ATTR_UNUSED, const char *key ATTR_UNUSED) { return 0; }
int mailbox_attribute_get(struct mailbox *box ATTR_UNUSED, enum mail_attribute_type type ATTR_UNUSED, const char *key ATTR_UNUSED, struct mail_attribute_value *value_r ATTR_UNUSED) { return 0; }
int mailbox_attribute_get_stream(struct mailbox *box ATTR_UNUSED, enum mail_attribute_type type ATTR_UNUSED, const char *key ATTR_UNUSED, struct mail_attribute_value *value_r ATTR_UNUSED) { return 0; }
struct mailbox_attribute_iter *mailbox_attribute_iter_init(struct mailbox *box ATTR_UNUSED, enum mail_attribute_type type ATTR_UNUSED, const char *prefix ATTR_UNUSED) { return NULL; }
const char *mailbox_attribute_iter_next(struct mailbox_attribute_iter *iter ATTR_UNUSED) { return NULL; }
int mailbox_attribute_iter_deinit(struct mailbox_attribute_iter **iter) { *iter = NULL; return 0; }
struct mail_namespace *mail_namespace_find_inbox(struct mail_namespace *namespaces ATTR_UNUSED) { return NULL; }
const char *mailbox_get_last_error(struct mailbox *box ATTR_UNUSED, enum mail_error *error_code_r ATTR_UNUSED) { return NULL; }

int mail_get_parts(struct mail *mail ATTR_UNUSED, struct message_part **parts_r ATTR_UNUSED) { return -1; }
int mail_get_binary_properties(struct mail *mail ATTR_UNUSED, const struct message_part *part ATTR_UNUSED, bool include_hdr ATTR_UNUSED, struct mail_binary_properties *props_r ATTR_UNUSED) { return -1; }
int mail_get_binary_stream(struct mail *mail ATTR_UNUSED, const struct message_part *part ATTR_UNUSED, bool include_hdr ATTR_UNUSED, struct mail_binary_properties *props_r ATTR_UNUSED, struct istream **stream_r ATTR_UNUSED) { return -1; }
int mail_get_stream_because(struct mail *mail ATTR_UNUSED, struct message_size *hdr_size ATTR_UNUSED, struct message_size *body_size ATTR_UNUSED, const char *reason ATTR_UNUSED, struct istream **stream_r ATTR_UNUSED) { return -1; }
int mail_get_hdr_stream(struct mail *mail ATTR_UNUSED, struct message_size *hdr_size ATTR_UNUSED, struct istream **stream_r ATTR_UNUSED) { return -1; }
int mail_get_virtual_size(struct mail *mail ATTR_UNUSED, uoff_t *size_r ATTR_UNUSED) { return -1; }
int mail_get_physical_size(struct mail *mail ATTR_UNUSED, uoff_t *size_r ATTR_UNUSED) { return -1; }
int mail_get_header_stream(struct mail *mail ATTR_UNUSED, struct mailbox_header_lookup_ctx *headers ATTR_UNUSED, struct istream **stream_r ATTR_UNUSED) { return -1; }
struct mailbox_header_lookup_ctx *mailbox_header_lookup_init(struct mailbox *box ATTR_UNUSED, const char *const headers[] ATTR_UNUSED) { return NULL; }
void mailbox_header_lookup_unref(struct mailbox_header_lookup_ctx **ctx) { *ctx = NULL; }
void mail_set_critical(struct mail *mail ATTR_UNUSED, const char *fmt ATTR_UNUSED, ...) { }
void mail_add_temp_wanted_fields(struct mail *mail ATTR_UNUSED, enum mail_fetch_field field ATTR_UNUSED, struct mailbox_header_lookup_ctx *headers ATTR_UNUSED) {}
int mail_get_special(struct mail *mail ATTR_UNUSED, enum mail_fetch_field field ATTR_UNUSED, const char **value_r ATTR_UNUSED) { return -1; }
void mail_set_cache_corrupted(struct mail *mail ATTR_UNUSED, enum mail_fetch_field field ATTR_UNUSED, const char *reason ATTR_UNUSED) {}
