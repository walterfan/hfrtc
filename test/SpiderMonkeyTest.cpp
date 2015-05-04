#include "jsapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define TRACE_MINARGS 2
#define TIME_FMT_LEN 50

using namespace JS;

// The class of the global object.
static JSClass globalClass = { "global", JSCLASS_GLOBAL_FLAGS, JS_PropertyStub,
        JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
        JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, nullptr, nullptr,
        nullptr, nullptr, JS_GlobalObjectTraceHook };

long long current_timestamp(char arrTimeStr[TIME_FMT_LEN]) {
    struct timeval tv;
    struct tm* ptm;
    char time_string[40];

    gettimeofday(&tv, NULL); // get current time
    if (arrTimeStr) {
        ptm = localtime(&tv.tv_sec);
        /* Format the date and time, down to a single second.  */
        strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", ptm);
        /* Compute milliseconds from microseconds.  */
        //snprintf(char * restrict str, size_t size, const char * restrict format,
        snprintf(arrTimeStr, TIME_FMT_LEN, "%s.%06d", time_string, tv.tv_usec);
    }
    long long total_us = tv.tv_sec * 1000000LL + tv.tv_usec ; // caculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return total_us;
}

// [SpiderMonkey 24] Use JSBool instead of bool.
static bool debug_trace(JSContext *cx, unsigned argc, jsval *vp) {
    JS::CallArgs args = CallArgsFromVp(argc, vp);

    char szTimeStr[TIME_FMT_LEN] = { '\0' };
    current_timestamp(szTimeStr);
    if (args.length() > 0) {
        JSString *str = args[0].toString();
        printf("[%s] %s\n", szTimeStr, JS_EncodeString(cx, str));
    }

    return true;
}

//typedef void (* JSErrorReporter)(JSContext *cx, const char *message, JSErrorReport *report);
// The error reporter callback.
void report_error(JSContext *cx, const char *message, JSErrorReport *report) {
    fprintf(stderr, "%s:%u:%s\n",
            report->filename ? report->filename : "[no filename]",
            (unsigned int) report->lineno, message);
}

int load_file_malloc(const char* szFile, char*& pBuffer,
        long* pBufSize = NULL) {
    FILE * pFile = NULL;
    long lSize = 0;
    size_t result = 0;

    pFile = fopen(szFile, "r");
    if (pFile == NULL) {
        fputs("File open error", stderr);
        return 1;
    }

    // obtain file size:
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // allocate memory to contain the whole file:
    pBuffer = (char*) malloc(sizeof(char) * lSize);
    if (pBuffer == NULL) {
        fputs("Memory allocate error", stderr);
        fclose(pFile);
        return 2;
    }

    // copy the file into the buffer:
    result = fread(pBuffer, 1, lSize, pFile);
    if (result != lSize) {
        fputs("Reading file error", stderr);
        fclose(pFile);
        return 3;
    }
    if (pBufSize)
        *pBufSize = lSize;

    fclose(pFile);
    return 0;
}

int test(JSContext *cx, RootedObject* pGlobal, const char* pScript) {
    //RootedObject global = *pGlobal;

    JS::RootedValue rval(cx);

    JSAutoCompartment ac(cx, *pGlobal);
    JS_InitStandardClasses(cx, *pGlobal);

    const char *filename = "noname";
    int lineno = 1;
    bool ok = JS_DefineFunction(cx, *pGlobal, "debug_trace", debug_trace,
            TRACE_MINARGS, 0);
    if (!ok)
        return 1;

    ok = JS_EvaluateScript(cx, *pGlobal, pScript, strlen(pScript), filename,
            lineno, &rval);
    if (!ok)
        return 2;

    //JSString *str = rval.toString();
    //printf("%s\n", JS_EncodeString(cx, str));

    return 0;
}

int run(JSContext *cx, const char* pScript) {
    // Enter a request before running anything in the context.
    JSAutoRequest ar(cx);

    // Create the global object and a new compartment.
    RootedObject global(cx);
    global = JS_NewGlobalObject(cx, &globalClass, nullptr,
            JS::DontFireOnNewGlobalHook);
    if (!global)
        return 1;

    // Enter the new global object's compartment.
    JSAutoCompartment ac(cx, global);

    // Populate the global object with the standard globals, like Object and
    // Array.
    if (!JS_InitStandardClasses(cx, global))
        return 1;

    // Your application code here. This may include JSAPI calls to create your
    // own custom JS objects and run scripts.
    long long begin_time = current_timestamp(NULL);
    test(cx, &global, pScript);
    long long end_time = current_timestamp(NULL);
    printf("calling costs %lld microseconds\n", end_time - begin_time);

    return 0;
}

int main(int argc, const char *argv[]) {
    // Initialize the JS engine.
    if (!JS_Init())
        return 1;

    // Create a JS runtime.
    JSRuntime *rt = JS_NewRuntime(8L * 1024L * 1024L, JS_USE_HELPER_THREADS);
    if (!rt)
        return 1;

    // Create a context.
    JSContext *cx = JS_NewContext(rt, 8192);
    if (!cx)
        return 1;
    //JS_SetErrorReporter(JSContext *cx, JSErrorReporter er);
    JS_SetErrorReporter(cx, report_error);

    int status = 0;
    if (argc > 1) {
        char* buffer = NULL;
        int ret = load_file_malloc(argv[1], buffer);
        if (ret != 0) {
            return ret;
        }

        status = run(cx, buffer);
        // free
        if (buffer)
            free(buffer);

    } else {
        const char *script = "'hello'+'world, it is '+new Date()";
        status = run(cx, script);
    }

    // Shut everything down.
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();

    return status;
}
