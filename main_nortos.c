/*
 * Copyright (c) 2017-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,

 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_nortos.c ========
 */
#include <stdint.h>
#include <stddef.h>

#include <NoRTOS.h>

#include <ti/drivers/Board.h>

extern void *mainThread(void *arg0);

/*
 * cmsis_msp432e4_dsp_example
 */
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Display Include via console */
#include "uartstdio.h"

#include "arm_math.h"
#include "arm_const_structs.h"

/* Define for Samples to be captured and Sampling Frequency */
#define NUM_SAMPLES 1024
#define SAMP_FREQ   1024000

/* DMA Buffer declaration and buffer complete flag */
static uint32_t bbxBuffer[1024] = {2048, 2087, 2126, 2165, 2204, 2243, 2282, 2321, 2360, 2399, 2437, 2475, 2513, 2551, 2589, 2627, 2664, 2701, 2738, 2774, 2810, 2846, 2882, 2917, 2952, 2986, 3020, 3054, 3088, 3121, 3153, 3185, 3217, 3248, 3279, 3309, 3339, 3368, 3397, 3425, 3453, 3480, 3507, 3533, 3559, 3584, 3608, 3632, 3655, 3678, 3700, 3722, 3743, 3763, 3783, 3802, 3820, 3838, 3856, 3872, 3888, 3904, 3919, 3933, 3946, 3959, 3972, 3983, 3995, 4005, 4015, 4024, 4033, 4041, 4049, 4056, 4062, 4068, 4073, 4078, 4082, 4085, 4088, 4091, 4092, 4094, 4095, 4095, 4095, 4094, 4093, 4091, 4089, 4087, 4084, 4080, 4076, 4072, 4068, 4062, 4057, 4051, 4045, 4038, 4031, 4024, 4017, 4009, 4001, 3992, 3983, 3975, 3965, 3956, 3946, 3936, 3926, 3916, 3905, 3895, 3884, 3873, 3862, 3851, 3839, 3828, 3817, 3805, 3793, 3782, 3770, 3758, 3747, 3735, 3723, 3711, 3700, 3688, 3676, 3665, 3653, 3641, 3630, 3619, 3607, 3596, 3585, 3574, 3564, 3553, 3542, 3532, 3522, 3512, 3502, 3492, 3482, 3473, 3464, 3455, 3446, 3437, 3429, 3420, 3412, 3405, 3397, 3390, 3382, 3375, 3369, 3362, 3356, 3349, 3344, 3338, 3332, 3327, 3322, 3317, 3313, 3308, 3304, 3300, 3296, 3293, 3290, 3286, 3283, 3281, 3278, 3276, 3273, 3271, 3270, 3268, 3266, 3265, 3264, 3263, 3262, 3261, 3261, 3260, 3260, 3259, 3259, 3259, 3259, 3259, 3260, 3260, 3260, 3261, 3261, 3262, 3263, 3263, 3264, 3265, 3266, 3266, 3267, 3268, 3269, 3270, 3271, 3271, 3272, 3273, 3274, 3274, 3275, 3275, 3276, 3276, 3277, 3277, 3277, 3277, 3278, 3278, 3277, 3277, 3277, 3276, 3276, 3275, 3274, 3274, 3273, 3271, 3270, 3269, 3267, 3266, 3264, 3262, 3260, 3258, 3255, 3253, 3250, 3247, 3244, 3241, 3238, 3235, 3231, 3228, 3224, 3220, 3216, 3212, 3207, 3203, 3198, 3194, 3189, 3184, 3179, 3174, 3169, 3163, 3158, 3152, 3147, 3141, 3135, 3129, 3123, 3117, 3111, 3105, 3098, 3092, 3086, 3079, 3073, 3066, 3060, 3053, 3047, 3040, 3034, 3027, 3020, 3014, 3007, 3001, 2994, 2988, 2982, 2975, 2969, 2963, 2957, 2950, 2944, 2939, 2933, 2927, 2921, 2916, 2910, 2905, 2900, 2895, 2890, 2885, 2880, 2876, 2871, 2867, 2863, 2859, 2855, 2851, 2848, 2845, 2842, 2839, 2836, 2833, 2831, 2829, 2827, 2825, 2823, 2822, 2820, 2819, 2818, 2818, 2817, 2817, 2817, 2817, 2817, 2817, 2818, 2819, 2820, 2821, 2822, 2824, 2826, 2827, 2829, 2832, 2834, 2837, 2839, 2842, 2845, 2848, 2851, 2855, 2858, 2862, 2866, 2869, 2873, 2877, 2882, 2886, 2890, 2895, 2899, 2903, 2908, 2913, 2917, 2922, 2927, 2931, 2936, 2941, 2945, 2950, 2955, 2959, 2964, 2968, 2973, 2977, 2982, 2986, 2990, 2994, 2998, 3002, 3006, 3009, 3013, 3016, 3019, 3022, 3025, 3028, 3030, 3032, 3034, 3036, 3038, 3039, 3041, 3042, 3042, 3043, 3043, 3043, 3043, 3042, 3041, 3040, 3039, 3037, 3035, 3033, 3030, 3027, 3024, 3020, 3016, 3012, 3008, 3003, 2998, 2992, 2986, 2980, 2973, 2967, 2959, 2952, 2944, 2935, 2927, 2918, 2909, 2899, 2889, 2879, 2868, 2857, 2845, 2834, 2822, 2809, 2797, 2784, 2770, 2757, 2743, 2729, 2714, 2699, 2684, 2669, 2653, 2637, 2621, 2604, 2588, 2571, 2553, 2536, 2518, 2500, 2482, 2464, 2445, 2427, 2408, 2389, 2370, 2350, 2331, 2311, 2291, 2271, 2252, 2231, 2211, 2191, 2171, 2150, 2130, 2109, 2089, 2069, 2048, 2027, 2007, 1987, 1966, 1946, 1925, 1905, 1885, 1865, 1844, 1825, 1805, 1785, 1765, 1746, 1726, 1707, 1688, 1669, 1651, 1632, 1614, 1596, 1578, 1560, 1543, 1525, 1508, 1492, 1475, 1459, 1443, 1427, 1412, 1397, 1382, 1367, 1353, 1339, 1326, 1312, 1299, 1287, 1274, 1262, 1251, 1239, 1228, 1217, 1207, 1197, 1187, 1178, 1169, 1161, 1152, 1144, 1137, 1129, 1123, 1116, 1110, 1104, 1098, 1093, 1088, 1084, 1080, 1076, 1072, 1069, 1066, 1063, 1061, 1059, 1057, 1056, 1055, 1054, 1053, 1053, 1053, 1053, 1054, 1054, 1055, 1057, 1058, 1060, 1062, 1064, 1066, 1068, 1071, 1074, 1077, 1080, 1083, 1087, 1090, 1094, 1098, 1102, 1106, 1110, 1114, 1119, 1123, 1128, 1132, 1137, 1141, 1146, 1151, 1155, 1160, 1165, 1169, 1174, 1179, 1183, 1188, 1193, 1197, 1201, 1206, 1210, 1214, 1219, 1223, 1227, 1230, 1234, 1238, 1241, 1245, 1248, 1251, 1254, 1257, 1259, 1262, 1264, 1267, 1269, 1270, 1272, 1274, 1275, 1276, 1277, 1278, 1279, 1279, 1279, 1279, 1279, 1279, 1278, 1278, 1277, 1276, 1274, 1273, 1271, 1269, 1267, 1265, 1263, 1260, 1257, 1254, 1251, 1248, 1245, 1241, 1237, 1233, 1229, 1225, 1220, 1216, 1211, 1206, 1201, 1196, 1191, 1186, 1180, 1175, 1169, 1163, 1157, 1152, 1146, 1139, 1133, 1127, 1121, 1114, 1108, 1102, 1095, 1089, 1082, 1076, 1069, 1062, 1056, 1049, 1043, 1036, 1030, 1023, 1017, 1010, 1004, 998, 991, 985, 979, 973, 967, 961, 955, 949, 944, 938, 933, 927, 922, 917, 912, 907, 902, 898, 893, 889, 884, 880, 876, 872, 868, 865, 861, 858, 855, 852, 849, 846, 843, 841, 838, 836, 834, 832, 830, 829, 827, 826, 825, 823, 822, 822, 821, 820, 820, 819, 819, 819, 818, 818, 819, 819, 819, 819, 820, 820, 821, 821, 822, 822, 823, 824, 825, 825, 826, 827, 828, 829, 830, 830, 831, 832, 833, 833, 834, 835, 835, 836, 836, 836, 837, 837, 837, 837, 837, 836, 836, 835, 835, 834, 833, 832, 831, 830, 828, 826, 825, 823, 820, 818, 815, 813, 810, 806, 803, 800, 796, 792, 788, 783, 779, 774, 769, 764, 758, 752, 747, 740, 734, 727, 721, 714, 706, 699, 691, 684, 676, 667, 659, 650, 641, 632, 623, 614, 604, 594, 584, 574, 564, 554, 543, 532, 522, 511, 500, 489, 477, 466, 455, 443, 431, 420, 408, 396, 385, 373, 361, 349, 338, 326, 314, 303, 291, 279, 268, 257, 245, 234, 223, 212, 201, 191, 180, 170, 160, 150, 140, 131, 121, 113, 104, 95, 87, 79, 72, 65, 58, 51, 45, 39, 34, 28, 24, 20, 16, 12, 9, 7, 5, 3, 2, 1, 1, 1, 2, 4, 5, 8, 11, 14, 18, 23, 28, 34, 40, 47, 55, 63, 72, 81, 91, 101, 113, 124, 137, 150, 163, 177, 192, 208, 224, 240, 258, 276, 294, 313, 333, 353, 374, 396, 418, 441, 464, 488, 512, 537, 563, 589, 616, 643, 671, 699, 728, 757, 787, 817, 848, 879, 911, 943, 975, 1008, 1042, 1076, 1110, 1144, 1179, 1214, 1250, 1286, 1322, 1358, 1395, 1432, 1469, 1507, 1545, 1583, 1621, 1659, 1697, 1736, 1775, 1814, 1853, 1892, 1931, 1970, 2009};

