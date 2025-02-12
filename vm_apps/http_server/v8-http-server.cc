// Copyright 2018 the MetaHash project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "vm_apps/http_server/http-server-session.h"
#include "vm_apps/http_server/tcp-server.h"
#include "vm_apps/http_server/v8-http-server-session.h"
#include "vm_apps/utils/app-utils.h"
#include "vm_apps/utils/command-line.h"

namespace {

// Switches
const char kSwitchPort[] = "port" ;

// Server default parameters
const char kServerName[] = "v8-http-server/1.0" ;
const std::int32_t kBodyBufferSize = 256 * 1024 ; // because of snapshots

}  //namespace

void HowToUse() {
  std::string exe_name = GetExecutablePath().BaseName().value() ;
  std::string help = StringPrintf(
      "usage: %s --%s=<server port> <args>\n\n", exe_name.c_str(),
      kSwitchPort) ;
  help += StringPrintf(
      "  %s  V8 HTTP server port for listening\n", kSwitchPort) ;
  help += StringPrintf(
      "  e.g.: %s --%s=7777\n", exe_name.c_str(), kSwitchPort) ;
  help += StringPrintf("\n%s", GetCommonCommandLineSwitches().c_str()) ;
  printf("%s\n", help.c_str()) ;
}

int main(int argc, char* argv[]) {
  CommandLine cmd_line(argc, argv) ;
  if (!cmd_line.HasSwitch(kSwitchPort)) {
    HowToUse() ;
    return 1 ;
  }

  // Initialize V8
  V8Initializer v8_initializer(cmd_line, &argc, argv) ;

  // Get a http-server port
  std::uint16_t server_port = 0 ;
  if (!StringToUint16(
          cmd_line.GetSwitchValueNative(kSwitchPort).c_str(), &server_port)) {
    return V8_ERROR_CREATE_WITH_MSG_SP(
        errInvalidArgument, "The server port is ivalid (Port: %s)",
        cmd_line.GetSwitchValueNative(kSwitchPort).c_str()) ;
  }

  V8_LOG_MSG("HTTP-server port: %d", server_port) ;

  // Start server
  TcpServer server ;
  HttpServerSession::ErrorHandler error_handler = std::bind(
      &V8HttpServerSession::WriteErrorResponseBody, nullptr,
      std::placeholders::_1, std::placeholders::_2) ;
  Error error = server.Start(
      server_port,
      HttpServerSession::GetCreator(
          V8HttpServerSession::ProcessSession, error_handler, kServerName,
          kBodyBufferSize)) ;
  V8_ERROR_RETURN_IF_FAILED(error) ;

  char command(0) ;
  while (command != 'q' && command != 'Q') {
    std::cin >> command ;
  }

  // Stop server
  error = server.Stop() ;
  V8_ERROR_RETURN_IF_FAILED(error) ;

  // Wait for server has stopped
  error = server.Wait() ;
  V8_ERROR_RETURN_IF_FAILED(error) ;

  return 0 ;
}
