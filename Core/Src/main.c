/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CO_app_STM32.h"
#include "OD.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#define PWM_PERIOD 2999
#define PI 3.14159265359
#define _PI_2 1.57079632679f
#define FULL_ROTATION (2 * PI)
#define AS5147U_ANGLE_REG  0x3FFF
#define AS5147U_COMMAND_RW_BIT 14
#define AS5147U_BIT_RESOLUTION 14
#define AS5147U_CPR 14
#define AS5147U_COMMAND_PARITY_BIT 15
#define DEG_PER_RAD 57.2957795131
#define DEG_TO_RAD 0.0174533
#define V_MIN -8.0
#define V_LIMIT 10.0
#define INTEGRAL_LIMIT  1.0
#define VQ_MIN_THRESHOLD  1.5
#define OVERCURRENT_LIMIT_SQ 2.8
float current_sq;
volatile uint32_t adc_value_A0, t_prev;
volatile uint32_t adc_value_A2;
float ia,ib,ic,i_alpha,i_beta,i_d,i_q,Valpha,Vbeta,Va,Vb,Vc,angle,error_d,error_q,error_d_sum, error_q_sum, speed_error_sum, error_pos_sum;
float Id_ref = 0.0;
float Iq_ref = 0.1 ,theta_ref = 0 ,velocity_ref = 600;
float Ki = 1.0 , Kp = 1.1 ,Kp_speed = 2, Ki_speed = 0.02,Kd_speed = 0, Ki_pos = 0.08, Kp_pos = 100 ,Kd_pos = 15;
float angle_current,angle_previous,velocity,total_angle,error_pos,theta_now,alpha = 0.9;
float previous_angle;
int turn_count = 0;
float execution_time,dt,speed_dt;
float angle_elec_rad,angle_elec_deg;
float angle_offset;
float error_speed;
uint16_t PWM_A,PWM_B,PWM_C;
uint16_t rawCount;
uint8_t PWMA[50];
uint8_t PWMB[50];
uint8_t PWMC[50];
uint8_t array_iq[50];
uint8_t array_iq_ref[50];
float theta = 0;
float Vd =0;
float Vq;
float output_q_rate;
float Vq_unclamped;
float elec_angle;
float shunt_resistor = 0.01;
float amp_gain = 50.0;
float volts_to_amps_ratio;
float offset_ia = 0;
float offset_ib = 0;
float offset_ic = 0;
float theta_align;
uint16_t adc_inj_val[2];
uint16_t cnt_val;
uint16_t adc_value_A = 0;
uint16_t adc_value_B = 0;
uint16_t adc_value_C = 0;
int pole_pairs = 7;
float total_angle_rad;
int speed_loop_counter = 0;
volatile uint8_t flag_current_loop = 0;
volatile uint8_t uart_busy = 0;
float error_q_prev = 0;
float error_d_prev = 0;
float voltage;
uint32_t adc_dma_value;
float adc_dma_voltage;
int i = 0;
float Iq_rate,idq=0;
float32_t rx_theta = 0;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

CAN_HandleTypeDef hcan1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim8;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM8_Init(void);
static void MX_UART4_Init(void);
static void MX_ADC2_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM7_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

unsigned long _micros(){
	return HAL_GetTick()*1000;
}

void Update_dt()
{

	 static uint32_t t_prev = 0;
	uint32_t t_now = _micros();
	dt = (t_now - t_prev) / 1000000.0f;
	if (dt <= 0.0f || dt > 0.5f) dt = 0.001f;
	t_prev = t_now;

}

void update_speed_dt()
{
	 static uint32_t t_speed_prev = 0;
	uint32_t t_speed_now = _micros();
	speed_dt = (t_speed_now - t_speed_prev) / 1000000.0f;
	if (speed_dt <= 0.0f || speed_dt > 0.5f) speed_dt = 0.001f;
	t_speed_prev = t_speed_now;
}

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim3,0);
	while (__HAL_TIM_GET_COUNTER(&htim3) < us);
}

uint8_t spiCalcEvenParity(uint16_t value) {
    uint8_t cnt = 0;
    for (uint8_t i = 0; i < 16; i++) {
        if (value & 0x1) cnt++;
        value >>= 1;
    }
    return cnt & 0x1;
}

