#!/usr/bin/python

import sys, os

import locale
import gettext

APP_NAME = "hello"

local_path = os.path.realpath(os.path.dirname(sys.argv[0]))
langs = []
lc, encoding = locale.getdefaultlocale() #Check the default locale
if lc: langs = [lc]

language = os.environ.get('LANGUAGE', None)
if (language): langs += language.split(":")
langs += ["es_ES"]

gettext.bindtextdomain(APP_NAME, local_path)
gettext.textdomain(APP_NAME)

lang = gettext.translation(APP_NAME, local_path,
                           languages=langs, fallback = True)
_ = lang.gettext


print _("hello world")
