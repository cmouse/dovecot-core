/* Copyright (c) 2025 Dovecot authors, see the included COPYING file */

#include "lib.h"
#include "test-common.h"
#include "mail-storage.h"
#include "mail-namespace.h"
#include "imap-metadata.h"

/* Mocks */
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

static void test_imap_metadata_verify_entry_name(void)
{
	struct {
		const char *name;
		bool valid;
	} tests[] = {
		{ "/private/comment", TRUE },
		{ "/shared/comment", TRUE },
		{ "/private/foo/bar", TRUE },
		{ "/shared/a/b/c", TRUE },
		{ "/PRIVATE/UPPER", TRUE },
		{ "/Shared/Mixed", TRUE },
		{ "private/foo", FALSE },
		{ "/private", TRUE },
		{ "/shared", TRUE },
		{ "/private/", FALSE },
		{ "/shared//foo", FALSE },
		{ "/private/foo*", FALSE },
		{ "/shared/foo%", FALSE },
		{ "/other/foo", FALSE },
		{ "", FALSE },
		{ "/", FALSE },
		{ "/private/ctrl\x01", FALSE },
		{ "//private/foo", FALSE },
		{ "/private/foo//bar", FALSE },
	};
	unsigned int i;

	test_begin("imap_metadata_verify_entry_name()");
	for (i = 0; i < N_ELEMENTS(tests); i++) {
		const char *error = NULL;
		bool result = imap_metadata_verify_entry_name(tests[i].name, &error);
		test_assert_idx(result == tests[i].valid, i);
	}
	test_end();
}

int main(void)
{
	static void (*const test_functions[])(void) = {
		test_imap_metadata_verify_entry_name,
		NULL
	};
	return test_run(test_functions);
}
