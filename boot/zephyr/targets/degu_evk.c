/*
 * Copyright (c) 2019 Atmark Techno, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <gpio.h>

#ifdef CONFIG_BOOT_USB_DFU_MODE
void start_usb_dfu_mode(void)
{
	struct device *gpio1 = device_get_binding(DT_GPIO_P1_DEV_NAME);
	u32_t sw;
	u32_t out = 0;

	/* SW4 */
	gpio_pin_configure(gpio1, 14, GPIO_DIR_IN | GPIO_PUD_PULL_UP);

	/* LED1 */
	gpio_pin_configure(gpio1, 7, GPIO_DIR_OUT);
	gpio_pin_write(gpio1, 7, 1);

	/* LED2 */
	gpio_pin_configure(gpio1, 5, GPIO_DIR_OUT);
	gpio_pin_write(gpio1, 5, 1);

	/*
	 * Degu Evaluation Kit enters to USB DFU mode
	 * if SW4 is pressed until booting.
	 */
	k_sleep(K_MSEC(1));
	while (gpio_pin_read(gpio1, 14, &sw)) {
	}

	if (sw == 0) {
		/* Indicate with LED blinking */
		while (1) {
			gpio_pin_write(gpio1, 7, out);
			gpio_pin_write(gpio1, 5, !out);
			out = !out;
			k_sleep(K_MSEC(500));
		}
	}
}
#endif
