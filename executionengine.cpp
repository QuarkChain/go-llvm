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

int LLVMAddObjectFileFromBuffer(LLVMExecutionEngineRef ref, const char *buffer, size_t buffer_size) {
    // LLVMExecutionEngineRef ref = (LLVMExecutionEngineRef)eeRef;
    // Load the .o file into memory
    auto bufPtr = llvm::MemoryBuffer::getMemBuffer(
        llvm::StringRef(buffer, buffer_size),
        "mem_buf",
        false // Doesn't require null terminator for this example
    );

    if (!bufPtr) {
        return 1;
    }

    auto objOrErr = ObjectFile::createObjectFile(bufPtr->getMemBufferRef());
    if (!objOrErr) {
        return 2;
    }

    auto ee = reinterpret_cast<llvm::ExecutionEngine*>(ref);
    ee->addObjectFile(std::move(*objOrErr));
    return 0;
}