
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

//Enter the colors you want here:
#define PRIMARYCOLOR RGB_PURPLE //Color when not hit
#define SECONDARYCOLOR RGB_GOLD //Color when hit

RGB_MATRIX_EFFECT(simple)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool simple(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / rgb_matrix_config.speed;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint16_t tick = max_tick;

        bool hit = false;
        
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                //tick = g_last_hit_tracker.tick[j];
                hit = true;
                break;
            }
        }

      
        if(hit){
          rgb_matrix_set_color(i, SECONDARYCOLOR);
        }
        else{
          rgb_matrix_set_color(i, PRIMARYCOLOR);
        }
    }
    return led_max <  DRIVER_1_LED_COUNT +  DRIVER_2_LED_COUNT;
}

#        endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif         // RGB_MATRIX_KEYREACTIVE_ENABLED


