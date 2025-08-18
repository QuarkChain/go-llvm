#include <llvm-c/ExecutionEngine.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO: expermential API
int LLVMAddObjectFileByFilename(LLVMExecutionEngineRef ref, const char *obj_file);
int LLVMAddObjectFileFromBuffer(LLVMExecutionEngineRef ref, const char *buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif /* defined(__cplusplus) */