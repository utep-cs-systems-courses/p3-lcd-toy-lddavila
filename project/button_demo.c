#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"
#include "draw_shapes.h"
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
  } else {
    drawChar5x7(text_col, text_row, '-',off_color, backgroundColor);
  }
  if (switch2_state == down) {
    drawChar5x7(text_col + char_width, text_row, '2',on_color, backgroundColor);
  } else {
    drawChar5x7(text_col + char_width, text_row, '-',off_color, backgroundColor);
  }
  if(switch3_state == down){
    drawChar5x7(text_col+ char_width*2, text_row, '3',on_color,backgroundColor);
  }
  else{
    drawChar5x7(text_col + char_width*2, text_row, '-',off_color, backgroundColor);
  }
  if(switch4_state == down){
    drawChar5x7(text_col+char_width*3, text_row, '4',on_color, backgroundColor);
  }
  else{drawChar5x7(text_col+char_width*3, text_row, '-',off_color, backgroundColor);
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
  
  
  

  rectangle borderLeft;
  borderLeft.rect_row = 0;
  borderLeft.rect_col = screenWidth/2;
  borderLeft.old_rect_row = 0 ;
  borderLeft.old_rect_col = screenWidth/2;
  borderLeft.height = screenHeight;
  borderLeft.width =10;
  draw_rectangle(0,0,borderLeft);

  rectangle borderRight;
  borderRight.rect_row =0;
  borderRight.rect_col=screenWidth/2;
  borderRight.old_rect_row=0;
  borderRight.old_rect_col = screenWidth/2;
  borderRight.height = screenHeight;
  borderRight.width = 10;
  draw_rectangle(screenWidth-10,0,borderRight);

  rectangle topPlayer;
  topPlayer.rect_row=0;
  topPlayer.rect_col = screenWidth/2;
  topPlayer.old_rect_row=0;
  topPlayer.old_rect_col= screenWidth/2;
  topPlayer.height = 5;
  topPlayer.width =15;
  draw_rectangle(screenWidth/2, 10, topPlayer);

  
  //init_shapes();
  //enableWDTInterrupts();
  //or_sr(0x18);/**< CPU off , GIE on/*/

  
  //while (1) {			/* forever */
  //if (redraw_screen) {
  //  redraw_screen = 0;
  //  update_text();
  //}
  //green_on = 0;   	/* led off */
  //led_changed = 1;
  //led_update();
  //or_sr(0x10);	/**< CPU OFF */
    
  //green_on = 1;	/* led on */
  //led_changed = 1;
  //led_update();
  //}
}

    
    
