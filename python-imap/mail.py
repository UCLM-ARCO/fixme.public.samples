#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

# http://stackoverflow.com/questions/2792623/reading-and-parsing-email-from-gmail-using-c-c-or-python

import sys
import email, imaplib

class Message:
    def __init__(self, account, num):
        typ, self.data = account.fetch(num, '(RFC822)')
        assert typ == 'OK'

        for part in self.data:
            if not isinstance(part, tuple):
                print "skip '%s'" % part
                continue

            print "-> '%s'" % part[0]
            self.msg = email.message_from_string(part[1])
            self.payload = self.msg.get_payload()
            print 'iteration'

    def __getitem__(self, key):
        return self.msg[key]


class ImapServer:
    def __init__(self, host, port):
        self.conn = imaplib.IMAP4_SSL(host, port)

    def __del__(self):
        try:
            self.conn.close()
        except:
            pass
        self.conn.logout()

    def login(self, user, pasw):
        self.conn.login(user, pasw)
        self.conn.select()

    def get_messages(self):
        typ, data = self.conn.search(None, 'ALL')
        assert typ == 'OK'

        retval = []
        for num in data[0].split():
            retval.append(Message(self.conn, num))

        return retval


if len(sys.argv) != 3:
    print "usage: %s nick password" % __file__
    sys.exit(1)

account = ImapServer('imap.gmail.com', 993)
account.login(sys.argv[1], sys.argv[2])

for msg in account.get_messages():
    print '-' * 20
    print msg['from'], msg['subject']
    print msg['date']
    print msg.payload
