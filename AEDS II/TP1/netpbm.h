typedef enum
{
    P2,
    P3
} encoding_type;

typedef struct _pbm_file
{
    encoding_type encoding;
    unsigned int depth;
    unsigned int resolution_x;
    unsigned int resolution_y;
    char *content;
} PBM_FILE;