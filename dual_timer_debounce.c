/*
 * Copyright 2017 Alex Ong <the.onga@gmail.com>
 * Copyright 2020 Andrei Purdea <andrei@purdea.ro>
 * Copyright 2021 Simon Arlott
 * Copyright 2024 Javier Oliver (@joliverMI)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
Basic symmetric per-key algorithm. Uses an 8-bit counter per key.
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/

#include "matrix.h"
#include "timer.h"
#include "quantum.h"
#include <stdlib.h>

#ifdef PROTOCOL_CHIBIOS
#    if CH_CFG_USE_MEMCORE == FALSE
#        error ChibiOS is configured without a memory allocator. Your keyboard may have set `#define CH_CFG_USE_MEMCORE FALSE`, which is incompatible with this debounce algorithm.
#    endif
#endif

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

// Maximum debounce: 127ms, minumum debounce 1
#if DEBOUNCE > 127
#    undef DEBOUNCE
#    define DEBOUNCE 127
#endif

#ifndef DEBOUNCE_DUAL_TIMER
#   define DEBOUNCE_DUAL_TIMER 50
#endif

#define ROW_SHIFTER ((matrix_row_t)1)

typedef struct {
    bool    pressed : 1;
    uint8_t time : 7;
} debounce_counter_t;

//Add second timer
typedef struct {
    bool    expired : 1;
    uint8_t time : 7;
} dual_counter_t;

#if DEBOUNCE > 0
static debounce_counter_t *debounce_counters;
static dual_counter_t     *dual_counters;
static fast_timer_t        last_time;
static bool                counters_need_update;
static bool                matrix_need_update;
static bool                cooked_changed;

#    define DEBOUNCE_ELAPSED 0
#    define DUAL_ELAPSED 0

static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t elapsed_time);
static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows);

// we use num_rows rather than MATRIX_ROWS to support split keyboards
void debounce_init(uint8_t num_rows) {
    debounce_counters = malloc(num_rows * MATRIX_COLS * sizeof(debounce_counter_t));
    int i             = 0;
    for (uint8_t r = 0; r < num_rows; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            debounce_counters[i].time = DEBOUNCE_ELAPSED;
            dual_counters[i].time = DEBOUNCE_DUAL_TIMER;
            dual_counters[i++].expired = false;
        }
    }
}

void debounce_free(void) {
    free(debounce_counters);
    free(dual_counters);
    debounce_counters = NULL;
    dual_counters = NULL;
}

bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    bool updated_last = false;
    cooked_changed    = false;

    if (counters_need_update) {
        fast_timer_t now          = timer_read_fast();
        fast_timer_t elapsed_time = TIMER_DIFF_FAST(now, last_time);

        last_time    = now;
        updated_last = true;
        if (elapsed_time > UINT8_MAX) {
            elapsed_time = UINT8_MAX;
        }

        if (elapsed_time > 0) {
            update_debounce_counters_and_transfer_if_expired(raw, cooked, num_rows, elapsed_time);
        }
    }

    if (changed || matrix_need_update) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        transfer_matrix_values(raw, cooked, num_rows);
    }
    return cooked_changed;
}

static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t elapsed_time) {
    debounce_counter_t *debounce_pointer = debounce_counters;
    dual_counter_t *dual_pointer = dual_counters;

    counters_need_update = false;
    matrix_need_update   = false;

    for (uint8_t row = 0; row < num_rows; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);
            if (dual_pointer->expired || (debounce_pointer->time == DEBOUNCE_ELAPSED)){
                //Don't do anything because timers have already been expired
            } else {
                if (dual_pointer->time <= elapsed_time){
                    //Act eagerly because long timer has expired
                    dual_pointer->expired = true;
                    matrix_need_update = true;
                } else if (debounce_pointer->time <= elapsed_time){
                    //Act deferred because debounce has expired
                    debounce_pointer->time = DEBOUNCE_ELAPSED;
                    matrix_row_t cooked_next = (cooked[row] & ~col_mask) | (raw[row] & col_mask);
                    cooked_changed |= cooked_next ^ cooked[row];
                    cooked[row] = cooked_next;
                    if (cooked_changed){
                        dual_pointer->expired = false;
                        dual_pointer->time = DEBOUNCE_DUAL_TIMER;
                    }
                }
            }
            //Count Down the timers
            if (!dual_pointer->expired){
                dual_pointer->time -= elapsed_time;
                counters_need_update = true;
            }
            if (debounce_pointer->time != DEBOUNCE_ELAPSED){
                debounce_pointer->time -= elapsed_time;
                counters_need_update = true;                    
            }
            // if (debounce_pointer->time != DEBOUNCE_ELAPSED) {
            //     if (debounce_pointer->time <= elapsed_time) {
            //         debounce_pointer->time = DEBOUNCE_ELAPSED;

            //         if (debounce_pointer->pressed) {
            //             // key-down: eager
            //             matrix_need_update = true;
            //         } else {
            //             // key-up: defer
            //             matrix_row_t cooked_next = (cooked[row] & ~col_mask) | (raw[row] & col_mask);
            //             cooked_changed |= cooked_next ^ cooked[row];
            //             cooked[row] = cooked_next;
            //         }
            //     } else {
            //         debounce_pointer->time -= elapsed_time;
            //         dual_pointer->time -= elapsed_time;
            //         counters_need_update = true;
            //     }
            // }
            debounce_pointer++;
            dual_pointer++;
        }
    }
}

static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows) {
    //This runs if a timer has elapsed or if the matrix changes
    debounce_counter_t *debounce_pointer = debounce_counters;
    dual_counter_t *dual_pointer = dual_counters;

    for (uint8_t row = 0; row < num_rows; row++) {
        matrix_row_t delta = raw[row] ^ cooked[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);

            if (delta & col_mask) {
                //Key has changed from the cooked value so run this:
                if (dual_pointer->expired || debounce_pointer->time == DEBOUNCE_ELAPSED) {
                    //Key changed and a timer expired so run this:
                    dual_pointer->expired = false;
                    dual_pointer->time = DEBOUNCE_DUAL_TIMER;
                    debounce_pointer->time = DEBOUNCE;
                    counters_need_update = true;
                    //eager run:
                    cooked[row] ^= col_mask;
                    cooked_changed = true;
                    //eager end
                } else {
                    //Key changed, but no timer expired so reset the debounce timer
                    debounce_pointer->time = DEBOUNCE;
                }
                // if (debounce_pointer->time == DEBOUNCE_ELAPSED) {
                //     debounce_pointer->pressed = (raw[row] & col_mask);
                //     debounce_pointer->time    = debounce_pointer->pressed ? DEBOUNCE_ELAPSED : DEBOUNCE;
                //     counters_need_update      = true;

                //     if (debounce_pointer->pressed) {
                //         // key-down: eager
                //         cooked[row] ^= col_mask;
                //         cooked_changed = true;
                //     }
                // }
            } else if (debounce_pointer->time != DEBOUNCE_ELAPSED) {
                //The key has not changed from the cooked value and the timers havent elapsed so run this:
                // debounce_pointer->time = DEBOUNCE_ELAPSED;
            }
            debounce_pointer++;
        }
    }
}

#else
#    include "none.c"
#endif