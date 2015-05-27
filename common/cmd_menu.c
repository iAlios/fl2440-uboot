#include <common.h>
#include <command.h>

extern char console_buffer[];
static char awaitkey(unsigned long delay, int* error_p) {
	int i;

	if (delay == -1) {
		while (1) {
			if (tstc()) /* we got a key press   */
				return getc();
		}
	} else {
		for (i = 0; i < delay; i++) {
			if (tstc()) /* we got a key pres   */
				return getc();
			udelay(10 * 1000);
		}
	}
	if (error_p)
		*error_p = -1;
	return 0;
}

void main_menu_usage(void) {
	printf("\r\n##### tftp menu for FL2440 #####\r\n");

	printf("[1] Download u-boot.bin to Nand Flash\r\n");
	printf("[2] Download uImage     to Nand Flash\r\n");
	printf("[3] Download root_yaffs2to Nand Flash\r\n");
	printf("[4] Download u-boot.bin to SDRAM &Run\r\n");
	printf("[5] Download uImage     to SDRAM &Run\r\n");
	printf("[b] Boot the system\r\n");
	printf("[r] Reboot u-boot\r\n");
	printf("[q] Quit from menu\r\n");
	printf("Enter your selection: ");
}

void menu_shell(void) {
	char c;
	char cmd_buf[200];

	while (1) {
		main_menu_usage();
		c = awaitkey(-1, NULL);
		printf("%c\n", c);
		switch (c) {
		case '1': {
			strcpy(cmd_buf,
					"tftp 0x31000000 u-boot.bin; nand erase.part bootloader; nand write.jffs2 0x31000000 bootloader");
			run_command(cmd_buf, 0);
			break;
		}
		case '2': {
			strcpy(cmd_buf,
					"tftp 0x31000000 uImage; nand erase.part kernel; nand write.jffs2 0x31000000 kernel");
			run_command(cmd_buf, 0);
			break;
		}

		case '3': {
			strcpy(cmd_buf,
					"tftp 0x31000000 root_yaffs2; nand erase.part root; nand write.yaffs 0x31000000 0x460000 0x528000");
			run_command(cmd_buf, 0);
			break;
		}

		case '4': {
			strcpy(cmd_buf, "tftp 0x31000000 u-boot.bin; go 0x31000000");
			run_command(cmd_buf, 0);
			break;
		}
		case '5': {
			strcpy(cmd_buf, "tftp 0x30007FC0 uImage; bootm 0x30007FC0");
			run_command(cmd_buf, 0);
			break;
		}

		case 'b': {
			printf("Booting Linux ...\n");
			strcpy(cmd_buf,
					"nand read.jffs2 0x30007FC0 kernel; bootm 0x30007FC0");
			run_command(cmd_buf, 0);
			break;
		}

		case 'r': {
			strcpy(cmd_buf, "reset");
			run_command(cmd_buf, 0);
			break;
		}

		case 'q': {
			return;
			break;
		}

		}

	}
}

int do_menu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]) {
	menu_shell();
	return 0;
}

U_BOOT_CMD(menu, 3, 0, do_menu,
		"menu - display a menu, to select the items to do something\n",
		" - display a menu, to select the items to do something");
