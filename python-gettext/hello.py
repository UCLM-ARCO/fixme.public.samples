#!/usr/bin/python

# from: http://www.learningpython.com/2006/12/03/translating-your-pythonpygtk-application/

import sys, os

import locale
import gettext

APP = "hello"

langs = []
lc, encoding = locale.getdefaultlocale()
if lc: langs = [lc]

language = os.environ.get('LANGUAGE', None)
if language: langs += language.split(":")
langs += ["es_ES"]

gettext.textdomain(APP)
gettext.bindtextdomain(APP, './i18n')
lang = gettext.translation(APP, './i18n', languages=langs, fallback = True)
_ = lang.gettext


print _("hello world")
