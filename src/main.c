#include <cairo.h>
#include <cairo-pdf.h>
#include <pango/pangocairo.h>

void draw_text(cairo_t *cr) {
    PangoLayout *layout = pango_cairo_create_layout(cr);
    pango_layout_set_text(layout, "مرحبا بالعالم", -1);
    PangoFontDescription *desc = pango_font_description_from_string("Sans 24");
    pango_layout_set_font_description(layout, desc);
    pango_font_description_free(desc);

    // optionally set direction, alignment, etc
    // e.g. pango_layout_set_alignment(layout, PANGO_ALIGN_CENTER);

    // render
    pango_cairo_show_layout(cr, layout);
    g_object_unref(layout);
}

int main() {
    const double width = 595, height = 842;  // e.g. A4 size in points

    // Create a PDF surface
    cairo_surface_t *surface = cairo_pdf_surface_create("/tmp/ugpc.pdf", width, height);
    cairo_t *cr = cairo_create(surface);

    // If needed, scale, translate, etc
    // e.g. cairo_translate(cr, 50, 50);

    // Draw text via Pango
    draw_text(cr);

    // Clean up
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}