uint16_t AS5147U_ReadAngle() {
    uint16_t command = AS5147U_ANGLE_REG ;
    command |= (1 << 14);
    command |= ((uint16_t)spiCalcEvenParity(command) << 15);
    uint16_t receivedData;

    uint16_t nop = 0x0000;

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, (uint8_t*)&command, 1, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&hspi1,(uint8_t*)&nop ,(uint8_t*)&receivedData, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

    receivedData = receivedData >> (1 + 13 - AS5147U_BIT_RESOLUTION);
    const uint16_t data_mask = 0xFFFF >> (16 - AS5147U_BIT_RESOLUTION);
    return receivedData & data_mask;

}

float normalize_angle(float angle_elec_rad) {
    while (angle_elec_rad >= 2 * M_PI) angle_elec_rad -= 2 * M_PI;
    while (angle_elec_rad < 0) angle_elec_rad += 2 * M_PI;
    return angle_elec_rad;
}

float AS5147U_GetAngleRad() {
    rawCount = AS5147U_ReadAngle();
    return rawCount / 16384.0 * 2.0 * PI;
}

float electricalAngle() {
	float mechanical_angle_rad = AS5147U_GetAngleRad();
     elec_angle = ((mechanical_angle_rad - angle_offset)) * pole_pairs;
    while (elec_angle >= 2 * M_PI) elec_angle -= 2 * M_PI;
    while (elec_angle < 0) elec_angle += 2 * M_PI;
    return elec_angle;
}


void alignRotor() {
    float V_align = 3.0;

    Va = V_align;
    PWM_A = ((Va / 8.0 + 0.5) * PWM_PERIOD)*0.4;
    PWM_B = 0;
    PWM_C = 0;

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_A);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_B);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, PWM_C);

    HAL_Delay(800);

    angle_offset = AS5147U_GetAngleRad();

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}
void clark()
{
 	i_alpha = ia;
	i_beta = (ib - ic) / sqrt(3);
}

void park()
{
	i_d = i_alpha*cos(theta) + i_beta*sin(theta);
	i_q = -i_alpha*sin(theta) + i_beta*cos(theta);
	idq = sqrt( i_d * i_d + i_q * i_q);
}

void setpwm(){

	PWM_A = ((Va / 8.0 + 1.0) * PWM_PERIOD ) * 0.4;
	PWM_B = ((Vb / 8.0 + 1.0) * PWM_PERIOD ) * 0.4;
	PWM_C = ((Vc / 8.0 + 1.0) * PWM_PERIOD ) * 0.4;


	 current_sq = sqrt(ia * ia + ib * ib + ic * ic);
	 //current_sq = ia * ia + ib * ib + ic * ic;


	if (current_sq > OVERCURRENT_LIMIT_SQ) {
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
	    //HAL_Delay(5000);

	} else {
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_A);
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_B);
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, PWM_C);
	}
//	if (adc_dma_voltage < 1.5 || adc_dma_voltage > 1.9) {
//		    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
//		    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
//		    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
//		    //HAL_Delay(5000);
//
//		} else {
//		    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_A);
//		    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_B);
//		    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, PWM_C);
//		}
}

void update_PID()
{
    if((velocity_ref > -100 && velocity_ref <= 0) || (velocity_ref > 0 && velocity_ref <= 100))
    {
        Ki = 0.8;
        Kp = 0.9;
    }
    else if((velocity_ref > -150 && velocity_ref <= -100)||(velocity_ref > 100 && velocity_ref <= 150))
    {
        Ki = 1.0;
        Kp = 1.1;
    }
    else if((velocity_ref > -250 && velocity_ref <= -150)||(velocity_ref > 150 && velocity_ref <= 250))
    {
        Ki = 1.1;
        Kp = 1.1;
    }
    else if((velocity_ref > -350 && velocity_ref <= -250)||(velocity_ref > 250 && velocity_ref <= 350))
    {
        Ki = 1.1;
        Kp = 0.9;
    }
    else if((velocity_ref > -500 && velocity_ref <= -350)||(velocity_ref > 350 && velocity_ref <= 500))
    {
        Ki = 1.3;
        Kp = 1.6;
    }
    else if((velocity_ref > -750 && velocity_ref <= -500)||(velocity_ref > 500 && velocity_ref <= 750))
    {
        Ki = 1.6;
        Kp = 1.7;
    }
    else if((velocity_ref > -1000 && velocity_ref <= -750)||(velocity_ref > 750 && velocity_ref <= 1000))
    {
        Ki = 1.8;
        Kp = 2.1;
    }
    else if((velocity_ref > -1500 && velocity_ref <= -1000)||(velocity_ref > 1000 && velocity_ref <= 1500))
    {
        Ki = 1.9;
        Kp = 2.2;
    }
    else
    {
        Ki = 2.2;
        Kp = 2.8;
    }
}

