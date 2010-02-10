#!/usr/bin/python

import os, sys
import pyPdf

output = pyPdf.PdfFileWriter()
input = pyPdf.PdfFileReader(file(sys.argv[1], 'rb'))

# metadata
print "title = %s" % input.getDocumentInfo().title
print "npages = %s" % input.getNumPages()

for i in range(input.getNumPages())[::-1]:
    output.addPage(input.getPage(i))

fdout = file(os.path.splitext(sys.argv[1])[0] + '.out.pdf', 'wb')
output.write(fdout)
fdout.close()

