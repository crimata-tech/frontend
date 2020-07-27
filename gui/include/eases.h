#ifndef __EASES
#define __EASES

#include <gtk/gtk.h>

/* Easing Math Utilites */

float quadratic_ease_in_out(double p, int distance);

float elastic_ease_out(float p);

float quadratic_ease_in(float p);

float quadratic_ease_out(float p);

float sine_ease_out(float p);

float back_ease_out(float p);

float exponential_ease_out(float p);

float sine_wave (float counter, float f, int A);

float sin_wave_scaled (float counter, float f, int A);

// float asin_wave_scaled (float counter, float f, int A, float t);

float cos_wave (float counter, float f, int A, float t);

float gravity_wave (float counter, float f, int A, float t);

float gravity_wave_cos (float counter, float w, float ampl);

struct Strobes
{
  int positionY;
  int positionX;

  float velocityY;
  float velocityX;
};

void damped_oscillator (float anchorX, float anchorY, float k, struct Strobes* circle);


#endif
