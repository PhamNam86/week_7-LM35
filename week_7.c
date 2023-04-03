#include <16F887.h>
#device *=16 adc=10
#FUSES HS, NOWDT, NOPUT, NOLVP, NOPROTECT, NOBROWNOUT
#use delay(clock=8M)
#include <lcd.h>
float GIA_TRI=0, NHIET_DO;
long NHIET_DO_100;
//long index=0;
void main(){
	set_tris_a(0xFF);
	set_tris_b(0x00);// SET PORT B LA OUTPUT
	set_tris_d(0x00);
	set_tris_e(0xff);
	
	SETUP_ADC(ADC_CLOCK_INTERNAL);
	setup_adc_ports(san7);
	lcd_init();
	
	delay_ms(5);
	output_b(0x00);
	
	lcd_gotoxy(1,1);
	printf(lcd_putc,"TEMPERATURE");
	lcd_gotoxy(1,2);
	printf(lcd_putc,"Temp:");
	while(TRUE)
	{
		
	/*	output_b(index) ;
		delay_ms(200);
		index+=1;
		if(index == 256) 
		index=0 ; // reset bien dem index
    */
		SET_ADC_CHANNEL(7);
		DELAY_ms(50);
		GIA_TRI=READ_ADC();
		delay_ms(500);
		NHIET_DO = GIA_TRI/2.048;
		NHIET_DO_100 =(long)(100 * NHIET_DO);		// GIA TRI NHIET DO
		LCD_GOTOXY(6,2);
		PRINTF(LCD_PUTC," %f ",NHIET_DO);
		DELAY_ms(500);

	if(NHIET_DO >= 100 )
	{
	output_low(pin_b0); 
	output_low(pin_b1); 
	output_low(pin_b2);
	output_low(PIN_B3); 
	output_low(pin_b4);	
	output_low(pin_b5);
	output_high(pin_b6); 
	OUTPUT_HIGH(PIN_B7);

    //PRINTF(LCD_PUTC," %f ",NHIET_DO);
	}
	if(50 < NHIET_DO && NHIET_DO < 100){
	output_low(pin_b1);
	output_high(pin_b5);
	output_low(pin_b0); 
	output_low(pin_b2); 
	output_high(pin_b3); 
	output_high(pin_b4);
	output_low(pin_b6); 
	output_low(pin_b7);
    //PRINTF(LCD_PUTC," %f ",NHIET_DO);
	}
	if(NHIET_DO <= 50)
	{	output_high(pin_b0);
	output_low(pin_b4);
	output_high(pin_b1); 
	output_high(pin_b2); 
	output_low(pin_b3); 
	output_low(pin_b5);
	output_low(pin_b6); 
	output_low(pin_b7);

    //PRINTF(LCD_PUTC," %f ",NHIET_DO);
	}
	if(NHIET_DO <= 0){
	output_b(0xFF);
	delay_ms(500);
	output_b(0x00);
	delay_ms(500);
	
	}
	
 }
}