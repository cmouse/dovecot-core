/* Copyright (c) 2025 Dovecot authors, see the included COPYING file */

#include "lib.h"
#include "test-common.h"
#include "mail-storage.h"
#include "imap-msgpart.h"

/* Mocks */
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

static void test_imap_msgpart_parse(void)
{
	struct {
		const char *section;
		bool success;
		bool contains_body;
	} tests[] = {
		{ "", TRUE, TRUE },
		{ "1", TRUE, TRUE },
		{ "1.2", TRUE, TRUE },
		{ "MIME", FALSE, FALSE },
		{ "1.MIME", TRUE, TRUE },
		{ "HEADER", TRUE, FALSE },
		{ "1.HEADER", TRUE, FALSE },
		{ "TEXT", TRUE, TRUE },
		{ "1.TEXT", TRUE, TRUE },
		{ "HEADER.FIELDS (Subject Date)", TRUE, FALSE },
		{ "HEADER.FIELDS.NOT (From)", TRUE, FALSE },
		{ "1.HEADER.FIELDS (Subject)", TRUE, FALSE },
		{ "1.2.3.4", TRUE, TRUE },
		{ "1.2.MIME", TRUE, TRUE },
		{ "1.2.TEXT", TRUE, TRUE },
		{ "1.2.HEADER", TRUE, FALSE },
		{ "1.", FALSE, FALSE },
		{ ".1", FALSE, FALSE },
		{ "1.2..3", FALSE, FALSE },
		{ "HEADER.FIELDS", FALSE, FALSE },
		{ "HEADER.FIELDS ()", FALSE, FALSE },
		{ "INVALID", FALSE, FALSE },
	};
	unsigned int i;

	test_begin("imap_msgpart_parse()");
	for (i = 0; i < N_ELEMENTS(tests); i++) {
		struct imap_msgpart *part = NULL;
		int ret = imap_msgpart_parse(tests[i].section, &part);
		bool success = (ret == 0);
		test_out(t_strdup_printf("case %u: %s (success)", i, tests[i].section),
			 success == tests[i].success);
		if (success) {
			test_out(t_strdup_printf("case %u: %s (contains_body)", i, tests[i].section),
				 imap_msgpart_contains_body(part) == tests[i].contains_body);
			imap_msgpart_free(&part);
		}
	}
	test_end();
}

int main(void)
{
	static void (*const test_functions[])(void) = {
		test_imap_msgpart_parse,
		NULL
	};
	return test_run(test_functions);
}
