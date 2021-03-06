/******************************************************************************
*  Nano-RK, a real-time operating system for sensor networks.
*  Copyright (C) 2007, Real-Time and Multimedia Lab, Carnegie Mellon University
*  All rights reserved.
*
*  This is the Open Source Version of Nano-RK included as part of a Dual
*  Licensing Model. If you are unsure which license to use please refer to:
*  http://www.nanork.org/nano-RK/wiki/Licensing
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, version 2.0 of the License.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*  Contributing Authors (specific to this file):
*  Anthony Rowe
*******************************************************************************/


#include <nrk.h>
#include <include.h>
#include <ulib.h>
#include <stdio.h>
#include <avr/sleep.h>
#include <hal.h>
#include <nrk_error.h>
#include <slip.h>

#define MAX_SLIP_BUF  128

NRK_STK Stack1[NRK_APP_STACKSIZE];
nrk_task_type TaskOne;
void Task1 (void);

NRK_STK Stack2[NRK_APP_STACKSIZE];
nrk_task_type TaskTwo;
void Task2 (void);

NRK_STK Stack3[NRK_APP_STACKSIZE];
nrk_task_type TaskThree;
void Task3 (void);

void nrk_create_taskset ();

uint8_t slip_buf[MAX_SLIP_BUF];

int main ()
{
  nrk_setup_ports ();
//  PORTE |= 2;
//  DDRA &= ~(0x10);
  nrk_setup_uart (UART_BAUDRATE_115K2);

  printf ("Starting up...\r\n");

  nrk_init ();

  nrk_led_clr (ORANGE_LED);
  nrk_led_clr (BLUE_LED);
  nrk_led_clr (GREEN_LED);
  nrk_led_clr (RED_LED);

  nrk_time_set (0, 0);
  nrk_create_taskset ();
  nrk_start ();

  return 0;
}

void Task1 ()
{
  uint16_t cnt;
  uint8_t len,i;
  uint16_t v;
  printf ("My node's address is %d\r\n", NODE_ADDR);

  printf ("Task1 PID=%d\r\n", nrk_get_pid ());
  cnt = 0;
  slip_init (stdin, stdout, 0, 0);

  while (1) {
    nrk_led_set (GREEN_LED);
    v = slip_rx (slip_buf, MAX_SLIP_BUF);
    if(v>0)
    {
    printf( "FF: %d [",v );
    for(i=0; i<v; i++ ) printf( "%x ",slip_buf[i] );
    nrk_kprintf( PSTR("]\r\n" ));
    nrk_led_clr (GREEN_LED);
    nrk_led_set (RED_LED);
    slip_tx (slip_buf, v);
    printf( "FF TX len: %d\r\n",v );
    nrk_led_clr (RED_LED);
    cnt++;
    } else nrk_kprintf( PSTR("SLIP RX error\r\n" ));
  }
}

void Task2 ()
{
  uint8_t cnt;
  printf ("Task2 PID=%d\r\n", nrk_get_pid ());
  cnt = 0;
  while (1) {
    nrk_led_set (BLUE_LED);
    printf ("Task2 cnt=%d\r\n", cnt);
    nrk_wait_until_next_period ();
    nrk_led_clr (BLUE_LED);
    nrk_wait_until_next_period ();
    cnt++;
  }
}

void nrk_create_taskset ()
{
  TaskOne.task = Task1;
  nrk_task_set_stk( &TaskOne, Stack1, NRK_APP_STACKSIZE);
  TaskOne.prio = 1;
  TaskOne.FirstActivation = TRUE;
  TaskOne.Type = BASIC_TASK;
  TaskOne.SchType = PREEMPTIVE;
  TaskOne.period.secs = 1;
  TaskOne.period.nano_secs = 500 * NANOS_PER_MS;
  TaskOne.cpu_reserve.secs = 0;
  TaskOne.cpu_reserve.nano_secs = 500 * NANOS_PER_MS;
  TaskOne.offset.secs = 0;
  TaskOne.offset.nano_secs = 0;
  nrk_activate_task (&TaskOne);

  TaskTwo.task = Task2;
  nrk_task_set_stk( &TaskTwo, Stack2, NRK_APP_STACKSIZE);
  TaskTwo.prio = 2;
  TaskTwo.FirstActivation = TRUE;
  TaskTwo.Type = BASIC_TASK;
  TaskTwo.SchType = PREEMPTIVE;
  TaskTwo.period.secs = 0;
  TaskTwo.period.nano_secs = 250 * NANOS_PER_MS;
  TaskTwo.cpu_reserve.secs = 0;
  TaskTwo.cpu_reserve.nano_secs = 0;
  //TaskTwo.cpu_reserve.nano_secs = 100 * NANOS_PER_MS;
  TaskTwo.offset.secs = 0;
  TaskTwo.offset.nano_secs = 0;
  nrk_activate_task (&TaskTwo);




}
