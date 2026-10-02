ENTRY(_start)

SECTIONS
{
	. = 0x7c00;

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

	. = 0x7dfe;

	.boot_signature :
	{
		BYTE(0x55)
		BYTE(0xaa)
	}

	/DISCARD/ :
	{
		*(.eh_frame)
		*(.note*)
		*(.comment)
	}
}