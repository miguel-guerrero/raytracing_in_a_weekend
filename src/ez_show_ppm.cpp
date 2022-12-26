//==================================================================================================
// Writen in 2022 by Miguel Guerrero
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================
#include <string>
#include <iostream>

extern "C" {
#include "ez-draw.h"
}

#define DELAY_MS 10

struct AppData {
    AppData(Ez_window win, int W_, int H_)
        : win1(win), W(W_), H(H_) {
        ez_set_data (win, this);
        r = new float[W*H];
        g = new float[W*H];
        b = new float[W*H];
    }
    Ez_window win1;
    int W, H;
    float *r, *g, *b;
    ~AppData() {
        delete [] r;
        delete [] g;
        delete [] b;
    }
};

void onExpose (Ez_event *ev) {
    AppData *a = (AppData*) ez_get_data (ev->win);
    for (int y=0; y<a->H; y++) {
        int yoffs =  y*a->W;
        for (int x=0; x<a->W; x++) {
            int ir = int(255.99*a->r[x + yoffs]);
            int ig = int(255.99*a->g[x + yoffs]);
            int ib = int(255.99*a->b[x + yoffs]);
            ez_set_color(ez_get_RGB(ir, ig, ib));
            ez_draw_point(ev->win, x, y);
        }
    }
}

void onKeyPress (Ez_event *ev) {
    switch (ev->key_sym) {
        case XK_q : ez_quit(); break;
    }
}

void onTimerNotify (Ez_event *ev) {
    ez_send_expose(ev->win);
    ez_start_timer(ev->win, DELAY_MS);
}


void onEvent (Ez_event *ev) {
    switch (ev->type) {
        case Expose      : onExpose  (ev); break;
        case KeyPress    : onKeyPress(ev); break;
        case TimerNotify : onTimerNotify(ev); break;
    }
}

Ez_window setupWin(int W, int H) {
    if (ez_init() < 0)
        exit(1);
    Ez_window w = ez_window_create(W, H, "", onEvent);
    //ez_start_timer(w, DELAY_MS);
    ez_window_dbuf(w, 1);
    return w;
}

int main () {
    std::string mark;
    int W, H, maxVal, r, g, b;

    std::cin >> mark >> W >> H >> maxVal; // "P3" ...
    Ez_window w = setupWin(W, H);
    AppData a(w, W, H);

    for (int y = 0; y < H; y++) {
        int yoffs =  y*W;
        for (int x = 0; x < W; x++) {
            std::cin >> r >> g >> b;
            a.r[x + yoffs] = float(r)/maxVal;
            a.g[x + yoffs] = float(g)/maxVal;
            a.b[x + yoffs] = float(b)/maxVal;
        }
    }

    ez_main_loop();
}

