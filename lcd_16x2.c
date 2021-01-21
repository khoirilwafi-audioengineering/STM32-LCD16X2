/* code program sederhana untuk interface lcd 16x2 */

#include "main.h"
#include "stdio.h"

void write_bit(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, ((data >> 0) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, ((data >> 1) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, ((data >> 2) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, ((data >> 3) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void lcd_en()
{
	HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
	for(int i=0; i<400; i++);
	HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
	for(int i=0; i<400; i++);
}

void lcd_command(unsigned char data)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	write_bit(data >> 4);
	lcd_en();
  write_bit(data);
	lcd_en();
}

void lcd_data(unsigned char data)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	write_bit(data >> 4);
	lcd_en();
  write_bit(data);
	lcd_en();
}

void lcd_print(char *str)
{
	for(int i = 0; str[i] != 0; i++)
	{
		lcd_data(str[i]);
	}
}

void lcd_setCursor(uint8_t x, uint8_t y)
{
	if(y == 0) lcd_command(0x80 + x);
	if(y == 1) lcd_command(0xC0 + x);
}

void lcd_init()
{
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0C);
	lcd_command(0x06);
	lcd_command(0x80); 
	lcd_command(0x01);
}

void lcd_number(int data)
{
	char buff[11];
	sprintf(buff, "%d", data);
	lcd_print(buff);
}

void lcd_float(float data, int koma)
{
	char buff[10];
	switch(koma)
	{
		case 0 :
			lcd_number(data);
			break;
		case 1 : 
			sprintf(buff, "%.1f", data);
			lcd_print(buff);
			break;
		case 2 :
			sprintf(buff, "%.2f", data);
			lcd_print(buff);
			break;
		case 3 :
			sprintf(buff, "%.3f", data);
		  lcd_print(buff);
			break;
		case 4 :
			sprintf(buff, "%.4f", data);
		  lcd_print(buff);
			break;
		case 5 :
			sprintf(buff, "%.5f", data);
			lcd_print(buff);
			break;
		case 6 :
			sprintf(buff, "%6f", data);
			lcd_print(buff);
			break;
		case 7 :
			sprintf(buff, "%.7f", data);
			lcd_print(buff);
			break;
		case 8 :
			sprintf(buff, "%.8f", data);
			lcd_print(buff);
			break;
		case 9 :
			sprintf(buff, "%.9f", data);
			lcd_print(buff);
			break;
	}
}

void lcd_clear()
{
	lcd_setCursor(0,0);
	lcd_print("                ");
	lcd_setCursor(0,1);
	lcd_print("                ");
}
