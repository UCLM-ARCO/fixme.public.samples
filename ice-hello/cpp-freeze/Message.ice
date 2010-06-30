// -*- mode: C++; coding: utf-8 -*-

// Message service.

module UCLM {

  interface Message {
    ["freeze:write"] void write(string msg);
    string read();
  };
};

