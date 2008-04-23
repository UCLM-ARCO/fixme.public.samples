// -*- mode: C++; coding: utf-8 -*-

// Message service with persistence.

#include "Message.ice"

module UCLM {

  class PersistentMessage implements Message {
    string message;
  };
};

