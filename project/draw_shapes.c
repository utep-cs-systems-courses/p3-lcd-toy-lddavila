#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include <libTimer.h>
#include "switches.h"
#include "led.h"


// global vars for the rectangle
rectangle rect1;
/* int rect_row, rect_col; */
/* int old_rect_row, old_rect_col; */
/* u_char height, width; */

// global vars for the circle
/* int cir_y, cir_x; */
/* int old_cir_y, old_cir_x; */
/* int r; */
circle cir1;
rectangle topPlayer;
rectangle bottomPlayer;

u_int background_color = COLOR_BLACK;

static int x_vel1 = 10;
static int x_vel2 = 10;

void
init_shapes(void)
{
  // vars for the rectangle
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
  
  topPlayer.rect_row=13;
  topPlayer.rect_col = 72;
  topPlayer.old_rect_row=13;
  topPlayer.old_rect_col= 72;
  topPlayer.height = 6;
  topPlayer.width =16;
  draw_rectangle(64, 10, topPlayer);
  
  bottomPlayer.rect_row=153;
  bottomPlayer.rect_col = 72;
  bottomPlayer.old_rect_row=153;
  bottomPlayer.old_rect_col= 72;
  bottomPlayer.height = 6;
  bottomPlayer.width =16;
  draw_rectangle(64, 150, bottomPlayer);

  // vars for the circle
  
  cir1.cir_y = 60;
  cir1.cir_x = screenWidth / 2;
  cir1.old_cir_y = 60;
  cir1.old_cir_x = screenWidth / 2;
  cir1.r =4 ;
  // draw_circle(screenWidth/2, screenHeight/2, cir1.r, WHITE);

  
}
void
change_direction(int button){
  switch(button){
  case 1:
    x_vel1 = change(0);
    break;
  case 2:
    x_vel1 = change(1);
    break;
  case 3:
    x_vel2= -10;
    break;
  case 4:
    x_vel2 = 10;
    break;

  }

}
void
draw_moving_shapes()
{
  int left_col1 = topPlayer.old_rect_col - (topPlayer.width / 2);
  int top_row1  = topPlayer.old_rect_row - (topPlayer.height / 2);

  // blank out the old top player
  fillRectangle(left_col1, top_row1, topPlayer.width, topPlayer.height, background_color);

  int left_col2 = bottomPlayer.old_rect_col - (bottomPlayer.width/2);
  int top_row2 = bottomPlayer.old_rect_row - (bottomPlayer.height/2);

  fillRectangle(left_col2, top_row2, bottomPlayer.width, bottomPlayer.width, background_color);
  
  // blank out the old circle
  draw_circle(cir1.old_cir_x, cir1.old_cir_y, cir1.r, background_color);

  // draw and update the rectangle
  moving_rectangle();
  
  // draw and update the circle
  moving_circle(cir1);  
}


void draw_rectangle(int xCoordinate, int yCoordinate,rectangle local)
{
  int left_col = local.rect_col - (local.width / 3);
  int top_row  = local.rect_row - (local.height / 2);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11)| (green << 5) | red;

  fillRectangle(xCoordinate, yCoordinate, local.width, local.height, color);
}


void
moving_rectangle()
{
  rectangle *to_draw1 = &topPlayer;
  rectangle *to_draw2 = &bottomPlayer;

  
  
  static int y_vel1 = 5;

  int left_col = to_draw1->rect_col - (to_draw1->width / 2);
  int top_row  = to_draw1->rect_row - (to_draw1->height / 2);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw rectangle at current position
  fillRectangle(left_col, top_row, to_draw1->width, to_draw1->height, color);

  // save current position
  to_draw1->old_rect_row = to_draw1->rect_row;
  to_draw1->old_rect_col = to_draw1->rect_col;

  // update position
  // to_draw->rect_row += y_vel;
  to_draw1->rect_col += x_vel1;

  // check boundaries, see if rectangle has hit the edges
  if ( ( to_draw1->rect_col - (to_draw1->width / 2) ) <= 14 ||            // left boundary
       ( to_draw1->rect_col + (to_draw1->width / 2) ) >= screenWidth-19 ) { // right boundary
    // right or left hit, reverse x velocity
    x_vel1 = x_vel1 * -1;
  }

  

  int left_col2 = to_draw2->rect_col-(to_draw2->width/2);
  int top_row2 = to_draw2->rect_row-(to_draw2->height/2);
  fillRectangle(left_col2,top_row2,to_draw2->width,to_draw2->width,color);

  to_draw2->old_rect_row = to_draw2->rect_row;
  to_draw2->old_rect_col= to_draw2->rect_col;
  to_draw2->rect_col+= x_vel2;
  
  if((to_draw2->rect_col-(to_draw2->width/2) ) <=14 ||
     (to_draw2->rect_col+(to_draw2->width/2) ) >= screenWidth-19) {
    x_vel2 = x_vel2 *-1;
  }

  if(switch1_state == down){
    x_vel1 = x_vel1 *-1;
    }
  

}


