// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Copyright 2018 the MetaHash project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "vm_apps/http_server/winsock-utils.h"

#include <cstdlib>

namespace {

// Prevent the compiler from optimizing away the arguments so they appear
// nicely on the stack in crash dumps.
#pragma warning(push)
#pragma warning (disable: 4748)
#pragma optimize( "", off )

// Pass the important values as function arguments so that they are available
// in crash dumps.
void CheckEventWait(WSAEVENT hEvent, DWORD wait_rv, DWORD expected) {
  if (wait_rv != expected) {
    DWORD err = ERROR_SUCCESS ;
    if (wait_rv == WAIT_FAILED)
      err = GetLastError() ;
    std::abort() ;  // Crash.
  }
}

#pragma optimize( "", on )
#pragma warning(pop)

}  // namespace

void AssertEventNotSignaled(WSAEVENT hEvent) {
  DWORD wait_rv = WaitForSingleObject(hEvent, 0) ;
  CheckEventWait(hEvent, wait_rv, WAIT_TIMEOUT) ;
}

bool ResetEventIfSignaled(WSAEVENT hEvent) {
  // TODO(wtc): Remove the CHECKs after enough testing.
  DWORD wait_rv = WaitForSingleObject(hEvent, 0) ;
  if (wait_rv == WAIT_TIMEOUT)
    return false ;  // The event object is not signaled.
  CheckEventWait(hEvent, wait_rv, WAIT_OBJECT_0) ;
  BOOL ok = WSAResetEvent(hEvent) ;
  if (!ok) {
    std::abort() ;
  }

  return true ;
}
