#include "header.h"

const char *get_content_type(const char* path) {
    const char *type = strrchr(path, '.');
    if (type) {
        if (strcmp(type, ".gif") == 0) return "image/gif";
        if (strcmp(type, ".htm") == 0) return "text/html";
        if (strcmp(type, ".html") == 0) return "text/html";
        if (strcmp(type, ".jpeg") == 0) return "image/jpeg";
        if (strcmp(type, ".jpg") == 0) return "image/jpeg";
        if (strcmp(type, ".js") == 0) return "application/javascript";
        if (strcmp(type, ".json") == 0) return "application/json";
        if (strcmp(type, ".png") == 0) return "image/png";
        if (strcmp(type, ".pdf") == 0) return "application/pdf";
        if (strcmp(type, ".svg") == 0) return "image/svg+xml";
        if (strcmp(type, ".txt") == 0) return "text/plain";
    }
    return "application/octet-stream";
}
