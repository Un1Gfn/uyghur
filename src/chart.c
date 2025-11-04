/*
export A=chart L=pango,cairo,pangocairo; B() { ./gen.sh >gen.h && gcc -std=gnu23 -Wall -Wextra -O0 -Og -g $(pkg-config --cflags $L) $A.c $(pkg-config --libs $L) -o $A.out; }; R() { env O=/home/darren/Desktop/$A.pdf ./$A.out; };
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
#define X 2
#define Y 16

cairo_surface_t *surface = NULL;
cairo_t *cr = NULL;

PangoFontDescription *desc = NULL;

double curH = 0;

// max size among all variants of all letters
int max_h = -1;
int max_w = -1;

// number of variants of each letter
int Cn[X][Y] = {};

// total width of all variants of each letter
int Cw[X][Y] = {};

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
	for (int x = 0; x < 2; x++) for (int y = 0; y < 16; y++) {
		LPP A = I[x][y];
		for (int i = 0; A[i]; i++) {
			int w=0, h=0;
			Cn[x][y]++;
			PangoLayout *l = pango_cairo_create_layout(cr);
			pango_layout_set_font_description(l, desc);
			pango_layout_set_text(l, A[i]->s, -1);
			pango_layout_get_size(l, &w, &h);
			//printf("%lf %lf\n", (double)w/PANGO_SCALE, (double)h/PANGO_SCALE);
			Cw[x][y] += w;
			if (w > max_w) max_w = w;
			if (h > max_h) max_h = h;
			A[i]->l = l;
		}
		if (Cn[x][y] > max_count) max_count = Cn[x][y];
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

void cell(int x, int y) {
	LPP A = I[x][y];
	double curW = W;
	int w = -1;
	double m = (double) ((max_w * 8) - Cw[x][y]) / PANGO_SCALE / (Cn[x][y] - 1);
	for (int i = 0; A[i]; i++) {
		PangoLayout *l = (PangoLayout*)A[i]->l;
		pango_layout_get_size(l, &w, NULL);
		curW -= (double) w / PANGO_SCALE;
		cairo_move_to(cr, curW, curH);
		pango_cairo_show_layout(cr, l);
		curW -= m;
	}
}

void text() {
	cell(0, 0);
	curH += (double) max_h / PANGO_SCALE;
	cell(1, 0);
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

