#include "executionengine.h"
#include <llvm/Support/MemoryBuffer.h>
#include <memory>
#include <iostream>
#include <llvm/Object/ObjectFile.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

using namespace llvm::object;

int LLVMAddObjectFileByFilename(LLVMExecutionEngineRef ref, const char *obj_file) {
    // LLVMExecutionEngineRef ref = (LLVMExecutionEngineRef)eeRef;
    // Load the .o file into memory
    auto FileOrErr = llvm::MemoryBuffer::getFile(obj_file);
    if (!FileOrErr) {
        return 1;
    }

    auto ObjOrErr = ObjectFile::createObjectFile(FileOrErr->get()->getMemBufferRef());
    if (!ObjOrErr) {
        return 2;
    }
    
    auto ee = reinterpret_cast<llvm::ExecutionEngine*>(ref);
    ee->addObjectFile(std::move(*ObjOrErr));
    return 0;
}