void update_PID_position()
{

}

void position_loop()
{
//	static float error_pos_prev = 0;
//	static float error_pos_sum = 0;
//	static float position_dt = 0.012;
//
//	 float raw_angle = AS5147U_GetAngleRad();
//	 theta_now =raw_angle;
//	 error_pos = theta_ref - theta_now;
//
//	 error_pos = normalize_angle(error_pos);
//
//	   if (error_pos > M_PI){
//		   error_pos-=2*M_PI;
//	    }

	    static float error_pos_sum = 0;
	    static float position_dt = 0.012;

	    static float raw_angle_prev = 0;
	    static int turn_count = 0;

	    static float velocity_ref_prev = 0; // Lưu giá trị trước đó của velocity_ref

	    float raw_angle = AS5147U_GetAngleRad();  // [0, 2π]
	    float delta = raw_angle - raw_angle_prev;

	    if (delta > M_PI) turn_count--;
	    else if (delta < -M_PI) turn_count++;

	    raw_angle_prev = raw_angle;

	    // Multi-turn position
	    theta_now = raw_angle + turn_count * 2.0f * M_PI;
	    error_pos = theta_ref - theta_now;

	    // PID vị trí
	    error_pos_sum += error_pos * position_dt;
	    error_pos_sum = fminf(fmaxf(error_pos_sum, -0.5f), 0.5f);

//	    float derivative_pos = (error_pos - error_pos_prev) / position_dt;
//	    error_pos_prev = error_pos;

	    float velocity_unclamped = Kp_pos * error_pos + Ki_pos * error_pos_sum;// + Kd_pos * derivative_pos;
	    velocity_unclamped = fminf(fmaxf(velocity_unclamped, -1000), 1000);

	    // Ramping giới hạn tốc độ thay đổi của velocity_ref
	    float velocity_ramp = 1000.0f;  // Giá trị ramping (đơn vị: rad/s²)
	    float velocity_rate = (velocity_unclamped - velocity_ref_prev) / position_dt;

	    if (velocity_rate > velocity_ramp)
	        velocity_ref = velocity_ref_prev + velocity_ramp * position_dt;
	    else if (velocity_rate < -velocity_ramp)
	        velocity_ref = velocity_ref_prev - velocity_ramp * position_dt;
	    else
	        velocity_ref = velocity_unclamped;

	    velocity_ref_prev = velocity_ref; // Cập nhật giá trị trước đó
}

void Speed_Loop()
{
	//update_speed_dt();
	speed_dt = 0.004;
    static float angle_prev = 0;
    static float error_speed_prev = 0;
    float angle_now = electricalAngle();
    float delta_angle = angle_now - angle_prev;

    if (delta_angle > PI) delta_angle -= 2 * PI;
    if (delta_angle < -PI) delta_angle += 2 * PI;

    velocity = alpha * velocity + (1 - alpha) * ((delta_angle / speed_dt) * (60.0f / (2.0f * PI)));
   // float abs_speed = fabs(velocity);
    error_speed = velocity_ref - velocity;
    speed_error_sum += error_speed * speed_dt;
    speed_error_sum = fminf(fmaxf(speed_error_sum, -0.8f), 0.8f);

    float derivative = (error_speed - error_speed_prev) / speed_dt;
    error_speed_prev = error_speed;

    float Iq_unlimited = Kp_speed * error_speed + Ki_speed * speed_error_sum + Kd_speed * derivative;

       float Ts = speed_dt;
       float Iq_ramp = 1000;
       //float Iq_ramp = 0.5;


       static float Iq_ref_prev = 0.0f;
        Iq_rate = (Iq_unlimited - Iq_ref_prev) / Ts;
       if (Iq_rate > Iq_ramp)
           Iq_ref = Iq_ref_prev + Iq_ramp * Ts;
       else if (Iq_rate < -Iq_ramp)
           Iq_ref = Iq_ref_prev - Iq_ramp * Ts;
       else
           Iq_ref = Iq_unlimited;

       Iq_ref = fminf(fmaxf(Iq_ref, -0.3f), 0.3f);


       Iq_ref_prev = Iq_ref;

    angle_prev = angle_now;

}


