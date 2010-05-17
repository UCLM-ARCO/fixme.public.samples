#!/usr/bin/python

import gtk
import cairo
import pango
import pangocairo

WIDTH, HEIGHT = 256, 256

w = gtk.Window()

da = gtk.DrawingArea()
w.add(da)

def on_realize(widget, width=50, height=50):
    print "realize"
    cr = widget.window.cairo_create()

    cr.move_to(0, 0)
    cr.set_source_rgb(0, 0, 0)

    cr.set_line_width(5)
    cr.line_to(50, 50)
    cr.stroke()

    # layout = cr.create_layout()
    # desc = pango.FontDescription("helvetica bold 10")
    # layout.set_font_description(desc)
    # layout.set_text("hoola")

    # w, h = layout.get_pixel_size()
    # box = 40
    # width = w + box

    # # white rectangle to clean are
    # cr.set_source_rgb(.75, .85, 1)
    # cr.rectangle(width - w - box, height - h - box,
    #              w + box, h + box)
    # cr.fill()

    # # number of page
    # cr.set_source_rgb(0, 0, 0)
    # cr.move_to(width - w - box / 2, height - h - box / 2)
    # cr.show_layout(layout)

    # # ctx = widget.window.cairo_create()
    # # ctx.move_to(50, 50)

    # # cr = pangocairo.CairoContext(ctx)
    # # layout = cr.create_layout()
    # # cr.set_source_rgb(0, 0, 0)

    # # desc = pango.FontDescription("helvetica bold 10")
    # # layout.set_font_description(desc)
    # # layout.set_text("hola")

    # # cr.show_layout(layout)
    # # cr.stroke()

da.connect("realize", on_realize)
w.connect("delete-event", gtk.main_quit)

# # surface = cairo.ImageSurface (cairo.FORMAT_ARGB32, WIDTH, HEIGHT)
# # ctx = cairo.Context(surface)

# cr = pangocairo.CairoContext(ctx)
# layout = cr.create_layout()
# cr.set_source_rgb(0, 0, 0)
# cr.show_layout(layout)

# desc = pango.FontDescription("helvetica bold 10")
# layout.set_font_description(desc)
# layout.set_text("hola")

# da.draw(ctx)

w.show_all()

try:
    gtk.main()
except KeyboardInterrupt:
    pass
