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
#include <iostream>

extern "C" {
#include "ez-draw.h"
}

#define DELAY_MS 10
#define NUM_SAMPLES 40

#include "rt.h"

struct AppData {
    AppData(Ez_window win, int W_, int H_, hitable* world_, camera* cam_)
        : win1(win), W(W_), H(H_), world(world_), cam(cam_) {
        ez_set_data (win, this);
        ns = 0;
        r = new float[W*H];
        g = new float[W*H];
        b = new float[W*H];
    }
    Ez_window win1;
    int ns, W, H;
    float *r, *g, *b;
    hitable* world;
    camera *cam;
};

void onExpose (Ez_event *ev) {
    AppData *a = (AppData*) ez_get_data (ev->win);
    if (a->ns < NUM_SAMPLES) {
        a->ns++;
        std::cout << "Rendering sample " << a->ns << std::endl;
        for (int y = 0; y < a->H; y++) {
            int yoffs = (a->H - 1 - y)*a->W;
            for (int x = 0; x < a->W; x++) {
                vec3 col(0, 0, 0);
                float u = float(x + drand48()) / float(a->W);
                float v = float(y + drand48()) / float(a->H);
                ray r = a->cam->get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, a->world, 0);
                a->r[x+yoffs] += col.r();
                a->g[x+yoffs] += col.g();
                a->b[x+yoffs] += col.b();
            }
        }
    }
    for (int y = 0; y < a->H; y++) {
        int yoffs = y*a->W;
        for (int x = 0; x < a->W; x++) {
            vec3 col(a->r[x+yoffs], a->g[x+yoffs], a->b[x+yoffs]);
            col /= float(a->ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            ez_set_color(ez_get_RGB(ir, ig, ib));
            ez_draw_point(ev->win, x, y);
        }
    }
    ez_set_color (ez_black);
    ez_draw_text (ev->win, EZ_BRF, a->W-10, a->H-10, "%d", a->ns);
    if (a->ns <= NUM_SAMPLES) {
        ez_send_expose(ev->win);
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
    int W = 1200/2;
    int H = 800/2;

    hitable *world = create_scene();
    camera* cam = create_cam(W, H);

    Ez_window w = setupWin(W, H);
    AppData a(w, W, H, world, cam);

    ez_main_loop();
}

