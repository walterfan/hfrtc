#include "include/v8.h"
#include "include/libplatform/libplatform.h"
#include "TinyUtil.h"

using namespace v8;
using namespace wfan;

// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

void debug_trace(const v8::FunctionCallbackInfo<v8::Value>& args) {
  bool first = true;
  for (int i = 0; i < args.Length(); i++) {
    v8::HandleScope handle_scope(args.GetIsolate());
    if (first) {
      first = false;
    } else {
      printf(" ");
    }
    char szTimeStr[TIME_FMT_LEN] = { '\0' };
    current_timestamp(szTimeStr);
	
    v8::String::Utf8Value str(args[i]);
    const char* cstr = ToCString(str);
    printf("[%s] %s", szTimeStr, cstr);
  }
  printf("\n");
  fflush(stdout);
}
/*
v8::Handle<v8::Context> CreateShellContext(v8::Isolate* isolate) {
  // Create a template for the global object.
  v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
  // Bind the global 'print' function to the C++ Print callback.
  global->Set(v8::String::NewFromUtf8(isolate, "print"),
              v8::FunctionTemplate::New(isolate, Print));
 
  return v8::Context::New(isolate, NULL, global);
}
*/

int main(int argc, char* argv[]) {
  // Initialize V8.
  V8::InitializeICU();
  Platform* platform = platform::CreateDefaultPlatform();
  V8::InitializePlatform(platform);
  V8::Initialize();

  // Create a new Isolate and make it the current one.
  Isolate* isolate = Isolate::New();
  {
    Isolate::Scope isolate_scope(isolate);

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Create a new context.
    Local<Context> context = Context::New(isolate);

    // Enter the context for compiling and running the hello world script.
    Context::Scope context_scope(context);

    // Create a string containing the JavaScript source code.
    Local<String> source;


    if (argc > 1) {
        char* buffer = NULL;
        int ret = load_file_malloc(argv[1], buffer);
        if (ret != 0) {
            return ret;
        }

        source = String::NewFromUtf8(isolate, buffer);
        // free
        if (buffer)
            free(buffer);

    } else {
    	source = String::NewFromUtf8(isolate, "'Hello' + ', World!'");
    }

    // Compile the source code.
    Local<Script> script = Script::Compile(source);

    // Run the script to get the result.
    Local<Value> result = script->Run();

    // Convert the result to an UTF8 string and print it.
    String::Utf8Value utf8(result);
    printf("%s\n", *utf8);
  }
  
  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  V8::Dispose();
  V8::ShutdownPlatform();
  delete platform;
  return 0;
}
