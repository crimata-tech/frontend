#include <eases.h>

#include <math.h>
#include <gtk/gtk.h>
#include <stdbool.h>

// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
float quadratic_ease_in_out(double p, int distance)
{
  double s = p / distance;

  if(s < 0.5)
  {
    return distance * 2 * s * s;
  }
  else
  {
    return distance * ((-2 * s * s) + (4 * s) - 1);
  }
}

// Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
float elastic_ease_out(float p)
{
  return sin(-13 * M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1;
}

// Modeled after the parabola y = x^2
float quadratic_ease_in(float p)
{
  return p * p;
}

// Modeled after the parabola y = -x^2 + 2x
float quadratic_ease_out(float p)
{
  return -(p * (p - 2));
}

// Modeled after quarter-cycle of sine wave (different phase)
float sine_ease_out(float p)
{
  return sin(p * M_PI_2);
}

// Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
float back_ease_out(float p)
{
  float f = (1 - p);
  return 1 - (f * f * f - f * sin(f * M_PI));
}

// Modeled after the exponential function y = -2^(-10x) + 1
float exponential_ease_out(float p)
{
  return (p == 1.0) ? p : 1 - pow(2, -10 * p);
}

float sine_wave (float counter, float f, int A)
{
  float t = counter * 0.01;
  return  A * sin (2 * M_PI * f * t);
}

float sin_wave_scaled (float counter, float f, int A)
{
  int t = counter;
  return  A * sin (2 * M_PI * f * t);
}

// float asin_wave_scaled (float counter, float f, int A, float t)
// {
//   t = counter;
//   return  A * asin (2 * M_PI * f * t);
// }


float cos_wave (float counter, float f, int A, float t)
{
  t = counter * 0.01;
  return  A * cos (2 * M_PI * f * t);
}

float gravity_wave (float counter, float f, int A, float t)
{
  t = counter;
  float x = A * sin (2 * M_PI * f * t);
  return fabsf(x);
}

float gravity_wave_cos (float counter, float w, float ampl)
{
  float t = 0.5;
  float x = ampl * cos ( counter * w * t );
  return fabsf(x);
}

void damped_oscillator (float anchorX, float anchorY, float k, struct Strobes* circle)
{

  // constants
  int gravity = 0;
  int mass = 10;
  float timeStep = 0.28;
  float damping = 10;

  // calculate force Y
  float springForceY = -k*(circle->positionY - anchorY);
  float dampingForceY = damping * circle->velocityY;
  float forceY = springForceY + mass * gravity - dampingForceY;

  // calculate position Y
  float accelerationY = forceY/mass;
  circle->velocityY = circle->velocityY + accelerationY * timeStep;
  circle->positionY = circle->positionY + circle->velocityY * timeStep;

  // calculate force X
  float springForceX = -k*(circle->positionX - anchorX);
  float dampingForceX = damping * circle->velocityX;
  float forceX = springForceX - dampingForceX;

  // calculate position X
  float accelerationX = forceX/mass;
  circle->velocityX = circle->velocityX + accelerationX * timeStep;
  circle->positionX = circle->positionX + circle->velocityX * timeStep;
}
