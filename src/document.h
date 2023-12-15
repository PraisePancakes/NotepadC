#ifndef DOCUMENT_H
#define DOCUMENT_H
#include "user.h"
#include <time.h>

typedef struct Document
{
    struct tm *created_at;
    struct tm *updated_at;
    char *title;
    char *contents;
} Document;

enum TmOffsets
{
    MONTH_OFFSET = 1,
    YEAR_OFFSET = 1900
};

struct tm *get_current_date_time();
void save_document(const char *full_path_to_document, Document *document);
Document *create_document(struct tm *current_date_time, User *user);
Document *load_document(const char *full_path_to_document);
char *doc_full_path_string(const char *docs_base_dir, char *doc_title);
void free_document(Document *loaded_document);

#endif