#include <stdio.h>
#include <python3.12/Python.h>
#include "../lib/duktape.h"
int py() {
    FILE* fp = fopen("main.py", "r");
    if (fp == NULL) {
        perror("File not found");
        return 1;
    }
    Py_Initialize();
    PyObject* global_dict = PyDict_New();
    PyRun_File(fp, "main.py", Py_file_input, global_dict, global_dict);
    fclose(fp);
    PyRun_String("py()", Py_single_input, global_dict, global_dict);
    Py_Finalize();
}
void js() {
    duk_context *ctx = duk_create_heap_default();
    FILE *f = fopen("main.js", "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        rewind(f);
        char *src = malloc(len + 1);
        fread(src, 1, len, f);
        src[len] = '\0';
        fclose(f);

        duk_eval_string(ctx, src);
        free(src);
    }
    duk_push_global_object(ctx);
    duk_get_prop_string(ctx, -1, "js");
    if (duk_pcall(ctx, 0) != DUK_EXEC_SUCCESS) {
        printf("Error: %s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);
    duk_destroy_heap(ctx);
}
void c(void) {
    printf("Hello from C!");
}

int main() {
    py();
    js();
}