ENTRY(_start)

SECTIONS
{
	. = 0x7c00;

	.boot :
	{
		*(.boot)
	}

	. = 0x7dfe;

	.boot_signature :
	{
		BYTE(0x55)
		BYTE(0xaa)
	}

	. = 0x7e00;

	.text :
	{
		*(.text)
	}

	.rodata :
	{
		*(.rodata*)
	}

	.data :
	{
		*(.data*)
	}

	.bss :
	{
		*(.bss*)
		*(COMMON)
	}

	/DISCARD/ :
	{
		*(.eh_frame)
		*(.note*)
		*(.comment)
	}
}