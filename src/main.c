#include <cairo.h>
#include <pango/pangocairo.h>

int main (int argc, char *argv[])
{
    const int WIDTH  = 400;
    const int HEIGHT = 100;
    const char *text = "مرحبا بالعالم";  /* Arabic “Hello world” */

    /* Create an image surface and a Cairo context */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                                           WIDTH, HEIGHT);
    cairo_t *cr = cairo_create (surface);

    /* Fill background white */
    cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
    cairo_paint (cr);

    /* Create Pango layout */
    PangoLayout *layout = pango_cairo_create_layout (cr);

    /* Set font description (use an Arabic-capable font) */
    PangoFontDescription *desc = pango_font_description_from_string ("Sans 24");
    pango_layout_set_font_description (layout, desc);
    pango_font_description_free (desc);

    /* Set the text */
    pango_layout_set_text (layout, text, -1);

    /* Enable automatic direction detection (so Arabic is treated RTL) */
    pango_layout_set_auto_dir (layout, TRUE);

    /* Set alignment to RIGHT */
    pango_layout_set_alignment (layout, PANGO_ALIGN_RIGHT);

    /* Set a width so that alignment has an effect */
    pango_layout_set_width (layout, WIDTH * PANGO_SCALE);

    /* Optionally set wrap / ellipsize if needed */
    // pango_layout_set_wrap (layout, PANGO_WRAP_WORD_CHAR);

    /* Get size of layout */
    int ink_width, ink_height;
    int logical_width, logical_height;
    pango_layout_get_pixel_extents (layout,
                                    NULL,  /* ink rect unused */
                                    & (PangoRectangle) {0,0,ink_width, ink_height});
    pango_layout_get_pixel_size (layout, &logical_width, &logical_height);

    /* Move to top-right (y=some margin) then render */
    const int margin = 10;
    cairo_move_to (cr, WIDTH - margin - (ink_width), margin);
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    pango_cairo_show_layout (cr, layout);

    /* Write to PNG */
    cairo_surface_write_to_png (surface, "/tmp/ugpc.pdf");

    /* Clean up */
    g_object_unref (layout);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

