#include <llvm-c/ExecutionEngine.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO: expermential API
int LLVMAddObjectFileByFilename(LLVMExecutionEngineRef ref, const char *obj_file);

#ifdef __cplusplus
}
#endif /* defined(__cplusplus) */