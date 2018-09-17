// Copyright 2018 the AdSniper project authors. All rights reserved.
//
//

#ifndef V8_VM_SCRIPT_RUNNER_H_
#define V8_VM_SCRIPT_RUNNER_H_

namespace v8 {
namespace vm {
namespace internal {

void RunScriptByCompilation(
    const char* compilation_path, const char* script_path) ;

}  // namespace internal
}  // namespace vm
}  // namespace v8

#endif  // V8_VM_VM_COMPILER_H_