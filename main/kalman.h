

#ifndef __MAIN_KALMAN_H__
#define __MAIN_KALMAN_H__

float kalman_filter_update(float measurement);
void kalman_init(float initial_estimate, float initial_estimate_error, float measurement_noise);

#endif /* __MAIN_KALMAN_H__ */
