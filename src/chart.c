/*
export A=chart L=pango,cairo,pangocairo; B() { ./gen.sh >gen.h && gcc -Wall -Wextra -O0 -Og -std=c99 $(pkg-config --cflags $L) $A.c $(pkg-config --libs $L) -o $A.out; }; R() { env O=/home/darren/Desktop/$A.pdf ./$A.out; };
*/

#include <assert.h>
#include <cairo-pdf.h>
#include <cairo.h>
#include <pango/pango-font.h>
#include <pango/pangocairo.h>

#include "gen.h"

#define W 595
#define H 842

#define _(X) assert(CAIRO_STATUS_SUCCESS==X);

cairo_surface_t *surface = NULL;
cairo_t *cr = NULL;

PangoFontDescription *desc = NULL;

void new() {
	const char *const file = getenv("O");
	assert(file);
	assert(file[0]);
	surface = cairo_pdf_surface_create(file, W, H);
	_(cairo_surface_status(surface));
	assert(CAIRO_SURFACE_TYPE_PDF == cairo_surface_get_type(surface));
	cr = cairo_create(surface);
	desc = pango_font_description_from_string("Noto Serif Old Uyghur Regular 27");
}

void delete() {
	pango_font_description_free(desc);
	desc = NULL;
	cairo_destroy(cr);
	cr = NULL;
	cairo_surface_destroy(surface);
	surface = NULL;
}

void bg() {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
}

void grid() {
}

void text() {

}

int main() {
	new();
	bg();
	grid();
	text();
	delete();
	return 0;
}