void
draw_triangle(void)
{
  u_char height = 40;
  u_char row = 80, col = screenWidth / 2;

  u_char step = 0;

  unsigned int blue = 31, green = 0, red = 31;

  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw a n equilateral triangle
  // starts at the top and works down
  // at the first row the width is 1, second 2 and so on
  for (step = 0; step < height; step++) {
    // left side of triangle
    u_char start_col = col - (step / 2);
    // right side of triangle
    u_char end_col   = col + (step / 2);
    u_char width     = end_col - start_col;
    fillRectangle(col - (step / 2), row+step, width, 1, color);
  }
}

void
drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int colorBGR)
{
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  for (u_int i = 0; i < length; i++) {
    lcd_writeColor(colorBGR);
  }
  
}

void
drawLines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color)
{
  // bottom
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord + x_point, color);
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord - x_point, color);
					  
}

void
draw_circle(int x, int y, int r, u_int color)
{
  int x_coord = x;
  int y_coord = y;
  // first point will be the very top;
  int x_point = 0;
  int y_point = r;
  int decision = 3 - (2 * r);

  drawLines(x_coord, y_coord, x_point, y_point, color);

  while (y_point >= x_point) {
    // move x over one
    x_point++;

    // check decision point
    if (decision > 0) {
      // move y down one
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    } else {
      decision = decision + 4 * x_point + 6;
    }
    drawLines(x_coord, y_coord, x_point, y_point, color);
  }
}

void
moving_circle()
{
  static int x_vel = 5;
  static int y_vel = 10;
  
  u_int color = COLOR_SIENNA;


  // draw at the new position
  draw_circle(cir1.cir_x, cir1.cir_y, cir1.r, color);

  // save current position
  cir1.old_cir_x =cir1.cir_x;
  cir1.old_cir_y = cir1.cir_y;

  // update position
  cir1.cir_x += x_vel;
  cir1.cir_y += y_vel;
  
  // check boundaries, see if circle has hit the border
  if ( (cir1.cir_x + cir1.r) >= screenWidth-10|| (cir1.cir_x - cir1.r) <= 10) {
    // top or bottom hit, reverse x velocity
    x_vel = x_vel * -1;
  }
  if ( ( cir1.cir_y - cir1.r ) <= 0 ||            // left boundary
       ( cir1.cir_y + cir1.r ) >= screenHeight ) { // right boundary
    // right or left hit, reverse y velocity
    y_vel = y_vel * -1;
  }

  
  if (((cir1.cir_y - topPlayer.rect_row) == cir1.r + topPlayer.height/2) &&
      (topPlayer.rect_col- topPlayer.width/2<= cir1.cir_x + cir1.r) &&
      (cir1.cir_x + cir1.r <=topPlayer.rect_col+topPlayer.width/2)) { 
    // right or left hit, reverse y velocity
    y_vel = y_vel * -1;
  }

  if((cir1.cir_y+cir1.r > 144) &&
     (bottomPlayer.rect_col- bottomPlayer.width/2<= cir1.cir_x + cir1.r) &&
     (cir1.cir_x + cir1.r <=bottomPlayer.rect_col+bottomPlayer.width/2)){
    y_vel = y_vel *-1;
  }
  
}