void Current_Loop()
{
    Update_dt();

    theta = electricalAngle();
    clark();
    park();

    error_d = Id_ref - i_d;
    error_q = Iq_ref - i_q;


    error_d_sum += error_d * dt;
    error_q_sum += error_q * dt;

    error_d_sum = fminf(fmaxf(error_d_sum, -INTEGRAL_LIMIT), INTEGRAL_LIMIT);
    error_q_sum = fminf(fmaxf(error_q_sum, -INTEGRAL_LIMIT), INTEGRAL_LIMIT);

    float Vd_unclamped = Kp * error_d + Ki * error_d_sum ;
     Vq_unclamped = Kp * error_q + Ki * error_q_sum ;

    float V_limit = 8.0f;
//    Vd_unclamped = fminf(fmaxf(Vd_unclamped, -V_limit), V_limit);
//    Vq_unclamped = fminf(fmaxf(Vq_unclamped, -V_limit), V_limit);

    // Ramping
    static float Vd_prev = 0;
    static float Vq_prev = 0;
    float output_ramp = 100.0f;

    float output_d_rate = (Vd_unclamped - Vd_prev) / dt;
    output_q_rate = (Vq_unclamped - Vq_prev) / dt;

    if (output_d_rate > output_ramp)
        Vd = Vd_prev + output_ramp * dt;
    else if (output_d_rate < -output_ramp)
        Vd = Vd_prev - output_ramp * dt;
    else
        Vd = Vd_unclamped;

    if (output_q_rate > output_ramp)
        Vq = Vq_prev + output_ramp * dt;
    else if (output_q_rate < -output_ramp)
        Vq = Vq_prev - output_ramp * dt;
    else
        Vq = Vq_unclamped;

    Vd = fminf(fmaxf(Vd, -V_limit), V_limit);
    Vq = fminf(fmaxf(Vq, -V_limit), V_limit);

    Vd_prev = Vd;
    Vq_prev = Vq;

	Valpha = Vd * cos(theta) - Vq * sin(theta);
	Vbeta  = Vd * sin(theta) + Vq * cos(theta);

    Va = Valpha;
    Vb = -0.5 * Valpha + (sqrtf(3) / 2) * Vbeta ;
    Vc = -0.5 * Valpha - (sqrtf(3) / 2) * Vbeta ;

    setpwm(Va, Vb, Vc);
    HAL_ADC_Start_DMA(&hadc2, &adc_dma_value, 1);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM8_Init();
  MX_UART4_Init();
  MX_ADC2_Init();
  MX_CAN1_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  CANopenNodeSTM32 canopenNodeSTM32;
  canopenNodeSTM32.CANHandle = &hcan1;
  canopenNodeSTM32.HWInitFunction = MX_CAN1_Init;
  canopenNodeSTM32.timerHandle = &htim7;
  canopenNodeSTM32.desiredNodeID = 32;
  canopenNodeSTM32.baudrate = 1000;
  canopen_app_init(&canopenNodeSTM32);

  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_Base_Start_IT(&htim8);
  HAL_TIM_Base_Start(&htim3);
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  HAL_TIM_Base_Start(&htim2);
  HAL_ADCEx_InjectedStart_IT(&hadc1);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
  HAL_ADC_Start_DMA(&hadc2, &adc_dma_value, 1);
  angle = AS5147U_GetAngleRad();
  alignRotor();


  //position_loop();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  canopen_app_process();
	  	  	OD_get_f32(OD_find(OD, 0x2000) , 0x01, &rx_theta, true);
	  	  	     theta_ref=rx_theta;


	  	OD_PERSIST_COMM.x2200_TPDO.theta_now= theta_now;
	  	OD_PERSIST_COMM.x2200_TPDO.i_d= i_d;
	  	OD_PERSIST_COMM.x2200_TPDO.i_q= i_q;

	  if (flag_current_loop)
	     {
	         flag_current_loop = 0;
	         position_loop();
	         Speed_Loop();
	         update_PID();
	         Current_Loop();

	         }
	       //  voltage = (adc_dma_value / 4095.0) * 3.3;

	         i++;
	         speed_loop_counter++;

//	         if(speed_loop_counter >= 3)
//	         {
//       	     position_loop();
//          	 speed_loop_counter = 0;
//	         	                   }

	         // demo vòng tốc độ
/*
	                   if(speed_loop_counter >= 1500)
	                   {
//	                	   position_loop();
	                	   velocity_ref+= 200;
	                	   if(velocity_ref >= 2100)
	                		   velocity_ref = 0;
	                       speed_loop_counter = 0;
	                   }
*/

// demo vòng vị trí
//
//	                   if(i >= 5000)
//	                   {
//	                	   //theta_ref = 3*PI/2;
//	                	   //theta_ref += (2*PI)/3;
//	                	   theta_ref = theta_ref + M_PI/2;
//	             //   	   if(theta_ref >= 2*PI)
//	              //  		   theta_ref = PI/4;
//
//	                	   i = 0;
//	                   }



	     }

	      if (!uart_busy)
	      {
	    	  // vòng điều khiển dòng
//	          sprintf((char*)array_iq, "%.5f\t%.5f\r\n", i_q, Iq_ref);
//	          uart_busy = 1; // Đánh dấu UART đang bận
//	          HAL_UART_Transmit_DMA(&huart2, array_iq, strlen((char*)array_iq));

// vòng điều khiển tốc độ
//	    sprintf((char*)array_iq, "%f\t%f\t\r\n", velocity_ref, velocity);
//	    uart_busy = 1; // Đánh dấu UART đang bận
//	    HAL_UART_Transmit_DMA(&huart2, array_iq, strlen((char*)array_iq));


	    	  	    sprintf((char*)array_iq, "%f\t%f\t\r\n", theta_ref, theta_now);
	    	  	    uart_busy = 1; // Đánh dấu UART đang bận
	    	  	    HAL_UART_Transmit_DMA(&huart2, array_iq, strlen((char*)array_iq));

	    //
//	    	    sprintf((char*)array_iq, "%f\t%f\t\r\n", i_d, i_q);
//	    	    uart_busy = 1; // Đánh dấu UART đang bận
//	    	    HAL_UART_Transmit_DMA(&huart2, array_iq, strlen((char*)array_iq));
      }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};
  ADC_InjectionConfTypeDef sConfigInjected = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_0;
  sConfigInjected.InjectedRank = 1;
  sConfigInjected.InjectedNbrOfConversion = 2;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_480CYCLES;
  sConfigInjected.ExternalTrigInjecConvEdge = ADC_EXTERNALTRIGINJECCONVEDGE_RISING;
  sConfigInjected.ExternalTrigInjecConv = ADC_EXTERNALTRIGINJECCONV_T1_TRGO;
  sConfigInjected.AutoInjectedConv = DISABLE;
  sConfigInjected.InjectedDiscontinuousConvMode = ENABLE;
  sConfigInjected.InjectedOffset = 0;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_4;
  sConfigInjected.InjectedRank = 2;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 18;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_2TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = ENABLE;
  hcan1.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
  htim1.Init.Period = 2999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 44;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 19;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 179;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 1000;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 179;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 999;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB3 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_5)
    {
        __HAL_TIM_SET_COUNTER(&htim2, 0);
    }
}*/
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {


   	     cnt_val = __HAL_TIM_GET_COUNTER(&htim1);
   	     adc_inj_val[0]= HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
         adc_value_A0 = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
         adc_inj_val[1]= HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_2);
         adc_value_A2 = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_2);
         ia = (((adc_value_A0/4095.0)*3.3 - 1.65))/(50.0*0.01);
         ib = (((adc_value_A2/4095.0)*3.3 - 1.65))/(50.0*0.01);
         ic= -( ia + ib);

    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM8) // Kiểm tra đúng Timer
    {
        flag_current_loop = 1;  // Đánh dấu cần thực hiện vòng dòng
    }

    if (htim->Instance == TIM7) // Kiểm tra đúng Timer
        {
            HAL_IncTick();
        }

    if (htim == canopenNodeSTM32->timerHandle) {
          canopen_app_interrupt();
      }

}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) // Kiểm tra đúng UART2
    {
        uart_busy = 0;  // Đánh dấu UART đã sẵn sàng gửi tiếp
    }
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC2)
    {
        adc_dma_voltage = (adc_dma_value / 4095.0) * 3.3;
       // voltage = (adc_dma_value / 4095.0) * 3.3;
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
