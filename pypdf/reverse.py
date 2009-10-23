#!/usr/bin/python

import os, sys
import pyPdf

output = pyPdf.PdfFileWriter()
input = pyPdf.PdfFileReader(file(sys.argv[1], 'rb'))

# print the title of document1.pdf
print "title = %s" % input.getDocumentInfo().title
print "npages = %s" % input.getNumPages()

for page in reversed(input.pages):
    output.addPage(page)

fdout = file(os.path.splitext(sys.argv[1])[0] + '.out.pdf', 'wb')
output.write(fdout)
fdout.close()

