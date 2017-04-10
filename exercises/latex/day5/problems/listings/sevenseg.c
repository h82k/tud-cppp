long d;					// always define variables at the beginning of a block!
for (d = 0; d < DELAY; ++d) {
	__wait_nop();		// wait one cycle
}
