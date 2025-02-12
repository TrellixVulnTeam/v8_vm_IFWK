// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Copyright 2018 the MetaHash project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "vm_apps/http_server/server-socket.h"

#include "vm_apps/http_server/ip-address.h"
#include "vm_apps/http_server/ip-endpoint.h"

ServerSocket::ServerSocket() {
}

ServerSocket::~ServerSocket() {
}

Error ServerSocket::ListenWithAddressAndPort(
    const std::string& address_string, std::uint16_t port, int backlog) {
  IPAddress ip_address ;
  if (!ip_address.AssignFromIPLiteral(address_string)) {
    return V8_ERROR_CREATE_WITH_MSG_SP(
        errNetAddressInvalid, "The net address is invalid - '%s'",
        address_string.c_str()) ;
  }

  return Listen(IPEndPoint(ip_address, port), backlog) ;
}
