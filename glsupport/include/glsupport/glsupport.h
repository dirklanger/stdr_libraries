/********************************************************
  Stanford Driving Software
  Copyright (c) 2011 Stanford University
  All rights reserved.

  Redistribution and use in source and binary forms, with 
  or without modification, are permitted provided that the 
  following conditions are met:

* Redistributions of source code must retain the above 
  copyright notice, this list of conditions and the 
  following disclaimer.
* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the 
  following disclaimer in the documentation and/or other
  materials provided with the distribution.
* The names of the contributors may not be used to endorse
  or promote products derived from this software
  without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
 ********************************************************/


#ifndef GLSUPPORT_GL_SUPPORT_H
#define GLSUPPORT_GL_SUPPORT_H

#include <cmath>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glsupport/fontRenderer.h>

namespace glsupport
{

void set_display_mode_2D(int w, int h);
void set_display_mode_3D(int w, int h, float fov, float near, float far);

// font rendering
void render_stroke_text_2D(float x, float y, float size, const char* string);
void render_stroke_text_centered_2D(float x, float y, float size, const char* string);
void renderBitmapString(float x, float y, const char* string);
void renderBitmapStringCentered(float x, float y, const char* string);
int bitmapStringWidth(const char* string);

void draw_circle(double x, double y, double r, bool filled);
void draw_dashed_circle(double x, double y, double r);
void draw_ellipse(double x, double y, double rx, double ry, bool filled);
void draw_diamond(double x, double y, double r);
void draw_arrowhead(double x, double y, double angle);

void draw_observed_car(double x, double y, double theta,
                       double w, double l, int id, double v, bool draw_flag,
                       double x_var, double y_var, int /*tracking_state*/,
                       int /*lane*/, double /*confidence*/, bool published,
                       double /*camera_pan*/, double, double, double, bool);  // TODO: use or remove?!?

void draw_scale(int window_width, double map_zoom);
void draw_coordinate_frame(double scale);

void draw_distance_rings(double x, double y, double theta, int max_distance, int distance_increment);

void draw_vehicle_outline(double length, double width, double height,
                          double wheel_base, double origin_to_front_axle_dist,
                          double front_axle_to_front_bumper_dist, double track_width,
                          double wheel_radius, double wheel_angle);

void draw_passat_simple(double length, double width, double height, double wheel_base,
                        double track_width, double wheel_radius, double wheel_angle);

void draw_arrow(double x1, double y1, double x2, double y2, 
                double head_width, double head_length);

void draw_arrowhead_2D(double x, double y, double angle);

extern inline void draw_line(double x1, double y1, double x2, double y2)
{
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
}

extern inline void draw_dashed_line(double x1, double y1, double x2, 
                                    double y2, double stripe_len)
{
  double frac, dx, dy, x, y;
  int i;

  frac = stripe_len / hypot(x2 - x1, y2 - y1);
  dx = frac * (x2 - x1);
  dy = frac * (y2 - y1);
  x = x1;
  y = y1;
  glBegin(GL_LINES);
  for(i = 0; i < (int)floor(1 / frac); i++) {
    if(i % 2 == 0) {
      glVertex2f(x, y);
      glVertex2f(x + dx, y + dy);
    }
    x += dx;
    y += dy;
  }
  glEnd();
}

extern float dgc_colormap_hsv[128][3];
extern float dgc_colormap_hot[128][3];
extern float dgc_colormap_autumn[128][3];
extern float dgc_colormap_bone[128][3];
extern float dgc_colormap_jet[128][3];
extern float dgc_colormap_prism[128][3];

} // namespace glsupport

#endif //GLSUPPORT_GL_SUPPORT_H
