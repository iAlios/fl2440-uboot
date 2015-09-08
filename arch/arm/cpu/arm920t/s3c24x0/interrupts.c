/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <gj@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

#include <asm/arch/s3c24x0_cpu.h>
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/proc-armv/ptrace.h>

static struct _irq_handler IRQ_HANDLER[N_IRQS];

static void default_isr(void *data)
{
	struct s3c24x0_interrupt * const intregs = s3c24x0_get_base_interrupt();
	printf("default_isr():  called for IRQ %d, Interrupt Status=%x PR=%x\n",
	       (int)data, readl(intregs->SRCPND), readl(intregs->PRIORITY));
}

static int next_irq(void)
{
	struct s3c24x0_interrupt * const intregs = s3c24x0_get_base_interrupt();
	return readl(&intregs->INTOFFSET);
}

void do_irq (struct pt_regs *pt_regs)
{
	int irq = next_irq();

	IRQ_HANDLER[irq].m_func(IRQ_HANDLER[irq].m_data);
}

void irq_install_handler (int irq, interrupt_handler_t handle_irq, void *data)
{
	if (irq >= N_IRQS || !handle_irq)
		return;

	IRQ_HANDLER[irq].m_data = data;
	IRQ_HANDLER[irq].m_func = handle_irq;
}

int arch_interrupt_init (void)
{
	int i;

	/* install default interrupt handlers */
	for (i = 0; i < N_IRQS; i++)
		irq_install_handler(i, default_isr, (void *)i);
	
#if defined(CONFIG_FL2440_LED)
	struct s3c24x0_gpio * const gpio = s3c24x0_get_base_gpio();
	gpio->GPBDAT = ((1<<5) | (1<<6) | (1<<8) | (1<<10));
	gpio->GPBDAT &= 0xffe;
	gpio->GPBDAT = ~(1<<8);
#endif

	struct s3c24x0_interrupt * const intregs = s3c24x0_get_base_interrupt();

	/* configure interrupts for IRQ mode */
	intregs->INTMSK |= 0xFFFFFFFF;

	return (0);
}