/* Global variables and defines for FFT */
#define IFFTFLAG   0
#define BITREVERSE 1

void ConfigureUART(uint32_t systemClock)
{
    /* Enable the clock to GPIO port A and UART 0 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* Configure the GPIO Port A for UART 0 */
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Configure the UART for 115200 bps 8-N-1 format */
    UARTStdioConfig(0, 115200, systemClock);
}

/*
 *  ======== main ========
 */
int main(void)
{
    Board_init();

    /* Start NoRTOS */
    NoRTOS_start();

    /* Call mainThread function */
    mainThread(NULL);

    /*
     * cmsis_msp432e4_dsp_example
     */
    uint32_t systemClock;

    /* Configure the system clock for 120 MHz */
    systemClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                          SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL |
                                          SYSCTL_CFG_VCO_480), 120000000);

    /* Initialize serial console */
    ConfigureUART(systemClock);

    /* Display the setup on the console. */
    UARTprintf("\033[2J\033[H");
    UARTprintf("\rCMSIS DSP Demo...\n\n");
    UARTprintf("\033[2GDC Average \033[31G\n");
    UARTprintf("\033[2GRMS \033[31G\n");
    UARTprintf("\033[2GFFT Amplitude \033[31G\n");
    UARTprintf("\033[2GFFT Frequency \033[31G\n");

    /* robust */
    /* Compute the 1024 point FFT on the sampled data and then find the
     * FFT point for maximum energy and the energy value */
    arm_cfft_q15(&arm_cfft_sR_q15_len1024, (q15_t *)bbxBuffer, IFFTFLAG,
                 BITREVERSE);

    while (1) {}
}
