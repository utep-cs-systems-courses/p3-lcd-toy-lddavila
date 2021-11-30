#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"
#include "draw_shapes.h"
#include "buzzer.h"
// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 


char redraw_screen = 1;
u_int backgroundColor = COLOR_BLACK;
 
void
update_text(void)
{
  const u_char text_row = 20;
  const u_char text_col = 40;
  const u_char char_width = 12;
  static u_char blue = 31, green = 16, red = 31;
  u_int on_color  =                (green << 5) | red;
  u_int off_color = (blue << 11)                | red;
  
  if (switch1_state == down) {
    drawChar5x7(text_col, text_row, '1',on_color, backgroundColor);
    change_direction(1);
  } else {
    drawChar5x7(text_col, text_row, ' ',off_color, backgroundColor);
  }
  if (switch2_state == down) {
    drawChar5x7(text_col + char_width, text_row, '2',on_color, backgroundColor);
    change_direction(2);
  } else {
    drawChar5x7(text_col + char_width, text_row, ' ',off_color, backgroundColor);
  }
  if(switch3_state == down){
    drawChar5x7(text_col+ char_width*2, text_row, '3',on_color,backgroundColor);
    change_direction(3);
  }
  else{
    drawChar5x7(text_col + char_width*2, text_row, ' ',off_color, backgroundColor);
  }
  if(switch4_state == down){
    drawChar5x7(text_col+char_width*3, text_row, '4',on_color, backgroundColor);
    change_direction(4);
  }
  else{drawChar5x7(text_col+char_width*3, text_row, ' ',off_color, backgroundColor);
  }

}



void main(void)
{
  
  configureClocks();
  led_init();
  switch_p2_init();
  lcd_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  clearScreen(backgroundColor);
  init_shapes();
  
  
  
  while (1) {			/* forever */
    update_text();
  
  }
}

    
    
