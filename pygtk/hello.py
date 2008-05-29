import gtk

b = gtk.Button('Click')
b.connect('clicked', gtk.main_quit)
w = gtk.Window()
w.add(b)
w.show_all()
gtk.main()
