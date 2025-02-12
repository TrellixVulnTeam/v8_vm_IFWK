// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Copyright 2018 the MetaHash project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_VM_APPS_HTTP_SERVER_SYS_BYTEORDER_H_
#define V8_VM_APPS_HTTP_SERVER_SYS_BYTEORDER_H_

#include <cstdint>

#include "src/base/build_config.h"
#include "src/base/compiler-specific.h"

namespace v8 {
namespace vm {
namespace internal {

// Returns a value with all bytes in |x| swapped, i.e. reverses the endianness.
inline std::uint16_t ByteSwap(std::uint16_t x) {
#if defined(V8_COMPILER_MSVC)
  return _byteswap_ushort(x) ;
#else
  return __builtin_bswap16(x) ;
#endif
}

inline std::uint32_t ByteSwap(std::uint32_t x) {
#if defined(V8_COMPILER_MSVC)
  return _byteswap_ulong(x) ;
#else
  return __builtin_bswap32(x) ;
#endif
}

inline uint64_t ByteSwap(std::uint64_t x) {
#if defined(V8_COMPILER_MSVC)
  return _byteswap_uint64(x) ;
#else
  return __builtin_bswap64(x) ;
#endif
}

inline std::uintptr_t ByteSwapUintPtrT(std::uintptr_t x) {
  // We do it this way because some build configurations are ILP32 even when
  // defined(ARCH_CPU_64_BITS). Unfortunately, we can't use sizeof in #ifs. But,
  // because these conditionals are constexprs, the irrelevant branches will
  // likely be optimized away, so this construction should not result in code
  // bloat.
  if (sizeof(std::uintptr_t) == 4) {
    return ByteSwap(static_cast<uint32_t>(x)) ;
  } else if (sizeof(std::uintptr_t) == 8) {
    return ByteSwap(static_cast<uint64_t>(x)) ;
  } else {
    // TODO: NOTREACHED() ;
  }
}

// Converts the bytes in |x| from host order (endianness) to little endian, and
// returns the result.
inline uint16_t ByteSwapToLE16(std::uint16_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return x ;
#else
  return ByteSwap(x) ;
#endif
}
inline std::uint32_t ByteSwapToLE32(std::uint32_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return x ;
#else
  return ByteSwap(x) ;
#endif
}
inline std::uint64_t ByteSwapToLE64(std::uint64_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return x ;
#else
  return ByteSwap(x) ;
#endif
}

// Converts the bytes in |x| from network to host order (endianness), and
// returns the result.
inline std::uint16_t NetToHost16(std::uint16_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return ByteSwap(x) ;
#else
  return x ;
#endif
}
inline std::uint32_t NetToHost32(std::uint32_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return ByteSwap(x) ;
#else
  return x ;
#endif
}
inline std::uint64_t NetToHost64(std::uint64_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return ByteSwap(x) ;
#else
  return x ;
#endif
}

// Converts the bytes in |x| from host to network order (endianness), and
// returns the result.
inline std::uint16_t HostToNet16(std::uint16_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return ByteSwap(x) ;
#else
  return x ;
#endif
}
inline std::uint32_t HostToNet32(std::uint32_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return ByteSwap(x) ;
#else
  return x ;
#endif
}
inline std::uint64_t HostToNet64(std::uint64_t x) {
#if defined(V8_TARGET_LITTLE_ENDIAN)
  return ByteSwap(x) ;
#else
  return x ;
#endif
}

}  // namespace internal
}  // namespace vm
}  // namespace v8

#endif  // V8_VM_APPS_HTTP_SERVER_SYS_BYTEORDER_H_
