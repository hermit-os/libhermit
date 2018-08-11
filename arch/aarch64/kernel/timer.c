/*
 * Copyright (c) 2010-2017, Stefan Lankes, RWTH Aachen University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the University nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <hermit/stdio.h>
#include <hermit/string.h>
#include <hermit/processor.h>
#include <hermit/time.h>
#include <hermit/tasks.h>
#include <hermit/errno.h>
#include <hermit/spinlock.h>
#include <hermit/logging.h>
#include <asm/irq.h>

/*
 * This will keep track of how many ticks the system
 * has been running for
 */
DEFINE_PER_CORE(uint64_t, timer_ticks, 0);
static uint32_t freq_hz;  /* frequency in Hz (updates per second) */

#if 0
extern int32_t boot_processor;
#endif

#define MHZ 1000000

#ifdef DYNAMIC_TICKS
DEFINE_PER_CORE(uint64_t, last_tsc, 0);
static uint64_t boot_tsc __attribute__ ((section(".data"))) = 0;

void check_ticks(void)
{
	// do we already know the timer frequency? => if not, ignore this check
	if (!freq_hz)
		return;

	const uint64_t curr_tsc = get_cntpct();
	mb();

	const uint64_t diff_tsc = curr_tsc - per_core(last_tsc);
	const uint64_t diff_ticks = (diff_tsc * (uint64_t) TIMER_FREQ) / freq_hz;

	if (diff_ticks > 0) {
		set_per_core(timer_ticks, per_core(timer_ticks) + diff_ticks);
		set_per_core(last_tsc, curr_tsc);
		rmb();
	}
}

uint64_t get_uptime(void)
{
	// do we already know the timer frequency?
	if (!freq_hz)
		return 0;

	const uint64_t curr_tsc = get_cntpct();

	mb();
	uint64_t diff = curr_tsc - boot_tsc;

	return (1000ULL*diff) / freq_hz;
}
#else
uint64_t get_uptime(void)
{
	return (get_clock_tick() * 1000) / TIMER_FREQ;
}

static void restart_periodic_timer(void)
{
	set_cntp_tval(freq_hz / TIMER_FREQ);
	set_cntp_ctl(1);
}
#endif

int timer_deadline(uint32_t ticks)
{
	set_cntp_tval(ticks * freq_hz / TIMER_FREQ);
	set_cntp_ctl(1);

	return 0;
}

void timer_disable(void)
{
	/* stop timer */
	set_cntp_ctl(0);
}

int timer_is_running(void)
{
	uint32_t v = get_cntp_ctl();

	return (v & 0x1);
}

/*
 * Handles the timer. In this case, it's very simple: We
 * increment the 'timer_ticks' variable every time the
 * timer fires.
 */
static void timer_handler(struct state *s)
{
#ifndef DYNAMIC_TICKS
	/* Increment our 'tick counter' */
	set_per_core(timer_ticks, per_core(timer_ticks)+1);
	restart_periodic_timer();
#else
	timer_disable();
#endif

#if 0
	/*
	 * Every TIMER_FREQ clocks (approximately 1 second), we will
	 * display a message on the screen
	 */
	if (timer_ticks % TIMER_FREQ == 0) {
		LOG_INFO("One second has passed %d\n", CORE_ID);
	}
#endif
}

void udelay(uint32_t usecs)
{
	uint64_t diff, end, start = get_cntpct();
	uint64_t deadline = (usecs * freq_hz) / 1000000;

	do {
		end = get_cntpct();
        rmb();
        diff = end > start ? end - start : start - end;
        if ((diff < deadline) && (deadline - diff > 50000))
			check_workqueues();
    } while(diff < deadline);
}

int timer_wait(unsigned int ticks)
{
	uint64_t eticks = per_core(timer_ticks) + ticks;

	task_t* curr_task = per_core(current_task);

	if (curr_task->status == TASK_IDLE)
	{
		/*
		 * This will continuously loop until the given time has
		 * been reached
		 */
		while (per_core(timer_ticks) < eticks) {
			check_workqueues();

			// recheck break condition
			if (per_core(timer_ticks) >= eticks)
				break;

			PAUSE;
		}
	} else if (per_core(timer_ticks) < eticks) {
		check_workqueues();

		if (per_core(timer_ticks) < eticks) {
			set_timer(eticks);
			reschedule();
		}
	}

	return 0;
}

int clock_init(void)
{
#ifdef DYNAMIC_TICKS
	if (!boot_tsc)
		boot_tsc = get_cntpct();
#endif

	return 0;
}

int timer_init(void)
{
#ifdef DYNAMIC_TICKS
	set_per_core(last_tsc, boot_tsc);
#endif

	return 0;
}

/*
 * Sets up the system clock
 */
int timer_calibration(void)
{
	freq_hz = get_cntfrq();

	LOG_INFO("aarch64_timer: frequency %d KHz\n", freq_hz / 1000);

	irq_install_handler(INT_PPI_NSPHYS_TIMER, timer_handler);

#ifndef DYNAMIC_TICKS
	restart_periodic_timer();
#endif

	return 0;
}
