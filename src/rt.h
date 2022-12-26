//==================================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================
#pragma once

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "camera.h"

vec3 color(const ray& r, hitable *world, int depth);
hitable *create_scene();
camera *create_cam(int nx, int ny);

