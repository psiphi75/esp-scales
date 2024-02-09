#include <math.h>

#include "esp_log.h"

// Kalman filter variables
float estimate = 0.0f;          // Current state estimate
float estimate_error = 1.0f;    // Current state estimate error
float measurement_noise = 1.0f; // Measurement noise (R)
float last_estimate = 0.0f;

static const char *TAG = "KALMAN";

// Function to update the Kalman filter
float kalman_filter_update(float measurement)
{
    float kalman_gain = estimate_error / (estimate_error + measurement_noise);
    estimate = last_estimate + kalman_gain * (measurement - last_estimate);
    estimate_error = (1.0f - kalman_gain) * estimate_error + fabsf(last_estimate - estimate) * measurement_noise;
    last_estimate = estimate;

    return estimate;
}

void kalman_init(float initial_estimate, float initial_estimate_error, float measurement_noise_)
{
    // Initialize the Kalman filter
    estimate = initial_estimate;
    estimate_error = initial_estimate_error;
    measurement_noise = measurement_noise_;
}