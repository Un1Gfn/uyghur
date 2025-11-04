/*
export A=chart L=pango,cairo,pangocairo; B() { ./gen.sh >gen.h && gcc -Wall -Wextra -O0 -Og -std=c99 $(pkg-config --cflags $L) $A.c $(pkg-config --libs $L) -o $A.out; }; R() { env O=/home/darren/Desktop/$A.pdf ./$A.out; };
*/

#include <assert.h>
#include <cairo-pdf.h>
#include <cairo.h>
#include <pango/pango-font.h>
#include <pango/pangocairo.h>

#include "gen.h"

#define W 842
#define H 1191

#define _(X) assert(CAIRO_STATUS_SUCCESS==X);

cairo_surface_t *surface = NULL;
cairo_t *cr = NULL;

PangoFontDescription *desc = NULL;

int max_w = -1;
int max_h = -1;

void new() {
	const char *const file = getenv("O");
	assert(file);
	assert(file[0]);
	surface = cairo_pdf_surface_create(file, W, H);
	_(cairo_surface_status(surface));
	assert(CAIRO_SURFACE_TYPE_PDF == cairo_surface_get_type(surface));
	cr = cairo_create(surface);
	desc = pango_font_description_from_string("Noto Serif Old Uyghur Regular 40");
}

void delete() {
	pango_font_description_free(desc);
	desc = NULL;
	cairo_destroy(cr);
	cr = NULL;
	cairo_surface_destroy(surface);
	surface = NULL;
}

void load() {
	static intptr_t max_count = -1;
	_Static_assert(sizeof(I) == 32 * sizeof(LPP), "");
	for (int i = 0; i < 2; i++) for (int j = 0; j < 16; j++) {
		LPP A = I[i][j];
		for (int i = 1; A[i]; i++) {
			int w=0, h=0;
			A[0] = (LP)((intptr_t)A[0] + 1);
			PangoLayout *l = pango_cairo_create_layout(cr);
			pango_layout_set_font_description(l, desc);
			pango_layout_set_text(l, A[i]->s, -1);
			pango_layout_get_size(l, &w, &h);
			//printf("%lf %lf\n", (double)w/PANGO_SCALE, (double)h/PANGO_SCALE);
			if (w > max_w) max_w = w;
			if (h > max_h) max_h = h;
			A[i]->l = l;
		}
		if((intptr_t)A[0] > max_count) max_count = (intptr_t)A[0];
	}
	assert(8 == max_count);
}

void bg() {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
}

void grid() {
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, W, 0, -(double)max_w/PANGO_SCALE*8, (double)max_h/PANGO_SCALE*17);
	cairo_stroke(cr);
}

void text() {

}

int main() {
	new();
	load();
	bg();
	grid();
	text();
	delete();
	return 0;
}

